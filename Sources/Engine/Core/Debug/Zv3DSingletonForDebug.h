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
Purpose: singleton for debug tools definition.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_DEBUG_SINGLETONFORDEBUG_H
#define ZV3D_DEBUG_SINGLETONFORDEBUG_H

#include "Core/Platform/Zv3DTypes.h"


namespace zvd
{
namespace debug
{

//-----------------------------------------------------------------------------
/** @class StaticAllocatedSingleton
    An object instance is allocated in static buffer.
*/
template <typename T, ZvdSize kBufferSize, typename TPseudoCtor>
class StaticAllocatedSingleton
{
public:
    StaticAllocatedSingleton() = default;

    /// Returns reference to a single instance of given template type.
    static T& Instance()
    {
        if (!sInstance_)
        {
            sInstance_ = TPseudoCtor() (&sBuffer_[0]);
        }
        return *sInstance_;
    }

    /// Destroys the instance explicitly.
    static void Destroy()
    {
        if (sInstance_)
        {
            sInstance_->~T();
            sInstance_ = nullptr;
        }
    }

private:

    // not allowed
    StaticAllocatedSingleton(const StaticAllocatedSingleton<T, kBufferSize, TPseudoCtor>&) = delete;
    StaticAllocatedSingleton& operator=(const StaticAllocatedSingleton<T, kBufferSize, TPseudoCtor>&) = delete;

    static T* sInstance_;
    static ZvdByte sBuffer_[kBufferSize];
};

//-----------------------------------------------------------------------------
template <typename T, ZvdSize kBufferSize, typename TPseudoCtor>
T* StaticAllocatedSingleton<T, kBufferSize, TPseudoCtor>::sInstance_ = nullptr;

//-----------------------------------------------------------------------------
template <typename T, ZvdSize kBufferSize, typename TPseudoCtor>
ZvdByte StaticAllocatedSingleton<T, kBufferSize, TPseudoCtor>::sBuffer_[kBufferSize];
} // end of debug
} // end of zvd

#endif // ZV3D_DEBUG_SINGLETONFORDEBUG_H
