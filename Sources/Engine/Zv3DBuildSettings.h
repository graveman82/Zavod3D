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
Purpose: build settings of engine.

----------------------
 for developers notes
----------------------
note1: this file must be included in all others!
*/

#ifndef ZV3D_BUILDSETTINGS_H
#define ZV3D_BUILDSETTINGS_H

//=============================================================================
// Selecting cpp std or crt
#if !(defined(ZVD_USED_CPPSTD) || defined(ZVD_USED_CRT))

//-----------------------------------------------------------------------------
/** Zavod3D engine uses either cpp std lib or crt lib (memcpy(), malloc() routines etc).
 So, you can choose one of them. By default crt is used.
 Macro is defined by in project setting or by commenting/uncommenting code below.
*/
// comment one and uncomment second
#   define ZVD_USED_CRT
//#   define ZVD_USED_CPPSTD

#endif // !(defined(ZVD_USED_CPPSTD) || defined(ZVD_USED_CRT))

// If you set both (for example, one in project settings and second was defined abovw in code)
#if defined(ZVD_USED_CPPSTD)
#   ifdef ZVD_USED_CRT
#       undef ZVD_USED_CRT
#   endif

#elif defined(ZVD_USED_CRT)
#   ifdef ZVD_USED_CPPSTD
#       undef ZVD_USED_CPPSTD
#   endif

#endif // defined(ZVD_USED_CPPSTD)


//=============================================================================
// Required compiler version

//-----------------------------------------------------------------------------
// GCC
#ifdef __GNUC__
#define ZVD_MIN_GCC_COMPILER_MAJOR 8
#define ZVD_MIN_GCC_COMPILER_MINOR 1
#define ZVD_MIN_GCC_COMPILER_PATCHLEVEL 0
#endif


//=============================================================================
// Fized size integer source
/// Value to set up @ref ZVD_USED_INT_FROM. Use language int types with size checking at compile-time.
#define ZVD_USED_INT_FROM_LANG 0 // char, short, int etc
/// Value to set up @ref ZVD_USED_INT_FROM. Use '(c)stdint.h' int types.
#define ZVD_USED_INT_FROM_STDINT 1
/// Value to set up @ref ZVD_USED_INT_FROM. Use 'boost::cstdint.h' int types.
#define ZVD_USED_INT_FROM_BOOST 2

//-----------------------------------------------------------------------------
// Comment 2, uncomment 1 of 3.
#ifndef ZVD_USED_INT_FROM // Use fized sized int types from -- {
/// Source of fixed sized integer types.
#define ZVD_USED_INT_FROM ZVD_USED_INT_FROM_LANG
//#define ZVD_USED_INT_FROM ZVD_USED_INT_FROM_STDINT
//#define ZVD_USED_INT_FROM ZVD_USED_INT_FROM_BOOST
#endif // } -- Use fized sized int types from


//=============================================================================
// Debugging
//#define ZVD_DEBUG_LEVEL ZVD_DEBUG_LEVEL_HIGH
//#define ZVD_USE_MSGBOX_FOR_ASSERT
#endif // ZV3D_BUILDSETTINGS_H
