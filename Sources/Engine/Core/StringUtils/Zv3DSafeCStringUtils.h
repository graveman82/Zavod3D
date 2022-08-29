/*
-----------------
 Persistent info
-----------------
(C) 2012-2022 Zavod3D project. Marat Sungatullin

.........
License:
.........

is in the "LICENSE" file.

......
 Web:
......

 + https://gamedev.ru/community/trash_team/forum/?id=192020 (for questions and help)

------
 Desc
------
Purpose: safe strung utils prototypes.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_STRINGUTILS_SAFECSTRINGUTILS_H
#define ZV3D_CORE_STRINGUTILS_SAFECSTRINGUTILS_H


#include "Core/Platform/Zv3DTypes.h"

ZvdSize __cdecl ZvdSafeStrLen(const char* str);

char*   __cdecl ZvdSafeStrCpy(char *dest, const char *src, ZvdSize* pLen = kZVD_NULL);
// 'R' - ranged version
char*   __cdecl ZvdSafeStrCpyR(char *dst, const char *src, const char* strE);
int     __cdecl ZvdSafeStrCmp(const char* str1, const char* str2);

const char*   __cdecl ZvdSafeStrChr (const char* str, char ch, ZvdSize* pLen = kZVD_NULL);
// 'R' - ranged version
const char*   __cdecl ZvdSafeStrChrR(const char* str, const char* strE, char ch);

#endif // ZV3D_CORE_STRINGUTILS_SAFECSTRINGUTILS_H

