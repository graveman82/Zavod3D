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
Purpose: small common utils which require no inline implementation.

----------------------
 for developers notes
----------------------

*/
#include "Core/Utils/Zv3DSmallCommonUtils.h"

#include "Core/Debug/Zv3DAssert.h"

//-----------------------------------------------------------------------------

void ZvdAssertIndexInRange(ZvdIndex idx, ZvdIndex idxStart, ZvdIndex idxEnd)
{
    ZVD_ASSERT_HIGH3(zvd::InRange(idx, idxStart, idxEnd, zvd::eInclusion::kYes, zvd::eInclusion::kNo), ZVD_DEBUG_TEXT("index %i is out of range [%i, %i)\n"), idx, idxStart, idxEnd);
}

