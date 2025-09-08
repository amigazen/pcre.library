
#include "lib.h"

/***********************************************************************/

void
freeBase(void)
{
    if (lib_pool)
    {
        DeletePool(lib_pool);
        lib_pool = NULL;
    }

    if (RexxSysBase)
    {
        CloseLibrary((struct Library *)RexxSysBase);
        RexxSysBase = NULL;
    }

    if (LocaleBase)
    {
        if (lib_cat)
        {
            CloseCatalog(lib_cat);
            lib_cat = NULL;
        }

        if (lib_locale)
        {
            CloseLocale(lib_locale);
            lib_locale = NULL;
        }

        CloseLibrary((struct Library *)LocaleBase);
        LocaleBase = NULL;
    }

    if (UtilityBase)
    {
        CloseLibrary(UtilityBase);
        UtilityBase = NULL;
    }

    if (DOSBase)
    {
        CloseLibrary((struct Library *)DOSBase);
        DOSBase = NULL;
    }

    lib_flags &= ~BASEFLG_Init;
}

/***********************************************************************/

#define CATNAME "pcre.catalog"

ULONG
initBase(void)
{
    if ((DOSBase = (struct DosLibrary *)OpenLibrary("dos.library",37)) &&
        (UtilityBase = OpenLibrary("utility.library",37)) &&
        (LocaleBase = (struct LocaleBase *)OpenLibrary("locale.library",37)) &&
        (RexxSysBase = (struct RxsLib *)OpenLibrary("rexxsyslib.library",0L)) &&
        (lib_locale = OpenLocale(NULL)) &&
        (lib_pool = CreatePool(MEMF_ANY|MEMF_CLEAR,4096,1024)) &&
        (lib_pcre_default_tables = pcre_maketables(NULL)))
    {
        lib_cat = openCatalog(CATNAME,0,0);

        lib_flags |= BASEFLG_Init;

        return TRUE;
    }

    freeBase();

    return FALSE;
}

/***********************************************************************/
