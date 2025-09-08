#ifndef _LIB_H
#define _LIB_H

#define __NOLIBBASE__
#define __USE_SYSBASE

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/utility.h>
#include <proto/locale.h>
#include <proto/rexx.h>

#include <clib/alib_protos.h>
#include <clib/debug_protos.h>

#include <utility/pack.h>
#include <rexx/rexxlibrary.h>

#include <dos.h>
#include <string.h>

#define CATCOMP_NUMBERS
#include "loc.h"

#include "base.h"
#include "internal.h"

/***********************************************************************/

extern char LIBNAME[];

/***********************************************************************/

enum
{
    PCREA_Options = (int)TAG_USER+1,
    PCREA_Table,
    PCREA_MallocHook,
    PCREA_FreeHook,
    PCREA_CalloutHook,
    PCREA_Pool,
    PCREA_PoolSem,
};

/***********************************************************************/

#include "lib_protos.h"

/***********************************************************************/

#endif /* _LIB_H */
