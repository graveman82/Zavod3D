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
Purpose: memory operations.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_MEMMNG_MEMUTILS_H
#define ZV3D_CORE_MEMMNG_MEMUTILS_H

#include "Core/Platform/Zv3DTypes.h"
#include "Core/MemMng/Zv3DMemDefs.h"


//=============================================================================
// Static shared buffer routines.
// Static shared buffer - mem inside PE image in memory (writable section).
// Just a static storage array variable of specified size.

//-----------------------------------------------------------------------------
/// Get static memory end. Use it when "not enough memory" case is not allowed.
const ZvdByte* ZvdGetSharedStaticBufferEnd();

//-----------------------------------------------------------------------------
/// Get static memory beginning. Use it when "not enough memory" case is not allowed.
ZvdByte* ZvdGetSharedStaticBuffer();

//-----------------------------------------------------------------------------
/// Get static memory size. Use it when "not enough memory" case is not allowed.
ZvdSize ZvdGetSharedStaticBufferSize();

//-----------------------------------------------------------------------------
// If returns true, code called ZvdGetSharedStaticBuffer() had overflowed static buffer.
bool ZvdIsSharedStaticBufferOverflowed();


//=============================================================================
// Memory error handler
void ZvdSetNotEnoughMemoryHandler(ZvdNotEnoughMemoryHandler_t handler);

//=============================================================================
// allocation-deallocation
void*   ZvdMalloc       (ZvdSize nBytes, const char* initiatorName = "", const char* comment = "");
void    ZvdFree         (void *p);
void*   ZvdRealloc      (void *p, ZvdSize newSizeInBytes);


//=============================================================================
// memory manipulation
void*   ZvdMemCpy(void *dst, const void *src, ZvdSize nBytes, ZvdSize* dstSize = nullptr);
void*   ZvdMemMove(void* dst, const void* src, ZvdSize nBytes);
void*   ZvdMemSet(void *dst, ZvdInt8 ch, ZvdSize nBytes);

#endif // ZV3D_CORE_MEMMNG_MEMUTILS_H
