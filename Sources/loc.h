#ifndef LOC_H
#define LOC_H


/****************************************************************************/


/* This file was created automatically by CatComp.
 * Do NOT edit by hand!
 */


#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifdef CATCOMP_ARRAY
#undef CATCOMP_NUMBERS
#undef CATCOMP_STRINGS
#define CATCOMP_NUMBERS
#define CATCOMP_STRINGS
#endif

#ifdef CATCOMP_BLOCK
#undef CATCOMP_STRINGS
#define CATCOMP_STRINGS
#endif


/****************************************************************************/


#ifdef CATCOMP_NUMBERS

#define CERR1 1
#define CERR2 2
#define CERR3 3
#define CERR4 4
#define CERR5 5
#define CERR6 6
#define CERR7 7
#define CERR8 8
#define CERR9 9
#define CERR10 10
#define CERR11 11
#define CERR12 12
#define CERR13 13
#define CERR14 14
#define CERR15 15
#define CERR16 16
#define CERR17 17
#define CERR18 18
#define CERR19 19
#define CERR20 20
#define CERR21 21
#define CERR22 22
#define CERR23 23
#define CERR24 24
#define CERR25 25
#define CERR26 26
#define CERR27 27
#define CERR28 28
#define CERR29 29
#define CERR30 30
#define CERR31 31
#define CERR32 32
#define CERR33 33
#define CERR34 34
#define CERR35 35
#define CERR36 36
#define CERR37 37
#define CERR38 38
#define CERR39 39
#define CERR40 40
#define CERR41 41
#define CERR42 42
#define CERR43 43
#define CERR44 44
#define CERR45 45
#define CERR46 46
#define CERR47 47
#define CERRSTUDY100 100
#define CERRSTUDY101 101
#define CERRSTUDY102 102

#endif /* CATCOMP_NUMBERS */


/****************************************************************************/


#ifdef CATCOMP_STRINGS

#define CERR1_STR "\\ at end of pattern"
#define CERR2_STR "\\c at end of pattern"
#define CERR3_STR "unrecognized character follows \\"
#define CERR4_STR "numbers out of order in {} quantifier"
#define CERR5_STR "number too big in {} quantifier"
#define CERR6_STR "missing terminating ] for character class"
#define CERR7_STR "invalid escape sequence in character class"
#define CERR8_STR "range out of order in character class"
#define CERR9_STR "nothing to repeat"
#define CERR10_STR "operand of unlimited repeat could match the empty string"
#define CERR11_STR "internal error: unexpected repeat"
#define CERR12_STR "unrecognized character after (?"
#define CERR13_STR "POSIX named classes are supported only within a class"
#define CERR14_STR "missing )"
#define CERR15_STR "reference to non-existent subpattern"
#define CERR16_STR "erroffset passed as NULL"
#define CERR17_STR "unknown option bit(s) set"
#define CERR18_STR "missing ) after comment"
#define CERR19_STR "parentheses nested too deeply"
#define CERR20_STR "regular expression too large"
#define CERR21_STR "failed to get memory"
#define CERR22_STR "unmatched parentheses"
#define CERR23_STR "internal error: code overflow"
#define CERR24_STR "unrecognized character after (?<"
#define CERR25_STR "lookbehind assertion is not fixed length"
#define CERR26_STR "malformed number after (?("
#define CERR27_STR "conditional group contains more than two branches"
#define CERR28_STR "assertion expected after (?("
#define CERR29_STR "(?R or (?digits must be followed by )"
#define CERR30_STR "unknown POSIX class name"
#define CERR31_STR "POSIX collating elements are not supported"
#define CERR32_STR "this version of PCRE is not compiled with PCRE_UTF8 support"
#define CERR33_STR "spare error"
#define CERR34_STR "character value in \\x{...} sequence is too large"
#define CERR35_STR "invalid condition (?(0)"
#define CERR36_STR "\\C not allowed in lookbehind assertion"
#define CERR37_STR "PCRE does not support \\L, \\l, \\N, \\U, or \\u"
#define CERR38_STR "number after (?C is > 255"
#define CERR39_STR "closing ) for (?C expected"
#define CERR40_STR "recursive call could loop indefinitely"
#define CERR41_STR "unrecognized character after (?P"
#define CERR42_STR "syntax error after (?P"
#define CERR43_STR "two named groups have the same name"
#define CERR44_STR "invalid UTF-8 string"
#define CERR45_STR "support for \\P, \\p, and \\X has not been compiled"
#define CERR46_STR "malformed \\P or \\p sequence"
#define CERR47_STR "unknown property name after \\P or \\p"
#define CERRSTUDY100_STR "argument is not a compiled regular expression"
#define CERRSTUDY101_STR "unknown or incorrect option bit(s) set"
#define CERRSTUDY102_STR "failed to get memory"

