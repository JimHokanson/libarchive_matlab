%Documentation
%
%   The general process is to first create the struct archive object, set
%   options, initialize the reader, iterate over the archive headers and
%   associated data, then close the archive and release all resources.
%
%
%   --- Archive Entry ----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntry3
%
% #include <archive_entry.h>
% struct archive_entry *
% archive_entry_clear(struct archive_entry *);
% struct archive_entry *
% archive_entry_clone(struct archive_entry *);
% void
% archive_entry_free(struct archive_entry *);
% struct archive_entry *
% archive_entry_new(void); 
%
%
%   ---- ACL (Access Control List) ----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryAcl3
%   
% #include <archive_entry.h>
% void
% archive_entry_acl_add_entry(struct archive_entry *a, int type, int permset, int tag, int qualifier, const char *name);
% void
% archive_entry_acl_add_entry_w(struct archive_entry *a, int type, int permset, int tag, int qualifier, const wchar_t *name);
% void
% archive_entry_acl_clear(struct archive_entry *a);
% int
% archive_entry_acl_count(struct archive_entry *a, int type);
% int
% archive_entry_acl_next(struct archive_entry *a, int type, int *ret_type, int *ret_permset, int *ret_tag, int *ret_qual, const char **ret_name);
% int
% archive_entry_acl_next_w(struct archive_entry *a, int type, int *ret_type, int *ret_permset, int *ret_tag, int *ret_qual, const wchar_t **ret_name);
% int
% archive_entry_acl_reset(struct archive_entry *a, int type);
% const wchar_t *
% archive_entry_acl_text_w(struct archive_entry *a, int flags); 
%
%
%
%   Hardlinks
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryLinkify3
%
%   Paths
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryPaths3
%
%   Permissions
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryPerms3
%
%   Stat
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryStat3
%
%   -----   Time   -----
%   These functions create and manipulate the time fields in an archive_entry.
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryTime3
%
%   =================  READING ========================
%   -----   Read Overview  -----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveRead3
%
%   ------ Read New -----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadNew3
%
%   ------ Read Format -----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadFormat3
%
%   ------ Passphrase -----
%   Functionality for supporting password entry while reading
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadAddPassphrase3
%
%   ------ Read Options -----
%   Very generic, doesn't look relevant for most cases
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadSetOptions3
%
%   ------ Read Filter -----
%   Allows specification of what type of compression to allow
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadFilter3
%
%
%
%
%   ------ Read Open ----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadOpen3
%
%
%   ------ Read Header -----
%   Consume next header
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadHeader3
%
%   ------ Header Stats -----
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveEntryStat3
%
%   ------  Read Data  ------
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadData3
%
%
%
%   ------ Read Disk -----
%   ???? vs read open ????
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadDisk3
%
%   ------ Read Extract ------
%   ????
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadExtract3
%
%   ------ Read Free  ------
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveReadFree3
%
%   ------ Utils ------
%   https://github.com/libarchive/libarchive/wiki/ManPageArchiveUtil3









