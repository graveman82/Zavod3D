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
Purpose: debug subsystem definitions.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_DEBUG_DEBUGDEFS_H
#define ZV3D_DEBUG_DEBUGDEFS_H


#include "Core/Platform/Zv3DTypes.h"
#include "Core/Utils/Zv3DStringify.h"
#include "Core/Containers/Zv3DVariant.h"
#include "Core/Utils/Zv3DSmallCommonUtils.h"

//-----------------------------------------------------------------------------
/// Stringifies class or other type name.
#define ZVD_CLASSNAME(cls) ZVD_STRINGIFY(cls, ZVD_NARROWCHAR)


//-----------------------------------------------------------------------------
enum eZvdErrorCode
{
    kZVD_ERRC_UNKNOWN = -1,         ///< uncategorized error
    kZVD_ERRC_OK = 1,               ///< no error (success)
    kZVD_ERRC_NOT_ENOUGH_MEM,       ///< not enough memory for allocation request
    kZVD_ERRC_FILE_NOT_FOUND,       ///< file or directory not found
};

//-----------------------------------------------------------------------------
//
#define kZVD_ERROR_DESC_TEXTUAL_INFO_SIZE 512
class ZvdErrorDesc
{
public:
    ZvdErrorDesc(eZvdErrorCode errorCode = kZVD_ERRC_OK,
                 const char* initiatorName = "",
                 const char* textualInfo = "",
                 ZvdSize textualInfoLen = 0,
                 const ZvdVariant& data = ZvdVariant())
        : errorCode_(errorCode)
        , initiatorName_(initiatorName)
        , data_(data)
    {
        ZvdSafeStrCpyR(textualInfo_, textualInfo,
                       textualInfo + zvd::Min(textualInfoLen, (ZvdSize)kZVD_ERROR_DESC_TEXTUAL_INFO_SIZE));
    }

    eZvdErrorCode ErrorCode() const { return errorCode_; }
    const char* InitiatorName() const { return initiatorName_; }
    const char* TextualInfo() const { return &textualInfo_[0]; }
    const ZvdVariant& Data() const { return data_; }

    ZvdErrorDesc& operator=(const ZvdErrorDesc& oth)
    {
        if (this != &oth)
        {
            errorCode_ = oth.ErrorCode();
            initiatorName_ = oth.InitiatorName();
            ZvdSafeStrCpy(textualInfo_, oth.TextualInfo());
            data_ = oth.Data();
        }
        return *this;
    }
private:
    eZvdErrorCode errorCode_;
    const char* initiatorName_;
    char textualInfo_[kZVD_ERROR_DESC_TEXTUAL_INFO_SIZE];
    ZvdVariant data_;
};
#endif // ZV3D_DEBUG_DEBUGDEFS_H
