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
Purpose: memory operations (implementation).

----------------------
 for developers notes
----------------------

*/

#include "Core/MemMng/Zv3DMemDefs.h"
#include "Core/MemMng/Zv3DMemUtils.h"
#include "Core/Debug/Zv3DAssert.h"
#include "Core/Utils/Zv3DSmallCommonUtils.h"

//-----------------------------------------------------------------------------
// Conditional headers
#ifdef ZVD_USED_CPPSTD
// cpp std based -- {

// } -- end of cpp std based
#else
// crt based -- {
#include <stdlib.h>
#include <string.h>

// } -- end of crt based
#endif // ZVD_USED_CPPSTD

//*****************************************************************************
// Implementation
//*****************************************************************************


//=============================================================================
// Static shared buffer related
//=============================================================================

namespace zvdMemMngPrivate
{

ZvdByte sSharedStaticBuffer[kZVD_SHARED_STATIC_BUFFER_SIZE + sizeof(ZvdUint32)];

static const ZvdUint32 kSHARED_STATIC_BUFFER_ENDCODE = ZVD_FOURCC('Z', 'v', '3', 'D');

void SetSharedStaticBufferEndCode()
{
    const ZvdUint32* pCode = reinterpret_cast<const ZvdUint32*>(ZvdGetSharedStaticBufferEnd());
    *(const_cast<ZvdUint32*>(pCode)) = kSHARED_STATIC_BUFFER_ENDCODE;
}

ZvdUint32 GetSharedStaticBufferEndCode()
{
    const ZvdUint32* pCode = reinterpret_cast<const ZvdUint32*>(ZvdGetSharedStaticBufferEnd());
    return *pCode;
}

static ZvdNotEnoughMemoryHandler_t sNotEnoughMemoryHandler = kZVD_NULL;
} // end of zvdPrivate

//-----------------------------------------------------------------------------
const ZvdByte* ZvdGetSharedStaticBufferEnd()
{
    return &zvdMemMngPrivate::sSharedStaticBuffer[0] + kZVD_SHARED_STATIC_BUFFER_SIZE;
}

//-----------------------------------------------------------------------------

ZvdByte* ZvdGetSharedStaticBuffer()
{
    zvdMemMngPrivate::SetSharedStaticBufferEndCode();
    return &zvdMemMngPrivate::sSharedStaticBuffer[0];
}

//-----------------------------------------------------------------------------

ZvdSize ZvdGetSharedStaticBufferSize() { return kZVD_SHARED_STATIC_BUFFER_SIZE; }

//-----------------------------------------------------------------------------
bool ZvdIsSharedStaticBufferOverflowed()
{
    return zvdMemMngPrivate::kSHARED_STATIC_BUFFER_ENDCODE != zvdMemMngPrivate::GetSharedStaticBufferEndCode();
}

//=============================================================================
// Memory error handler
//=============================================================================

void ZvdSetNotEnoughMemoryHandler(ZvdNotEnoughMemoryHandler_t handler)
{
    ZVD_ASSERT_HIGH_NOMSG(handler);
    zvdMemMngPrivate::sNotEnoughMemoryHandler = handler;
}

//=============================================================================
// C/C++ support
//=============================================================================

//=============================================================================
// allocation-deallocation

//-----------------------------------------------------------------------------

void* ZvdMalloc(ZvdSize nBytes, const char* initiatorName, const char* comment)
{
    void* ZvdMalloc_(ZvdSize nBytes);

    static bool fDenyRequest = false;
    if (fDenyRequest)
        return kZVD_NULL;

    void* p = ZvdMalloc_(nBytes);
    if (!p)
    {   // not memory or something go wrong
        if (!zvdMemMngPrivate::sNotEnoughMemoryHandler)
            return kZVD_NULL;
        fDenyRequest = true; // deny next requests for memory
        // we have a handler, so try to exit softly
        // Внимание отладчик использует данные на стеке этой функции.
        const ZvdSize knErrorTextualInfoSize = 512;
        char errorTextualInfo[knErrorTextualInfoSize] = {};
        const ZvdSize nCommentLen = ZvdSafeStrLen(comment);
        ZvdSafeStrCpyR(errorTextualInfo, comment, comment + zvd::Min(nCommentLen + 1, knErrorTextualInfoSize));
        if (nCommentLen + 1 < knErrorTextualInfoSize)
        {
            const ZvdSize nSpaceLeft = knErrorTextualInfoSize - (nCommentLen + 1);
            const char* infoFromZvdMalloc = "\n  -- Request to ZvdMalloc() was failed!";
            ZvdSafeStrCpyR(errorTextualInfo + nCommentLen,
                           infoFromZvdMalloc,
                           infoFromZvdMalloc + nSpaceLeft);
        }

        ZvdErrorDesc errorDesc(kZVD_ERRC_NOT_ENOUGH_MEM,
                               initiatorName,
                               errorTextualInfo,
                               ZvdSafeStrLen(errorTextualInfo),
                               ZvdVariant((int)nBytes));
        zvdMemMngPrivate::sNotEnoughMemoryHandler(errorDesc);
        return kZVD_NULL;
    }
    //
    //success
    //

    return p;
}

#ifdef ZVD_USED_CPPSTD
// cpp std based -- {

// } -- end of cpp std based
#else
// crt based -- {

//=============================================================================
// allocation-deallocation

//-----------------------------------------------------------------------------

void* ZvdMalloc_(ZvdSize nBytes)
{
    return malloc(nBytes);
}

//-----------------------------------------------------------------------------
void ZvdFree(void* p)
{
    if (p)
    {
        free(p);
    }
}

//-----------------------------------------------------------------------------
void* ZvdRealloc(void *p, ZvdSize newSizeInBytes)
{
    return realloc(p, newSizeInBytes);
}

//=============================================================================
// memory manipulation

//-----------------------------------------------------------------------------
void* ZvdMemCpy(void *dst, const void *src, ZvdSize nBytes, ZvdSize* dstSize)
{
    ZVD_ASSERT_HIGH(dst, ZVD_DEBUG_TEXT("dst is null"));
    ZVD_ASSERT_HIGH(src, ZVD_DEBUG_TEXT("src is null"));
    if (dstSize)
    {
        ZVD_ASSERT_HIGH(nBytes <= *dstSize, ZVD_DEBUG_TEXT("trying dest buffer to overflow!"));

        return dst;
    }
    ZVD_ASSERT_HIGH(zvd::AbsPtrDist(dst, src) >= nBytes, ZVD_DEBUG_TEXT("overlapped"));
    return memcpy(dst, src, nBytes);
}

//-----------------------------------------------------------------------------
void* ZvdMemMove(void* dst, const void* src, ZvdSize nBytes)
{
    ZVD_ASSERT_HIGH(dst, ZVD_DEBUG_TEXT("dst is null"));
    ZVD_ASSERT_HIGH(src, ZVD_DEBUG_TEXT("src is null"));
    return memmove(dst, src, nBytes);
}

//-----------------------------------------------------------------------------
void* ZvdMemSet(void *dst, ZvdInt8 ch, ZvdSize nBytes)
{
    ZVD_ASSERT_HIGH(dst, ZVD_DEBUG_TEXT("dst is null"));
    return memset(dst, ch, nBytes);
}
// } -- end of crt based
#endif // ZVD_USED_CPPSTD

