#ifndef PRAGMAS_PCRE_PRAGMAS_H
#define PRAGMAS_PCRE_PRAGMAS_H

/*
**  $VER: pcre_pragmas.h 1.0 (19.10.2004)
**  Includes Release 1.0
**
**  Written by Alfonso [alfie] Ranieri <alforan@tin.it>.
**
**  Released under the terms of the
**  GNU Public Licence version 2.
*/

#ifndef CLIB_PCRE_PROTOS_H
#include <clib/pcre_protos.h>
#endif

#if defined(AZTEC_C) || defined(__MAXON__) || defined(__STORM__)
#pragma amicall(PCREBase,0x024,PCREVersion())
#pragma amicall(PCREBase,0x02a,PCRECompileA(a0,a1,a2,a3))
#pragma amicall(PCREBase,0x030,PCREExec(a0,a1,a2,d0,d1,d2,a3,d3))
#pragma amicall(PCREBase,0x036,PCREStudy(a0,d0,a1))
#pragma amicall(PCREBase,0x03c,PCREInfo(a0,a1,a2))
#pragma amicall(PCREBase,0x042,PCREFulliNfo(a0,a1,d0,a2))
#pragma amicall(PCREBase,0x048,PCREConfig(d0,a0))
#pragma amicall(PCREBase,0x04e,PCREGetStringNumber(a0,a1))
#pragma amicall(PCREBase,0x054,PCRECopySubString(a0,a1,d0,d1,a2,d2))
#pragma amicall(PCREBase,0x05a,PCRECopyNamedSubstring(a0,a1,a2,d0,a3,d1,d2))
#pragma amicall(PCREBase,0x060,PCREGetSubstring_list(a0,a1,d0,a2))
#pragma amicall(PCREBase,0x066,PCREFreeSubstringList(a0))
#pragma amicall(PCREBase,0x06c,PCREGetSubString(a0,a1,d0,d1,a2))
#pragma amicall(PCREBase,0x072,PCREGetNamedSubString(a0,a1,a2,d0,a3,d1))
#pragma amicall(PCREBase,0x078,PCREFreeSubString(a0))
#pragma amicall(PCREBase,0x07e,PCREFree(a0))
#pragma amicall(PCREBase,0x084,PCREGetString(d0))
#endif
#if defined(_DCC) || defined(__SASC)
#pragma  libcall PCREBase PCREVersion               024 00
#pragma  libcall PCREBase PCRECompileA              02a ba9804
#pragma  libcall PCREBase PCREExec                  030 3b210a9808
#pragma  libcall PCREBase PCREStudy                 036 90803
#pragma  libcall PCREBase PCREInfo                  03c a9803
#pragma  libcall PCREBase PCREFullInfo              042 a09804
#pragma  libcall PCREBase PCREConfig                048 8002
#pragma  libcall PCREBase PCREGetStringNumber       04e 9802
#pragma  libcall PCREBase PCRECopySubString         054 2a109806
#pragma  libcall PCREBase PCRECopyNamedSubString    05a 21b0a9807
#pragma  libcall PCREBase PCREGetSubStringList      060 a09804
#pragma  libcall PCREBase PCREFreeSubStringList     066 801
#pragma  libcall PCREBase PCREGetSubString          06c a109805
#pragma  libcall PCREBase PCREGetNamedSubString     072 1b0a9806
#pragma  libcall PCREBase PCREFreeSubString         078 801
#pragma  libcall PCREBase PCREFree                  07e 801
#pragma  libcall PCREBase PCREGetString             084 001
#endif
#ifdef __STORM__
#pragma tagcall(PCREBase,0x02a,PCRECompile(a0,a1,a2,a3))
#endif
#ifdef __SASC_60
#pragma  tagcall PCREBase PCRECompile               02a ba9804
#endif

#endif /* PRAGMAS_PCRE_PRAGMAS_H */
