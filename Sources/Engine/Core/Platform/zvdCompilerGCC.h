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
Purpose: gcc dependent defs.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_PLATFORM_COMPILERGCC_H
#define ZV3D_CORE_PLATFORM_COMPILERGCC_H

//-----------------------------------------------------------------------------
/// GCC Compiler Version
#define ZVD_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

/// Returns true if used GCC Compiler version >= specified
#define ZVD_IS_COMPILER_GCC_GREATER_OR_EQUAL(major,minor,patchlevel)\
(ZVD_COMPILER_GCC >= (major * 10000 + minor * 100 + patchlevel))

#if (!ZVD_IS_COMPILER_GCC_GREATER_OR_EQUAL(8,1,0))
#   error "GCC: compiler version lower than 8.1.0 is not guaranteed!"
#endif

//-----------------------------------------------------------------------------
// C++ version -- {
#if defined(__cplusplus)
/// C++ version
#   define ZVD_CPP __cplusplus

#   if (199711L == ZVD_CPP)
/// C++ standard number
#       define ZVD_CPP_STANDARD 1
#   elif (201103L == ZVD_CPP)
#       define ZVD_CPP_STANDARD 11
#   elif (201402L == ZVD_CPP)
#       define ZVD_CPP_STANDARD 14
#   elif (201703L == ZVD_CPP)
#       define ZVD_CPP_STANDARD 17
#   elif (202002L == ZVD_CPP)
#       define ZVD_CPP_STANDARD 20
#   else
#       error "GCC: ZVD_CPP_STANDARD undefined"
#   endif

#   if (ZVD_CPP_STANDARD < 11)
#       error "GCC: C++ 11 or higher compiler is required"
#   endif

#else
#   error "GCC: C++ compiler is required"

#endif // } -- end of C++ version

//-----------------------------------------------------------------------------
// Identify the Operating System -- {

#if defined(__WIN32__) || defined(_WIN32)
/// Macros indicating OS Windows used
#   define ZVD_OS_WIN
/// Macros indicating 32-bit OS Windows used
#   define ZVD_OS_WIN32
#   if defined(_WIN64)
/// OS Windows string
#       define ZVD_OS_STRING "Win64"
/// Macros indicating 64-bit OS Windows used
#       define ZVD_OS_WIN64
#   else
#       define ZVD_OS_STRING "Win32"
#   endif

#else
#   error "GCC: Unsupported Operating System"
#endif // } -- end of Identify the Operating System

//-----------------------------------------------------------------------------
// Identify the CPU -- {
#if defined(i386)
/// CPU string
#   define ZVD_CPU_STRING "Intel x86"
/// x86 CPU used
#   define ZVD_CPU_X86
/// Little-endian machine used
#   define ZVD_LITTLE_ENDIAN

#else
#   error "GCC: Unsupported Target CPU"
#endif // } -- end of Identify the CPU

#endif // ZV3D_CORE_PLATFORM_COMPILERGCC_H
