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
Purpose: small common used utils.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_CORE_UTILS_SMALLCOMMONUTILS_H
#define ZV3D_CORE_UTILS_SMALLCOMMONUTILS_H

#include "Core/Platform/Zv3DTypes.h"

//=============================================================================
// Macro utils
/// Unused variable wrapper.
#define ZVD_UNUSED(x) ((void)sizeof(x))

//-----------------------------------------------------------------------------
/// FOURCC - packs characters into 32-bit unsigned int.
#define ZVD_FOURCC(ch0, ch1, ch2, ch3)      \
   (((ZvdUint32(ch0) & 0xFF)      ) |       \
    ((ZvdUint32(ch1) & 0xFF) << 8 ) |       \
    ((ZvdUint32(ch2) & 0xFF) << 16) |       \
    ((ZvdUint32(ch3) & 0xFF) << 24) )

//=============================================================================
// Bit manipulation
namespace zvd
{

//-----------------------------------------------------------------------------
/// Returns value with bit x set (2^x).
template <typename T>
inline T BitToValue(Index_t bitIdx)
{
    return (T(1) << bitIdx);
}

//-----------------------------------------------------------------------------
/// Returns true if specified bit is set.
template <typename T>
inline bool IsBitSet(T x, Index_t bitIdx)
{
    return (x & BitToValue<T>(bitIdx));
}

//-----------------------------------------------------------------------------
/// Sets a specified bit.
template <typename T>
inline void SetBit(T x, Index_t bitIdx)
{
   x |= BitToValue<T>(bitIdx);
}

//-----------------------------------------------------------------------------
/// Resets a specified bit.
template <typename T>
inline void ResetBit(T x, Index_t bitIdx)
{
   x &= ~BitToValue<T>(bitIdx);
}

} // end of zvd


//=============================================================================
// Some simple math

namespace zvd
{

//-----------------------------------------------------------------------------
/// Returns the lesser of the two values.
template <typename T>
inline T Min(T a, T b)
{
    return a < b ? a : b;
}

//-----------------------------------------------------------------------------
/// Returns the greater of the two values.
template <typename T>
inline T Max(T a, T b)
{
    return a > b ? a : b;
}

//-----------------------------------------------------------------------------
/// Returns the absolute value of the value.
template <typename T>
inline T Abs(T a)
{
    return a >= 0 ? a : -a;
}

//-----------------------------------------------------------------------------
/// Swap two values.
template <typename T>
inline void Swap(T& a, T& b)
{
    T tmp(a);
    a = b;
    b = tmp;
}

//-----------------------------------------------------------------------------
/** Returns true if point x is in the range a, b.
 @param fAIncl==eInclusion::kYes means [a, and (a, otherwise.
 @param fBIncl==eInclusion::kYes means ,b] and ,b) otherwise.
*/
template <typename T>
inline bool InRange(T x, T a, T b, eInclusion fAIncl, eInclusion fBIncl)
{
    bool fASatisfies{};
    bool fBSatisfies{};

    if (eInclusion::kYes == fAIncl)
        fASatisfies = (x >= a);
    else
        fASatisfies = (x > a);

    if (eInclusion::kYes == fBIncl)
        fBSatisfies = (x <= b);
    else
        fBSatisfies = (x < b);

    return fASatisfies & fBSatisfies;
}

template <typename T>
inline bool InRange(T x, T a, T b, T tol, eInclusion fAIncl, eInclusion fBIncl)
{
    bool fASatisfies{};
    bool fBSatisfies{};

    if (eInclusion::kNo == fAIncl)
        fASatisfies = (x > a + tol);
    else
        fASatisfies = ((Abs(x - a) <= tol) || (x > a));

     if (eInclusion::kNo == fBIncl)
        fBSatisfies = (x < b - tol);
    else
        fBSatisfies = ((Abs(x - b) <= tol) || (x < b));

    return fASatisfies & fBSatisfies;
}

//-----------------------------------------------------------------------------
/// Returns true if point x is in the range (a, b).
template <typename T>
inline bool InOpenRange(T x, T a, T b, eInclusion fAIncl, eInclusion fBIncl)
{
    return InRange(x, a, b, eInclusion::kNo, eInclusion::kNo);
}


template <typename T>
inline bool InOpenRange(T x, T a, T b, T tol, eInclusion fAIncl, eInclusion fBIncl)
{
    return InRange(x, a, b, tol, eInclusion::kNo, eInclusion::kNo);
}

//-----------------------------------------------------------------------------
/// Returns true if point x is in the range [a, b].
template <typename T>
inline bool InClosedRange(T x, T a, T b, eInclusion fAIncl, eInclusion fBIncl)
{
    return InRange(x, a, b, eInclusion::kYes, eInclusion::kYes);
}

template <typename T>
inline bool InClosedRange(T x, T a, T b, T tol, eInclusion fAIncl, eInclusion fBIncl)
{
    return InRange(x, a, b, tol, eInclusion::kYes, eInclusion::kYes);
}

} // end of zvd


//=============================================================================
// Pointers

namespace zvd
{

//-----------------------------------------------------------------------------
/// Cast raw (void) pointer to pointer of bytes.
inline Byte_t* CastToBytePtr(void* pRaw)
{
    return reinterpret_cast<Byte_t*>(pRaw);
}

inline const Byte_t* CastToBytePtr(const void* pRaw)
{
    return reinterpret_cast<const Byte_t*>(pRaw);
}

//-----------------------------------------------------------------------------
/// Returns the absolute distanse of 1st pointer to 2nd.
inline Size_t AbsPtrDist(const void* p1, const void* p2)
{
    const Byte_t* pb1 = CastToBytePtr(p1);
    const Byte_t* pb2 = CastToBytePtr(p2);
    if (pb1 > pb2)
    {
        return pb1 - pb2;
    }
    return pb2 - pb1;
}
} // end of zvd



//=============================================================================
// Asserts special
void ZvdAssertIndexInRange(ZvdIndex idx, ZvdIndex idxStart, ZvdIndex idxEnd);

#endif // ZV3D_CORE_UTILS_SMALLCOMMONUTILS_H
