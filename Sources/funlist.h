
/**************************************************************************************/

#ifdef __MORPHOS__
extern LONG help(struct header *,STRPTR *,struct RexxMsg *,struct resultBox *);
extern LONG xwz309(struct header *,STRPTR *,struct RexxMsg *,struct resultBox *);
extern LONG pcrematch(struct header *,STRPTR *,struct RexxMsg *,struct resultBox *);
#else
/*extern LONG ASM help(REG(a0) struct header *,REG(a1) STRPTR *,REG(a2) struct RexxMsg *,REG(a3) struct resultBox *);
extern LONG ASM xwz309(REG(a0) struct header *,REG(a1) STRPTR *,REG(a2) struct RexxMsg *,REG(a3) struct resultBox *);
extern LONG ASM pcrematch(REG(a0) struct header *,REG(a1) STRPTR *,REG(a2) struct RexxMsg *,REG(a3) struct resultBox *);
#endif*/

extern rexxFunction help,
                    xwz309,
                    pcrematch;
#endif

/**************************************************************************************/

functionElement functionList[] =
{
    { "HELP",                 FH_F,   "D",                "<fun>",                                                        help },
    { "PCREMATCH",            FH_F,   "DDV",              "<re>,<str>,<stem/V>",                                          pcrematch },
    { "pcre_xwz309",          FH_F,   "",                 "",                                                             xwz309 },
};

/**************************************************************************************/
