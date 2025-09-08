
#include "lib.h"
#include "pcre.library_rev.h"

/****************************************************************************/

UBYTE                   lib_name[] = PRG;
UBYTE		        lib_ver[] = VSTRING;
UBYTE                   lib_fullName[] = PRGNAME;
ULONG                   lib_version = VERSION;
ULONG                   lib_revision = REVISION;

struct ExecBase         *SysBase = NULL;
struct DosLibrary       *DOSBase = NULL;
struct Library          *UtilityBase = NULL;
struct LocaleBase       *LocaleBase = NULL;
struct RxsLib           *RexxSysBase = NULL;

struct Library          *lib_base = NULL;
ULONG                   lib_segList = NULL;
struct SignalSemaphore  lib_sem = {0};
struct SignalSemaphore  lib_memSem = {0};
APTR                    lib_pool = NULL;
struct Catalog          *lib_cat = NULL;
struct Locale           *lib_locale = NULL;
ULONG                   lib_flags = 0;

unsigned char           *lib_pcre_default_tables = NULL;

/****************************************************************************/

#ifdef __MORPHOS__
#include <exec/resident.h>

static struct Library *initLib ( struct Library *base , BPTR segList , struct ExecBase *sys );
static struct Library *openLib ( void );
static ULONG expungeLib ( void );
static ULONG closeLib ( void );
static ULONG nil (void );

#pragma pack(2)
struct dataTable
{
	UBYTE ln_Type_Init[4];
	UBYTE ln_Pri_Init[4];
	UBYTE ln_Name_Init[2];
	ULONG ln_Name_Content;
	UBYTE lib_Flags_Init[4];
	UBYTE lib_Version_Init[2];
        UWORD lib_Version_Content;
	UBYTE lib_Revision_Init[2];
        UWORD lib_Revision_Content;
	UBYTE lib_IdString_Init[2];
	ULONG lib_IdString_Content;
	UWORD EndMark;
};
#pragma pack()

static const APTR funcTable[] =
{
        (APTR)   FUNCARRAY_BEGIN,
	(APTR)   FUNCARRAY_32BIT_NATIVE,
	(APTR)   openLib,
	(APTR)   closeLib,
	(APTR)   expungeLib,
	(APTR)   nil,
        (APTR)   0xffffffff,

        (APTR)   FUNCARRAY_32BIT_D0D1A0A1SR_NATIVE,
        (APTR)	 dispatch,
        (APTR)   0xffffffff,

	(APTR)   FUNCARRAY_32BIT_NATIVE,

        (APTR)   LIB_pcre_version,
        (APTR)   LIB_pcre_compileA,
        (APTR)   LIB_pcre_exec,

        (APTR)   LIB_pcre_study,
        (APTR)   LIB_pcre_info,
        (APTR)   LIB_pcre_fullinfo,
        (APTR)   LIB_pcre_config,

        (APTR)   LIB_pcre_get_stringnumber,
        (APTR)   LIB_pcre_copy_substring,
        (APTR)   LIB_pcre_copy_named_substring,
        (APTR)   LIB_pcre_get_substring_list,
        (APTR)   LIB_pcre_free_substring_list,
        (APTR)   LIB_pcre_get_substring,
        (APTR)   LIB_pcre_get_named_substring,
        (APTR)   LIB_pcre_free_substring,

        (APTR)   LIB_pcre_free,

        (APTR)   LIB_pcre_getstring,

        (APTR)   -1
};

static const struct dataTable dataTable	=
{
	0xa0,8,  NT_LIBRARY,0,
	0xa0,9,  0,0,
	0x80,10, (ULONG)lib_name,
	0xa0,14, LIBF_SUMUSED|LIBF_CHANGED,0,
	0x90,20, VERSION,
	0x90,22, REVISION,
	0x80,24, (ULONG)lib_ver,
	0
};

static const ULONG initTable[] =
{
	sizeof(struct Library),
	(ULONG)funcTable,
	(ULONG)&dataTable,
	(ULONG)initLib
};

const struct Resident romTag =
{
	RTC_MATCHWORD,
	(struct Resident *)&romTag,
	(struct Resident *)&romTag+1,
	RTF_AUTOINIT|RTF_PPC|RTF_EXTENDED,
	VERSION,
	NT_LIBRARY,
	0,
	(STRPTR)lib_name,
	(STRPTR)lib_ver,
	(APTR)initTable,
	REVISION,
        NULL
};

const ULONG __abox__	= 1;
#endif

/****************************************************************************/

#ifdef __MORPHOS__
static struct Library *initLib(struct Library *base,BPTR segList,struct ExecBase *sys)
#else
struct Library *SAVEDS ASM initLib(REG(a0) ULONG segList,REG(a6) APTR sys,REG(d0) struct Library *base)
#endif
{

#define SysBase sys
    InitSemaphore(&lib_sem);
    InitSemaphore(&lib_memSem);
#undef SysBase

    SysBase     = sys;
    lib_segList = segList;

    return lib_base = base;
}

/****************************************************************************/

#ifdef __MORPHOS__
static struct Library *openLib(void)
#else
struct Library * SAVEDS ASM openLib(REG(a6) struct Library *base)
#endif
{
#ifdef __MORPHOS__
	struct Library *base = (struct Library *)REG_A6;
#endif
    register struct Library *res;

    ObtainSemaphore(&lib_sem);

    base->lib_OpenCnt++;
    base->lib_Flags &= ~LIBF_DELEXP;

    if (!(lib_flags & BASEFLG_Init) && !initBase())
    {
        base->lib_OpenCnt--;
        res = NULL;
    }
    else res = base;

    ReleaseSemaphore(&lib_sem);

    return res;
}

/****************************************************************************/

#ifdef __MORPHOS__
static ULONG expungeLib(void)
#else
ULONG SAVEDS ASM expungeLib(REG(a6) struct Library *base)
#endif
{
#ifdef __MORPHOS__
    struct Library *base = (struct Library *)REG_A6;
#endif
    register ULONG res;

    ObtainSemaphore(&lib_sem);

    if (!base->lib_OpenCnt)
    {
        Remove((struct Node *)base);
        FreeMem((UBYTE *)base-base->lib_NegSize,base->lib_NegSize+base->lib_PosSize);

        res = lib_segList;
    }
    else
    {
        base->lib_Flags |= LIBF_DELEXP;
        res = NULL;
    }

    ReleaseSemaphore(&lib_sem);

    return res;
}

/****************************************************************************/

#ifdef __MORPHOS__
static ULONG closeLib(void)
#else
ULONG SAVEDS ASM closeLib(REG(a6) struct Library *base)
#endif
{
#ifdef __MORPHOS__
    struct Library *base = (struct Library *)REG_A6;
#endif
    register ULONG res = NULL;

    ObtainSemaphore(&lib_sem);

    if (!--base->lib_OpenCnt)
    {
        freeBase();

        if (base->lib_Flags & LIBF_DELEXP)
	{
            Remove((struct Node *)base);
    	    FreeMem((UBYTE *)base-base->lib_NegSize,base->lib_NegSize+base->lib_PosSize);

            res = lib_segList;
	}
    }

    ReleaseSemaphore(&lib_sem);

    return res;
}

/****************************************************************************/

#ifdef __MORPHOS__
static ULONG nil(void)
{
    return 0;
}
#endif

/****************************************************************************/