#endif /* CATCOMP_STRINGS */


/****************************************************************************/


#ifdef CATCOMP_ARRAY

struct CatCompArrayType
{
    LONG   cca_ID;
    STRPTR cca_Str;
};

static const struct CatCompArrayType CatCompArray[] =
{
    {CERR1,(STRPTR)CERR1_STR},
    {CERR2,(STRPTR)CERR2_STR},
    {CERR3,(STRPTR)CERR3_STR},
    {CERR4,(STRPTR)CERR4_STR},
    {CERR5,(STRPTR)CERR5_STR},
    {CERR6,(STRPTR)CERR6_STR},
    {CERR7,(STRPTR)CERR7_STR},
    {CERR8,(STRPTR)CERR8_STR},
    {CERR9,(STRPTR)CERR9_STR},
    {CERR10,(STRPTR)CERR10_STR},
    {CERR11,(STRPTR)CERR11_STR},
    {CERR12,(STRPTR)CERR12_STR},
    {CERR13,(STRPTR)CERR13_STR},
    {CERR14,(STRPTR)CERR14_STR},
    {CERR15,(STRPTR)CERR15_STR},
    {CERR16,(STRPTR)CERR16_STR},
    {CERR17,(STRPTR)CERR17_STR},
    {CERR18,(STRPTR)CERR18_STR},
    {CERR19,(STRPTR)CERR19_STR},
    {CERR20,(STRPTR)CERR20_STR},
    {CERR21,(STRPTR)CERR21_STR},
    {CERR22,(STRPTR)CERR22_STR},
    {CERR23,(STRPTR)CERR23_STR},
    {CERR24,(STRPTR)CERR24_STR},
    {CERR25,(STRPTR)CERR25_STR},
    {CERR26,(STRPTR)CERR26_STR},
    {CERR27,(STRPTR)CERR27_STR},
    {CERR28,(STRPTR)CERR28_STR},
    {CERR29,(STRPTR)CERR29_STR},
    {CERR30,(STRPTR)CERR30_STR},
    {CERR31,(STRPTR)CERR31_STR},
    {CERR32,(STRPTR)CERR32_STR},
    {CERR33,(STRPTR)CERR33_STR},
    {CERR34,(STRPTR)CERR34_STR},
    {CERR35,(STRPTR)CERR35_STR},
    {CERR36,(STRPTR)CERR36_STR},
    {CERR37,(STRPTR)CERR37_STR},
    {CERR38,(STRPTR)CERR38_STR},
    {CERR39,(STRPTR)CERR39_STR},
    {CERR40,(STRPTR)CERR40_STR},
    {CERR41,(STRPTR)CERR41_STR},
    {CERR42,(STRPTR)CERR42_STR},
    {CERR43,(STRPTR)CERR43_STR},
    {CERR44,(STRPTR)CERR44_STR},
    {CERR45,(STRPTR)CERR45_STR},
    {CERR46,(STRPTR)CERR46_STR},
    {CERR47,(STRPTR)CERR47_STR},
    {CERRSTUDY100,(STRPTR)CERRSTUDY100_STR},
    {CERRSTUDY101,(STRPTR)CERRSTUDY101_STR},
    {CERRSTUDY102,(STRPTR)CERRSTUDY102_STR},
};

#endif /* CATCOMP_ARRAY */


/****************************************************************************/


#ifdef CATCOMP_BLOCK

