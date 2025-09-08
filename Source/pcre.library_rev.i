VERSION EQU 0
REVISION EQU 2
DATE MACRO
    dc.b '7.11.2004'
    ENDM
VERS MACRO
    dc.b 'pcre.library 0.2'
    ENDM
VSTRING MACRO
    dc.b 'pcre.library 0.2 (7.11.2004)',13,10,0
    ENDM
VERSTAG MACRO
    dc.b 0,'$VER: pcre.library 0.2 (7.11.2004)',0
    ENDM
