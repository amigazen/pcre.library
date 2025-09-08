#ifndef CLIB_PCRE_PROTOS_H
#define CLIB_PCRE_PROTOS_H

/*
**  $VER: pcre_library.h 1.0 (19.10.2004)
**  Includes Release 1.0
**
**  C prototypes. For use with 32 bit integers only.
**
**  Written by Alfonso [alfie] Ranieri <alforan@tin.it>.
**
**  Released under the terms of the
**  GNU Public Licence version 2
*/

#ifndef LIBRARIES_PCRE_H
#include <libraries/pcre.h>
#endif

pcre_extra *PCREStudy ( const pcre *external_re , int options , int *errorptr );

int PCREGetStringNumber ( const pcre *code , const char *stringname );
int PCRECopySubString ( const char *subject , int *ovector , int stringcount , int stringnumber , char *buffer , int size );
int PCRECopyNamedSubstring ( const pcre *code , const char *subject , int *ovector , int stringcount , const char *stringname , char *buffer , int size );
int PCREGetUbstringList ( const char *subject , int *ovector , int stringcount , const char ***listptr );
void PCREFreeSubStringList ( const char **pointer );
int PCREGetSubString ( const char *subject , int *ovector , int stringcount , int stringnumber , const char **stringptr );
int PCREGetNamedSubString ( const pcre *code , const char *subject , int *ovector , int stringcount , const char *stringname , const char **stringptr );
void PCREFreeSubString ( const char *pointer );

const char *PCREVersion ( void );
int PCREInfo ( const pcre *argument_re , int *optptr , int *first_byte );
int PCREFullInfo ( const pcre *argument_re , const pcre_extra *extra_data , int what , void *where );
int PCREConfig ( int what , void *where );
pcre *PCRECompileA ( const char *pattern , int *errorptr , int *erroroffset , struct TagItem *attrs );
pcre *PCRECompile ( const char *pattern , int *errorptr , int *erroroffset , Tag tag1, ... );
int PCREExec ( const pcre *argument_re , const pcre_extra *extra_data , const char *subject , int length , int start_offset , int options , int *offsets , int offsetcount );
void PCREFree ( const pcre *argument_re );

STRPTR PCREGetString ( ULONG id );

#endif /* CLIB_PCRE_PROTOS_H */
