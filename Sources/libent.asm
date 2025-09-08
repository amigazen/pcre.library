
        SECTION pcre,CODE

        NOLIST

        INCLUDE "pcre.library_rev.i"
        INCLUDE "exec/libraries.i"
        INCLUDE "exec/resident.i"
        INCLUDE "exec/initializers.i"
        INCLUDE "exec/lists.i"
        INCLUDE "exec/semaphores.i"

        LIST

        XREF    _LinkerDB
        XREF    _lib_name
        XREF    ENDCODE

        XREF    _initLib
        XREF    _openLib
        XREF    _expungeLib
        XREF    _closeLib

        XREF    _dispatch

        XREF    _pcre_version
        XREF    _pcre_info
        XREF    _pcre_fullinfo
        XREF    _pcre_config
        XREF    _pcre_compileA
        XREF    _pcre_exec

        XREF    _pcre_study

        XREF    _pcre_get_stringnumber
        XREF    _pcre_copy_substring
        XREF    _pcre_copy_named_substring
        XREF    _pcre_get_substring_list
        XREF    _pcre_free_substring_list
        XREF    _pcre_get_substring
        XREF    _pcre_get_named_substring
        XREF    _pcre_free_substring

        XREF    _pcre_free

        XREF    _pcre_getstring

        XDEF    _ID

PRI     EQU 0

start:  moveq   #-1,d0
        rts

romtag:
        dc.w    RTC_MATCHWORD
        dc.l    romtag
        dc.l    ENDCODE
        dc.b    RTF_AUTOINIT
        dc.b    VERSION
        dc.b    NT_LIBRARY
        dc.b    PRI
        dc.l    _lib_name
        dc.l    _ID
        dc.l    init

_ID:    VSTRING

        CNOP    0,4

init:   dc.l    LIB_SIZE
        dc.l    funcTable
        dc.l    dataTable
        dc.l    _initLib

funcTable:
        dc.l    _openLib
        dc.l    _closeLib
        dc.l    _expungeLib
        dc.l    nil

        dc.l    query

        dc.l    _pcre_version
        dc.l    _pcre_compileA
        dc.l    _pcre_exec

        dc.l    _pcre_study
        dc.l    _pcre_info
        dc.l    _pcre_fullinfo
        dc.l    _pcre_config

        dc.l    _pcre_get_stringnumber
        dc.l    _pcre_copy_substring
        dc.l    _pcre_copy_named_substring
        dc.l    _pcre_get_substring_list
        dc.l    _pcre_free_substring_list
        dc.l    _pcre_get_substring
        dc.l    _pcre_get_named_substring
        dc.l    _pcre_free_substring

        dc.l    _pcre_free

        dc.l    _pcre_getstring

        dc.l    -1

dataTable:
        INITBYTE LN_TYPE,NT_LIBRARY
        INITLONG LN_NAME,_lib_name
        INITBYTE LIB_FLAGS,(LIBF_SUMUSED!LIBF_CHANGED)
        INITWORD LIB_VERSION,VERSION
        INITWORD LIB_REVISION,REVISION
        INITLONG LIB_IDSTRING,_ID
        dc.w     0

        CNOP    0,4

nil:    moveq   #0,d0
        rts

query:  movem.l a1/a4,-(sp)
        lea     _LinkerDB,a4
        subq.l  #4,sp
        movea.l sp,a1
        bsr     _dispatch
        movem.l (sp)+,a0/a1/a4
        rts

        END
