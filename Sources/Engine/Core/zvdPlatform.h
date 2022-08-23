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
Purpose: .

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_PLATFORM_H
#define ZV3D_CORE_PLATFORM_H

//-----------------------------------------------------------------------------
// Identify the compiler being used

// GNU GCC
#if defined(__GNUC__)
#   include "Core/Platform/zvdCompilerGCC.h"
#elif defined(_MSC_VER)
#   include "Core/Platform/zvdCompilerMSVC.h"
#else
#   error "Unknown Compiler"
#endif

#endif // ZV3D_CORE_PLATFORM_H
