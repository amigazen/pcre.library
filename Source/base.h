#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

#include "macros.h"

/***************************************************************************/

extern UBYTE                   lib_name[];
extern UBYTE	               lib_ver[];
extern UBYTE                   lib_fullName[];
extern ULONG                   lib_version;
extern ULONG                   lib_revision;

extern struct ExecBase         *SysBase;
extern struct DosLibrary       *DOSBase;
extern struct Library          *UtilityBase;
extern struct LocaleBase       *LocaleBase;
extern struct RxsLib           *RexxSysBase;

extern struct SignalSemaphore  lib_sem;
extern struct SignalSemaphore  lib_memSem;
extern struct Library          *lib_base;
extern ULONG                   lib_segList;
extern APTR                    lib_pool;
extern struct Catalog          *lib_cat;
extern struct Locale           *lib_locale;
extern ULONG                   lib_flags;

extern unsigned char           *lib_pcre_default_tables;

/***************************************************************************/

enum
{
    BASEFLG_Init  = 1<<0,
};

/***************************************************************************/