static const char CatCompBlock[] =
{
    "\x00\x00\x00\x01\x00\x14"
    CERR1_STR "\x00"
    "\x00\x00\x00\x02\x00\x16"
    CERR2_STR "\x00\x00"
    "\x00\x00\x00\x03\x00\x22"
    CERR3_STR "\x00\x00"
    "\x00\x00\x00\x04\x00\x26"
    CERR4_STR "\x00"
    "\x00\x00\x00\x05\x00\x20"
    CERR5_STR "\x00"
    "\x00\x00\x00\x06\x00\x2A"
    CERR6_STR "\x00"
    "\x00\x00\x00\x07\x00\x2C"
    CERR7_STR "\x00\x00"
    "\x00\x00\x00\x08\x00\x26"
    CERR8_STR "\x00"
    "\x00\x00\x00\x09\x00\x12"
    CERR9_STR "\x00"
    "\x00\x00\x00\x0A\x00\x3A"
    CERR10_STR "\x00\x00"
    "\x00\x00\x00\x0B\x00\x22"
    CERR11_STR "\x00"
    "\x00\x00\x00\x0C\x00\x20"
    CERR12_STR "\x00"
    "\x00\x00\x00\x0D\x00\x36"
    CERR13_STR "\x00"
    "\x00\x00\x00\x0E\x00\x0A"
    CERR14_STR "\x00"
    "\x00\x00\x00\x0F\x00\x26"
    CERR15_STR "\x00\x00"
    "\x00\x00\x00\x10\x00\x1A"
    CERR16_STR "\x00\x00"
    "\x00\x00\x00\x11\x00\x1A"
    CERR17_STR "\x00"
    "\x00\x00\x00\x12\x00\x18"
    CERR18_STR "\x00"
    "\x00\x00\x00\x13\x00\x1E"
    CERR19_STR "\x00"
    "\x00\x00\x00\x14\x00\x1E"
    CERR20_STR "\x00\x00"
    "\x00\x00\x00\x15\x00\x16"
    CERR21_STR "\x00\x00"
    "\x00\x00\x00\x16\x00\x16"
    CERR22_STR "\x00"
    "\x00\x00\x00\x17\x00\x1E"
    CERR23_STR "\x00"
    "\x00\x00\x00\x18\x00\x22"
    CERR24_STR "\x00\x00"
    "\x00\x00\x00\x19\x00\x2A"
    CERR25_STR "\x00\x00"
    "\x00\x00\x00\x1A\x00\x1C"
    CERR26_STR "\x00\x00"
    "\x00\x00\x00\x1B\x00\x32"
    CERR27_STR "\x00"
    "\x00\x00\x00\x1C\x00\x1E"
    CERR28_STR "\x00\x00"
    "\x00\x00\x00\x1D\x00\x26"
    CERR29_STR "\x00"
    "\x00\x00\x00\x1E\x00\x1A"
    CERR30_STR "\x00\x00"
    "\x00\x00\x00\x1F\x00\x2C"
    CERR31_STR "\x00\x00"
    "\x00\x00\x00\x20\x00\x3C"
    CERR32_STR "\x00"
    "\x00\x00\x00\x21\x00\x0C"
    CERR33_STR "\x00"
    "\x00\x00\x00\x22\x00\x32"
    CERR34_STR "\x00\x00"
    "\x00\x00\x00\x23\x00\x18"
    CERR35_STR "\x00"
    "\x00\x00\x00\x24\x00\x28"
    CERR36_STR "\x00\x00"
    "\x00\x00\x00\x25\x00\x2C"
    CERR37_STR "\x00"
    "\x00\x00\x00\x26\x00\x1A"
    CERR38_STR "\x00"
    "\x00\x00\x00\x27\x00\x1C"
    CERR39_STR "\x00\x00"
    "\x00\x00\x00\x28\x00\x28"
    CERR40_STR "\x00\x00"
    "\x00\x00\x00\x29\x00\x22"
    CERR41_STR "\x00\x00"
    "\x00\x00\x00\x2A\x00\x18"
    CERR42_STR "\x00\x00"
    "\x00\x00\x00\x2B\x00\x24"
    CERR43_STR "\x00"
    "\x00\x00\x00\x2C\x00\x16"
    CERR44_STR "\x00\x00"
    "\x00\x00\x00\x2D\x00\x32"
    CERR45_STR "\x00\x00"
    "\x00\x00\x00\x2E\x00\x1C"
    CERR46_STR "\x00"
    "\x00\x00\x00\x2F\x00\x26"
    CERR47_STR "\x00\x00"
    "\x00\x00\x00\x64\x00\x2E"
    CERRSTUDY100_STR "\x00"
    "\x00\x00\x00\x65\x00\x28"
    CERRSTUDY101_STR "\x00\x00"
    "\x00\x00\x00\x66\x00\x16"
    CERRSTUDY102_STR "\x00\x00"
};

#endif /* CATCOMP_BLOCK */


/****************************************************************************/


struct LocaleInfo
{
    APTR li_LocaleBase;
    APTR li_Catalog;
};


#ifdef CATCOMP_CODE

STRPTR GetString(struct LocaleInfo *li, LONG stringNum)
{
LONG   *l;
UWORD  *w;
STRPTR  builtIn;

    l = (LONG *)CatCompBlock;

    while (*l != stringNum)
    {
        w = (UWORD *)((ULONG)l + 4);
        l = (LONG *)((ULONG)l + (ULONG)*w + 6);
    }
    builtIn = (STRPTR)((ULONG)l + 6);

#undef LocaleBase
#define LocaleBase li->li_LocaleBase
    
    if (LocaleBase)
        return(GetCatalogStr(li->li_Catalog,stringNum,builtIn));
#undef LocaleBase

    return(builtIn);
}


#endif /* CATCOMP_CODE */


/****************************************************************************/


#endif /* LOC_H */
