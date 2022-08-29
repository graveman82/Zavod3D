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
Purpose: C string utils declarations.

----------------------
 for developers notes
----------------------

*/

#include "Core/StringUtils/Zv3DCStrUtils.h"
#include "Core/Debug/Zv3DAssert.h"
#include "Core/Utils/Zv3DSmallCommonUtils.h"

//-----------------------------------------------------------------------------
// Conditional headers
#ifdef ZVD_USED_CPPSTD
// cpp std based -- {

// } -- end of cpp std based
#else
// crt based -- {
#include <string.h>

// } -- end of crt based
#endif // ZVD_USED_CPPSTD

//*****************************************************************************
// Implementation
#ifdef ZVD_USED_CPPSTD
// cpp std based -- {

// } -- end of cpp std based
#else
// crt based -- {

//=============================================================================
// string examination

//-----------------------------------------------------------------------------
ZvdSize ZvdStrLen(const char *str)
{
    ZVD_ASSERT_HIGH(str, ZVD_ASSERT_TEXT(""));
    return strlen(str);
}
// } -- end of crt based
#endif // ZVD_USED_CPPSTD
