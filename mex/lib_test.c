//TODO: Switch on system

#if defined(_WIN32) && !defined(__CYGWIN__)
#else
#endif

#include "mac/archive.h"
#include "mac/archive_entry.h"


#include "mex.h"

//  mex -L/usr/local/opt/libarchive/lib -I/usr/local/opt/libarchive/include lib_test.c

/*
mex -L"/Users/jim/Documents/repos/matlab_git/libarchive_matlab/mex/mac" -larchive.13 lib_test.c
lib_test()
 *
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[])
{
    
    //Currently hardcoded to list file contents of zip on my desktop
    
    
//     Create one using archive_XXX_new()
//     Configure it using "support" or "set" calls.
//      ("Support" calls allow libarchive to decide when to use a feature,
//      "set" calls enable the feature unconditionally.)
//     "Open" a particular data source.
//     Iterate over the contents: ask alternately for "header"
//  (which returns an entry object describing the next entry in the archive)
//  and "data"
//     When you're done, you can "close", query any final information or
//    statistics, then call "free" to free the archive object. (The
//  "free" calls were named "finish" in earlier versions of libarchive.)
//
//
    
    struct archive *a;
    struct archive_entry *entry;
    int r;
    
    a = archive_read_new();
    
//https://github.com/libarchive/libarchive/wiki/Examples
    
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    
    
    
//https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadOpen3
    //archive_read_open_memory(struct archive *, void *buff, size_t size); 
    //
//archive_read_open_filename(struct archive *, const char *filename, size_t block_size); 
    size_t block_size = 10240;
    //For non-tapes block_size may be adjusted for better performance
    r = archive_read_open_filename(a, "/Users/jim/Desktop/test.zip", block_size); // Note 1
    
    if (r != ARCHIVE_OK){
        mexErrMsgIdAndTxt("lib:zip","archive open failure");
    }
    
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        mexPrintf("%s\n",archive_entry_pathname(entry));
        mexPrintf("Size: %d\n",archive_entry_size(entry));
        archive_read_data_skip(a);  // Note 2
    }
    
    r = archive_read_free(a);  // Note 3   archive_read_finish in older
//if (r != ARCHIVE_OK)
//c  exit(1);
    
    
//    struct archive *arch = archive_read_new();
//    struct archive_entry *ent;
//    int ret;
//
//    g_assert(arch != NULL);
//    g_assert(!archive_read_support_format_zip(arch));
//    g_assert(!archive_read_open_memory(arch, (void *) data, len));
//    while (!(ret = archive_read_next_header(arch, &ent))) {
//      if (archive_read_extract(arch, ent, ARCHIVE_EXTRACT_SECURE_SYMLINKS |
//                               ARCHIVE_EXTRACT_SECURE_NODOTDOT)) {
//        fprintf(stderr, "%s\n", archive_error_string(arch));
//        abort();
//      }
//    }
//    g_assert(ret == ARCHIVE_EOF);
//    g_assert(!archive_read_finish(arch));
// }
    
    
    
}