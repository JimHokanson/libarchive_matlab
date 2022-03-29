#include "mac/archive.h"
#include "mac/archive_entry.h"

#include <string.h>
#include <stdint.h>
#include "mex.h"


/*
libarchive_main(0);
 mex -L"/Users/jim/Documents/repos/matlab_git/libarchive_matlab/mex/mac" -larchive.13 libarchive_main.c -v
 */

#define MEX_INPUT nlhs, plhs, nrhs, prhs
#define MEX_DEF_INPUT int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[] 

/*
 file_path = '/Users/jim/Desktop/test.zip';
 archive = libarchive_main(1,file_path);

 
 %List file names
names = libarchive_main(3,archive)


 %Freeing the archive
libarchive_main(2,archive)
 */    

    
//Helpers =================================================================    
mxArray* pointer_to_mx(int64_t v){
    mxArray *out = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
    int64_t *data = (int64_t *)mxGetData(out);
    *data = v;
    return out;
}

mxArray* archive_to_mx(struct archive *a){
    return pointer_to_mx((int64_t)a);
}

int64_t mx_to_int64(const mxArray *input){  
    int64_t *data = (int64_t *)mxGetData(input);
    return data[0];
}

//TODO: Ask why this didn't work
//void mx_to_archive(const mxArray *input, struct **a){
struct archive * mx_to_archive(const mxArray *input){
    //struct archive *a2 = (struct archive *) mx_to_int64(input)
    return (struct archive *) mx_to_int64(input);
    //*a = a2;
}

//1 Open a file based on name ---------------------------------------------
void libarchive_read_open_filename(MEX_DEF_INPUT){
    //
    //  archive = f(1,file_path)
    
    struct archive *a;
    int r;
    char *file_path;
    
    if (nrhs != 2){
        mexErrMsgIdAndTxt("libarchive:n_inputs","libarchive_read_open_filename requires 2 inputs");
    }
    
    a = archive_read_new();
    
    //We could make these options as well
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    
    //Currently hardcoded, eventually code be exposed as optional
    //For non-tapes block_size may be adjusted for better performance
    size_t block_size = 10240;
    
    file_path = mxArrayToString(prhs[1]);
    r = archive_read_open_filename(a, file_path, block_size);
    
    //Only counts the # of files processed
    //mexPrintf("count: %d\n",archive_file_count(a));
    
    if (r != ARCHIVE_OK){
        mexErrMsgIdAndTxt("libarchive:archive_read_open_filename","Failed to open archive from filename");
    }
    
    plhs[0] = archive_to_mx(a);
}

//2 Free the archive ------------------------------------------------------
void libarchive_read_free(MEX_DEF_INPUT){
    //
    //  archive = f(2,mx_archive)
    
    struct archive *a;
    int r;
    
    a = mx_to_archive(prhs[1]);
    
    r = archive_read_free(a);    
}

//3 Get the entry names ---------------------------------------------------
void lib2_get_entry_names(MEX_DEF_INPUT){
    //
    //  names = f(3,mx_archive)
    
    struct archive *a;
    struct archive_entry *entry;
    int r;
    
    a = mx_to_archive(prhs[1]);
    
    mxArray *output = mxCreateCellMatrix(100,1);
    mxArray *temp;
    //mxArray **entries = mxMalloc(100*
    
    //mxArray *mxCreateCellMatrix(mwSize m, mwSize n);
    //mxSetCell(mxArray *pm, mwIndex index, mxArray *value);
    //mxArray *mxCreateString(const char *str);
    
    int i = 0;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        temp = mxCreateString(archive_entry_pathname(entry));
        mxSetCell(output,i,temp);
        i++;
        if (i == 0){
            mexErrMsgIdAndTxt("libarchive:lib2_get_entry_names","Entry listing currently limited to 100 items which was exceeded");
        }
    }
    mxSetM(output,i);
    
    plhs[0] = output;
}

//4 Read a file into memory   ---------------------------------------------
void libarchive_read_data(MEX_DEF_INPUT){
//archive_read_data(struct archive *, void *buff, size_t len); 
    //
    //            0  1           2      3
    //  names = f(3, mx_archive, I,    *n_add)
    //  I - 1 based indexing
    //
    //  names = f(3, mx_archive, name, *n_add)
    //  name - name to match
    
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char *header_name;
    
    size_t n_add = 0;
    size_t I;
    bool found_header = false;
    
    
    if (!((nrhs == 3) | (nrhs == 4))){
        mexErrMsgIdAndTxt("libarchive:n_inputs","Function requires 3 or 4");
    }
    
    a = mx_to_archive(prhs[1]);
    
    if (nrhs == 4){
        if (!mxIsClass(prhs[3],"double")){
            mexErrMsgIdAndTxt("libarchive:input_type",
                    "# of samples to add must be a double");
        }else{
            n_add = (size_t)mxGetScalar(prhs[3]);
        }
    }
    
    if (mxIsClass(prhs[2],"double")){
        //Index advancement ---------------------
        I = (size_t)mxGetScalar(prhs[2]);
        for (size_t i = 0; i < I; i++){
           r = archive_read_next_header(a, &entry);
           if (r != ARCHIVE_OK){
               mexErrMsgIdAndTxt("libarchive:read_data",
                       "Error while reading headers");
           }
           if (i != (I-1)){
              archive_read_data_skip(a); 
           }
        }
    }else if (mxIsClass(prhs[2],"char")){
        //Name matching ---------------------------
        header_name = mxArrayToString(prhs[2]);
     	while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            if (strcmp(archive_entry_pathname(entry),header_name) == 0){
                found_header = true;
                break;
            }else{
                archive_read_data_skip(a);
            }
        }
        if (!found_header){
            
        }
    }else{
       mexErrMsgIdAndTxt("libarchive:input_type","3rd input must be char or double"); 
    }

    
    
    
    //mxIsDouble(const mxArray *pm)
    
    //TODO: Check the # of inputs
    
    //la_ssize_t
    //`- archive_read_data(struct archive *, void *buff, size_t len); 
    
}

int locked = 0;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[])
{
    //
    //  
    
    if (!locked)
    {
//         git_libgit2_init();
//         mexAtExit(&shutdown);
        mexLock();
        locked = 1;
    }
    
    if (nrhs < 1){
        mexErrMsgIdAndTxt("libarchive:n_inputs","At least 1 input is required");
    }else if (!mxIsClass(prhs[0],"double")){
        mexErrMsgIdAndTxt("libarchive:input_type","First input must be a double");
    }
    
    int type = (int) mxGetScalar(prhs[0]);
    
    switch (type) {
        case 0:
            mexUnlock();
            break;
        case 1:
            libarchive_read_open_filename(MEX_INPUT);
            break;
        case 2:
            libarchive_read_free(MEX_INPUT);
            break;
        case 3:
            lib2_get_entry_names(MEX_INPUT);
            break;
        case 4:
            libarchive_read_data(MEX_INPUT);
            break;
        default:
            mexErrMsgIdAndTxt("libarchive:archive_select","Invalid function option");
    }
    
}

