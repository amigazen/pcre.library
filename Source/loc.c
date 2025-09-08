
#define CATCOMP_ARRAY
#include "lib.h"

/****************************************************************************/

struct Catalog *
openCatalog(STRPTR name,ULONG minVer,ULONG minRev)
{
    register struct Catalog *cat;

    if (cat = OpenCatalogA(NULL,name,NULL))
    {
        register ULONG ver = cat->cat_Version;

        if ((ver<minVer) ? TRUE : ((ver==minVer) ? (cat->cat_Revision<minRev) : FALSE))
        {
            CloseCatalog(cat);
            cat = NULL;
        }
    }

    return cat;
}

/***********************************************************************/

#ifdef __MORPHOS__
STRPTR pcre_getstring(ULONG id)
#else
STRPTR SAVEDS ASM pcre_getstring(REG(d0) ULONG id)
#endif
{
    register struct CatCompArrayType    *cca;
    register int                        cnt;

    for (cnt = (sizeof(CatCompArray)/sizeof(struct CatCompArrayType))-1, cca = (struct CatCompArrayType *)CatCompArray+cnt;
         (cnt>=0) && (id!=cca->cca_ID);
         cnt--, cca--);

    return (cnt>=0) ? (lib_cat ? GetCatalogStr(lib_cat,id,cca->cca_Str) : cca->cca_Str) : NULL;
}

#ifdef __MORPHOS__
STRPTR LIB_pcre_getstring(void)
{
    return pcre_getstring((ULONG)REG_D0);
}

#endif


/***********************************************************************/

#ifndef __MORPHOS__
RXLFUN(pcreGetString)
{
    register char *string;

    if (!(string = pcre_getstring((LONG)argv[0])))
        string = "";

    return (result->value.argString = CreateArgstring(string,strlen(string))) ?
        TYPE_ArgString : 3;
}
#endif

/****************************************************************************/

