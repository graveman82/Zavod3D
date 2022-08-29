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
Purpose: memory management relative definitions.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_MEMMNG_MEMDEFS_H
#define ZV3D_CORE_MEMMNG_MEMDEFS_H

#include "Core/Platform/Zv3DTypes.h"
#include "Core/Debug/Zv3DDebugDefs.h"

#define kZVD_SHARED_STATIC_BUFFER_SIZE 4096

typedef void (__stdcall *ZvdNotEnoughMemoryHandler_t)(const ZvdErrorDesc&);

#endif // ZV3D_CORE_MEMMNG_MEMDEFS_H
