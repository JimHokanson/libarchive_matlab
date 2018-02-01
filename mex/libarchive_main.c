#include "mac/archive.h"
#include "mac/archive_entry.h"

#include <stdint.h>
#include "mex.h"

/*
 mex -L"/Users/jim/Documents/repos/matlab_git/libarchive_matlab/mex/mac" -larchive.13 libarchive_main.c -v
 */

#define MEX_INPUT nlhs, plhs, nrhs, prhs
#define MEX_DEF_INPUT int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[] 

/*
 file_path = '/Users/jim/Desktop/test.zip';
 archive = libarchive_main(1,file_path)
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
    
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    
    //Currently hardcoded, eventually code be exposed as optional
    //For non-tapes block_size may be adjusted for better performance
    size_t block_size = 10240;
    
    //file_path = mxArrayToString(prhs[1]);
    //mexPrintf("Test: %s\n");
    r = archive_read_open_filename(a, "/Users/jim/Desktop/test.zip", block_size);
    
    //mexPrintf("%d",(int64_t)a);
    if (r != ARCHIVE_OK){
        mexErrMsgIdAndTxt("libarchive:archive_read_open_filename","Failed to open archive from filename");
    }
    
    plhs[0] = archive_to_mx(a);
}

void libarchive_read_free(MEX_DEF_INPUT){
    //
    //  archive = f(2,mx_archive)
    
    struct archive *a;
    int r;
    
    a = mx_to_archive(prhs[1]);
    
    r = archive_read_free(a);    
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
        case 1:
            libarchive_read_open_filename(MEX_INPUT);
            break;
        case 2:
            libarchive_read_free(MEX_INPUT);
            break;
        default:
            mexErrMsgIdAndTxt("libarchive:archive_select","Invalid function option");
    }
    
}

