#ifndef _CLASS_PROTOS_H
#define _CLASS_PROTOS_H

/* init.c */
void freeBase ( void );
ULONG initBase ( void );

/* utils.c */
APTR allocVecPooled ( APTR pool , ULONG size );
void freeVecPooled ( APTR pool , APTR mem );
void *allocArbitratePooled ( size_t size );
void freeArbitratePooled ( void *mem , size_t size );
void *allocArbitrateVecPooled ( size_t size );
void freeArbitrateVecPooled ( void *mem );
#ifdef __MORPHOS__
#define sprintf(to, fmt, ...) \
({ ULONG _tags[] = { __VA_ARGS__ }; RawDoFmt(fmt, _tags, (void (*)(void)) 0, to); })
#endif

/* alloc.c */
APTR allocMem ( const pcre *re , ULONG size );
void freeMem ( const pcre *re , APTR mem );
pcre *allocRe ( struct Hook *hmalloc , APTR pool , struct SignalSemaphore *poolSem , ULONG size );
void freeRe ( const pcre *re );

/* loc.c */
struct Catalog *openCatalog ( STRPTR name , ULONG minVer , ULONG minRev );
#ifdef __MORPHOS__
STRPTR pcre_getstring ( ULONG id );
STRPTR LIB_pcre_getstring ( void );
#else
STRPTR SAVEDS ASM pcre_getstring ( REG (d0 )ULONG id );
#endif

/* maketables.c */
#ifdef __MORPHOS__
unsigned char *pcre_maketables ( struct Locale *locale );
unsigned char *LIB_pcre_maketables ( void );
#else
unsigned char *SAVEDS ASM pcre_maketables ( REG (a0 )struct Locale *locale );
#endif

/* study.c */
#ifdef __MORPHOS__
pcre_extra *pcre_study ( const pcre *external_re , int options , int *errorptr );
pcre_extra *LIB_pcre_study (void);
#else
SAVEDS ASM pcre_extra *pcre_study ( REG (a0 )const pcre *external_re , REG (d0 )int options , REG (a1 ) int *errorptr );
#endif

/* get.c */
#ifdef __MORPHOS__
int pcre_get_stringnumber ( const pcre *code , const char *stringname );
int pcre_copy_substring ( const char *subject , int *ovector , int stringcount , int stringnumber , char *buffer , int size );
int pcre_copy_named_substring ( const pcre *code , const char *subject , int *ovector , int stringcount , const char *stringname , char *buffer , int size );
int pcre_get_substring_list ( const char *subject , int *ovector , int stringcount , const char ***listptr );
void pcre_free_substring_list ( const char **pointer );
int pcre_get_substring ( const char *subject , int *ovector , int stringcount , int stringnumber , const char **stringptr );
int pcre_get_named_substring ( const pcre *code , const char *subject , int *ovector , int stringcount , const char *stringname , const char **stringptr );
void pcre_free_substring ( const char *pointer );

int LIB_pcre_get_stringnumber (void);
int LIB_pcre_copy_substring (void);
int LIB_pcre_copy_named_substring (void);
int LIB_pcre_get_substring_list (void);
void LIB_pcre_free_substring_list (void);
int LIB_pcre_get_substring (void);
int LIB_pcre_get_named_substring (void);
void LIB_pcre_free_substring (void);

#else
int SAVEDS ASM pcre_get_stringnumber ( REG (a0 )const pcre *code , REG (a1 )const char *stringname );
int SAVEDS ASM pcre_copy_substring ( REG (a0 )const char *subject , REG (a1 )int *ovector , REG (d0 )int stringcount , REG (d1 )int stringnumber , REG (a2 )char *buffer , REG (d2 )int size );
int SAVEDS ASM pcre_copy_named_substring ( REG (a0 )const pcre *code , REG (a1 )const char *subject , REG (a2 )int *ovector , REG (d0 )int stringcount , REG (a3 )const char *stringname , REG (d1 )char *buffer , REG (d2 )int size );
int SAVEDS ASM pcre_get_substring_list ( REG (a0 )const char *subject , REG (a1 )int *ovector , REG (d0 )int stringcount , REG (a2 )const char ***listptr );
void SAVEDS ASM pcre_free_substring_list ( REG (a0 )const char **pointer );
int SAVEDS ASM pcre_get_substring ( REG (a0 )const char *subject , REG (a1 )int *ovector , REG (d0 )int stringcount , REG (d1 )int stringnumber , REG (a2 )const char **stringptr );
int SAVEDS ASM pcre_get_named_substring ( REG (a0 )const pcre *code , REG (a1 )const char *subject , REG (a2 )int *ovector , REG (d0 )int stringcount , REG (a3 )const char *stringname , REG (d1 )const char **stringptr );
void SAVEDS ASM pcre_free_substring ( REG (a0 )const char *pointer );
#endif

/* pcre.c */
#ifdef __MORPHOS__
const char *pcre_version ( void );
int pcre_info ( const pcre *argument_re , int *optptr , int *first_byte );
int pcre_fullinfo ( const pcre *argument_re , const pcre_extra *extra_data , int what , void *where );
int pcre_config ( int what , void *where );
pcre *pcre_compileA ( const char *pattern , int *errorptr , int *erroroffset , struct TagItem *attrs );
int pcre_exec ( const pcre *argument_re , const pcre_extra *extra_data , const char *subject , int length , int start_offset , int options , int *offsets , int offsetcount );
void pcre_free ( pcre *re );

const char *LIB_pcre_version ( void );
int LIB_pcre_info (void);
int LIB_pcre_fullinfo (void);
int LIB_pcre_config (void);
pcre *LIB_pcre_compileA (void);
int LIB_pcre_exec (void);
void LIB_pcre_free (void);
#else
SAVEDS ASM const char *pcre_version ( void );
SAVEDS ASM int pcre_info ( REG (a0 )const pcre *argument_re , REG (a1 )int *optptr , REG (a2 )int *first_byte );
SAVEDS ASM int pcre_fullinfo ( REG (a0 )const pcre *argument_re , REG (a1 )const pcre_extra *extra_data , REG (d0 )int what , REG (a2 )void *where );
SAVEDS ASM int pcre_config ( REG (d0 )int what , REG (a0 )void *where );
SAVEDS ASM pcre *pcre_compileA ( REG (a0 )const char *pattern , REG (a1 )int *errorptr , REG (a2 )int *erroroffset , REG (a3 )struct TagItem *attrs );
SAVEDS ASM int pcre_exec ( REG (a0 )const pcre *argument_re , REG (a1 )const pcre_extra *extra_data , REG (a2 )const char *subject , REG (d0 )int length , REG (d1 )int start_offset , REG (d2 )int options , REG (a3 )int *offsets , REG (d3 )int offsetcount );
SAVEDS ASM void pcre_free ( REG (a0 )pcre *re );
#endif

/* dispatch.c */
#ifdef __MORPHOS__
LONG dispatch ( void );
#endif

#endif /* _CLASS_PROTOS_H */
