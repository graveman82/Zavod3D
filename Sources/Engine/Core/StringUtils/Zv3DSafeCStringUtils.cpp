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
Purpose: safe strung utils prototypes.(implementation).

----------------------
 for developers notes
----------------------

*/

#include "Core/StringUtils/Zv3DSafeCStringUtils.h"
#include "Core/Debug/Zv3DAssert.h"
#include "Core/Utils/Zv3DSmallCommonUtils.h"
#include "Core/MemMng/Zv3DMemDefs.h"
#include "Core/MemMng/Zv3DMemUtils.h"



#define kZVD_MAX_SAFE_CSTRING_SIZE kZVD_SHARED_STATIC_BUFFER_SIZE

// Returns true and set "len" to length of specified string if it is null-terminated.
/* Для строки, расположенной в пределах статичного разделяемого буфера, проверка не
выходит за пределы этого буфера.
*/
static bool ZvdIsNullTerminated(const char* str, ZvdSize& len)
{
    if (!str)
        return false;

    ZvdSize nCheckedSize = kZVD_MAX_SAFE_CSTRING_SIZE;
    if (str >= (const char*)ZvdGetSharedStaticBuffer() && str < (const char*)ZvdGetSharedStaticBufferEnd())
    {
        nCheckedSize = (const char*)ZvdGetSharedStaticBufferEnd() - str;
    }
    const char* const str0 = str;
    const char* const strE = str + nCheckedSize;
    while (str < strE)
    {
        if (!*str)
        {
            // '\0' -- fount end of C string
            len = str - str0;
            return true;
        }
        ++str;
    }
    return false;
}

//-----------------------------------------------------------------------------

ZvdSize __cdecl ZvdSafeStrLen(const char* str)
{
    ZvdSize len = 0;
    if (!ZvdIsNullTerminated(str, len))
        return 0;
    return len;
}

//-----------------------------------------------------------------------------

char* __cdecl ZvdSafeStrCpy(char *dst, const char *src, ZvdSize* pLen)
{
    ZVD_ASSERT_HIGH(dst, ZVD_DEBUG_EMPTY_TEXT);

    ZvdSize len = 0;
    if (!ZvdIsNullTerminated(src, len))
    {
        if (pLen)
            *pLen = 0;
        return dst;
    }

    if (pLen)
        *pLen = len;

    dst[len] = 0;
    while (len--)
    {
        dst[len] = src[len];
    }
    return dst;
}

//-----------------------------------------------------------------------------

char* __cdecl ZvdSafeStrCpyR(char *dst, const char *src, const char* srcE)
{
    ZVD_ASSERT_HIGH(dst, ZVD_DEBUG_EMPTY_TEXT);
    if (!src)
        return dst;

    char* dst0 = dst;
    while (src < srcE)
    {
        *dst++ = *src++;
    }
    *dst = 0;
    return dst0;
}

//-----------------------------------------------------------------------------

int __cdecl ZvdSafeStrCmp (const char* str1, const char* str2)
{
    ZvdSize len1 = 0;
    bool nt1 = ZvdIsNullTerminated(str1, len1);
    ZvdSize len2 = 0;
    bool nt2 = ZvdIsNullTerminated(str2, len2);

    ZVD_ASSERT_HIGH(nt1, ZVD_DEBUG_EMPTY_TEXT);
    ZVD_ASSERT_HIGH(nt2, ZVD_DEBUG_EMPTY_TEXT);

    if (len1 > len2)
        return 1;
    else if (len1 < len2)
        return -1;

    ZvdSize len = len1;

    int rslt = 0;

    for (ZvdIndex i = 0; (ZvdSize)i < len; ++i)
    {
        rslt = int((ZvdByte)str1[i] - (ZvdByte)str2[i]);
        if (rslt)
            break;

    }

    if (rslt < 0)
        rslt = -1;
    else if (rslt > 0)
        rslt = 1;

    return rslt;
}

//-----------------------------------------------------------------------------
const char* __cdecl ZvdSafeStrChr (const char* str, char ch, ZvdSize* pLen)
{
    ZvdSize len = 0;
    if (!ZvdIsNullTerminated(str, len))
    {
        if (pLen)
            *pLen = 0;
        return kZVD_NULL;
    }

    if (pLen)
        *pLen = len;

    for (ZvdIndex i = 0; (ZvdSize)i < len; ++i)
    {
        if (str[i] == ch)
            return &str[i];
    }
    return kZVD_NULL;
}

//-----------------------------------------------------------------------------
const char* __cdecl ZvdSafeStrChrR (const char* str, const char* strE, char ch)
{
    if (!str)
        return kZVD_NULL;

    while (str < strE)
    {
        if (*str == ch)
            return str;
        ++str;
    }
    return kZVD_NULL;
}
