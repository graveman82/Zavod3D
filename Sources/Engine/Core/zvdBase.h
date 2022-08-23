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
Purpose: включается во все файлы.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_BASE_H
#define ZV3D_CORE_BASE_H

/** Zavod3D engine api exporting declaration specifiers.
Define macro ZVD_EXPORTS if you want to export engine interfaces.
*/
#ifdef ZVD_EXPORTS
#   define ZVD_ENGINE_API __declspec(dllexport)
#else
#   define ZVD_ENGINE_API __declspec(dllimport)
#endif

#endif // ZV3D_CORE_BASE_H
