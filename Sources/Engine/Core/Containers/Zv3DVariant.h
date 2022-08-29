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
Purpose: Variant data struct definition.

----------------------
 for developers notes
----------------------

*/

#ifndef ZV3D_DATASTRUCTS_VARIANT_H
#define ZV3D_DATASTRUCTS_VARIANT_H


#include "Core/Platform/Zv3DTypes.h"
#include "Core/StringUtils/Zv3DSafeCStringUtils.h"


//*****************************************************************************
// Variable data struct. Can store:
// int, float (and 4 float array), 4 byte array, C String pointer, raw pointer.
struct ZvdVariant
{
//=============================================================================
// Interface (types and some static methods)
    enum eType
    {
        kUnk,
        kInt,
        kFlt,
        kPtr,
        kStr,
        kV4b,
        kV4f,
    };
    typedef ZvdByte V4b[4];
    typedef ZvdFlt32 V4f[4];

    static
    V4b& assign(V4b* thisPtr, const V4b& oth)
    {
        if (thisPtr == &oth)
            return *thisPtr;
        for (int i = 0; i < 4; ++i)
            (*thisPtr)[i] = oth[i];
        return *thisPtr;
    }

    static
    V4f& assign(V4f* thisPtr, const V4f& oth)
    {
        if (thisPtr == &oth)
            return *thisPtr;
        for (int i = 0; i < 4; ++i)
            (*thisPtr)[i] = oth[i];
        return *thisPtr;
    }

    static
    bool isSameFloats(ZvdFlt32 f1, ZvdFlt32 f2)
    {
        ZvdUint32* pu1 = reinterpret_cast<ZvdUint32*>(&f1);
        ZvdUint32* pu2 = reinterpret_cast<ZvdUint32*>(&f2);
        return (*pu1) == (*pu2);
    }

    static
    bool isSameStrings(const char* s1, const char* s2)
    {
        if (s1 == kZVD_NULL)
        {
            if (s2 == kZVD_NULL)
                return true;
            else
                return false;
        }
        else if (s2 == kZVD_NULL)
        {
            return false;
        }

        return !ZvdSafeStrCmp(s1, s2);
    }

    static
    int cmpStrings(const char* s1, const char* s2)
    {
        if (s1 == kZVD_NULL)
        {
            if (s2 == kZVD_NULL)
                return 0;
            else
                return -1;
        }
        else if (s2 == kZVD_NULL)
        {
            return 1;
        }

        return ZvdSafeStrCmp(s1, s2);
    }
private:
    union Data
    {
        int n;
        ZvdFlt32 f;
        void* p;
        const char* s;
        V4b v4b;
        V4f v4f;
    };

    void reset()
    {
        data_.f = 0.0f;
        data_.n = 0;
        data_.p = kZVD_NULL;
        data_.s = kZVD_NULL;
        data_.v4b[0] = data_.v4b[1] = data_.v4b[2] = data_.v4b[3] = 0;
        data_.v4f[0] = data_.v4f[1] = data_.v4f[2] = data_.v4f[3] = 0.0f;
        type_ = kUnk;
    }

//=============================================================================
// Interface (methods)
public:
    ZvdVariant() : type_(kUnk)
    {
        reset();
    }

    ZvdVariant(int n) : type_(kUnk)
    {
        reset();
        set(n);
    }

    ZvdVariant(ZvdFlt32 f) : type_(kUnk)
    {
        reset();
        set(f);
    }

    ZvdVariant(void* p) : type_(kUnk)
    {
        reset();
        set(p);
    }

    ZvdVariant(const char* s) : type_(kUnk)
    {
        reset();
        set(s);
    }

    void set(int n)             { data_.n = n; setType(kInt); }
    void set(ZvdFlt32 f)        { data_.f = f; setType(kFlt); }
    void set(void* p)           { data_.p = p; setType(kPtr); }
    void set(const char*  s)    { data_.s = s; setType(kStr); }
    void set(const V4b& v4b)    { assign(&data_.v4b, v4b); setType(kV4b); }
    void set(ZvdByte b0,
             ZvdByte b1,
             ZvdByte b2,
             ZvdByte b3)
    {
        data_.v4b[0] = b0;
        data_.v4b[1] = b1;
        data_.v4b[2] = b2;
        data_.v4b[3] = b3;

        setType(kV4b);
    }

    void set(const V4f& v4f)    { assign(&data_.v4f, v4f); setType(kV4f); }
    void set(ZvdFlt32 f0,
             ZvdFlt32 f1,
             ZvdFlt32 f2,
             ZvdFlt32 f3)
    {
        data_.v4f[0] = f0;
        data_.v4f[1] = f1;
        data_.v4f[2] = f2;
        data_.v4f[3] = f3;

        setType(kV4f);
    }

    int getInt() const;
    ZvdFlt32 getFlt() const;
    void* getPtr() const;
    const char* getStr() const;
    const V4b& getV4b() const;
    const V4f& getV4f() const;

    eType getType() const { return type_; }
    void setType(eType type) { type_ = type; }
    bool isInt() const { return type_ == kInt; }
    bool isFlt() const { return type_ == kFlt; }
    bool isPtr() const { return type_ == kPtr; }
    bool isStr() const { return type_ == kStr; }
    bool isV4b() const { return type_ == kV4b; }
    bool isV4f() const { return type_ == kV4f; }
    bool isUnk() const { return type_ == kUnk; }

    operator bool() const { return !isUnk(); }

    ZvdVariant(const ZvdVariant& oth)
    {
        *this = oth;
    }

    ZvdVariant& operator=(const ZvdVariant& oth)
    {
        if (this == &oth)
            return *this;

        if (oth.isInt())
        {
            set(oth.getInt());
        }
        else if (oth.isFlt())
        {
            set(oth.getFlt());
        }
        else if (oth.isPtr())
        {
            set(oth.getPtr());
        }
        else if (oth.isStr())
        {
            set(oth.getStr());
        }
        else if (oth.isV4b())
        {
            set(oth.getV4b());
        }
        else if (oth.isV4f())
        {
            set(oth.getV4f());
        }
        return *this;
    }

    bool operator == (const ZvdVariant& oth) const
    {
        if (getType() != oth.getType())
            return false;

        if (isInt())
            return getInt() == oth.getInt();

        if (isFlt())
            return isSameFloats(getFlt(), oth.getFlt());

        if (isPtr())
            return getPtr() == oth.getPtr();

        if (isStr())
        {
            if (getStr() == oth.getStr())
                return true;

            return isSameStrings(getStr(), oth.getStr());
        }

        if (isV4b())
        {
           for (int i = 0; i < 4; ++i)
           {
               if (getV4b()[i] != getV4b()[i])
                    return false;
           }
           return true;
        }

        if (isV4f())
        {
           for (int i = 0; i < 4; ++i)
           {
               if (!isSameFloats(getV4f()[i], getV4f()[i]))
                return false;
           }
           return true;
        }
    }

    friend bool operator < (const ZvdVariant& v1, const ZvdVariant& v2);
    friend bool operator <=(const ZvdVariant& v1, const ZvdVariant& v2);

private:
    eType type_;
    Data data_;
};

bool operator < (const ZvdVariant& v1, const ZvdVariant& v2);
bool operator <=(const ZvdVariant& v1, const ZvdVariant& v2);

const char* ZvdToString(char* buf, ZvdSize nBufSize, const ZvdVariant& v);


#endif // ZV3D_DATASTRUCTS_VARIANT_H

