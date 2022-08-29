#include "Core/Containers/Zv3DVariant.h"
#include "Core/Debug/Zv3DAssert.h"


#include <stdio.h>


//-----------------------------------------------------------------------------
int ZvdVariant::getInt() const
{
    ZVD_ASSERT_HIGH_NOMSG(*this);
    return data_.n;
}

//-----------------------------------------------------------------------------

float ZvdVariant::getFlt() const
{
    ZVD_ASSERT_HIGH_NOMSG(*this);
    return data_.f;
}

//-----------------------------------------------------------------------------

void* ZvdVariant::getPtr() const
{
    ZVD_ASSERT_HIGH_NOMSG(*this);
    return data_.p;
}

//-----------------------------------------------------------------------------

const char* ZvdVariant::getStr() const
{
    ZVD_ASSERT_HIGH_NOMSG(*this);
    return data_.s;
}

//-----------------------------------------------------------------------------

const ZvdVariant::V4b& ZvdVariant::getV4b() const
{
    ZVD_ASSERT_HIGH_NOMSG(*this);
    return data_.v4b;
}

//-----------------------------------------------------------------------------

const ZvdVariant::V4f& ZvdVariant::getV4f() const
{
    ZVD_ASSERT_HIGH_NOMSG(*this);
    return data_.v4f;
}

//-----------------------------------------------------------------------------

bool operator <(const ZvdVariant& v1, const ZvdVariant& v2)
{
    ZVD_ASSERT_HIGH_NOMSG(v1.getType() == v2.getType());
    ZVD_ASSERT_HIGH(!(v1.isV4b() || v1.isV4f()), ZVD_DEBUG_TEXT("less op is unsupported for vectors"));

    if (v1.isInt())
        return v1.getInt() < v2.getInt();

    if (v1.isFlt())
        return v1.getFlt() < v2.getFlt();

    if (v1.isPtr())
        return v1.getPtr() < v2.getPtr();

    if (v1.isStr())
    {
        if (v1.getStr() == v2.getStr())
            return false;

        if (ZvdVariant::cmpStrings(v1.getStr(), v2.getStr()) == -1)
            return true;

        return false;
    }
    return false; // avoiding warning
}

//-----------------------------------------------------------------------------

bool operator <=(const ZvdVariant& v1, const ZvdVariant& v2)
{
    ZVD_ASSERT_HIGH_NOMSG(v1.getType() == v2.getType());
    ZVD_ASSERT_HIGH(!(v1.isV4b() || v1.isV4f()), ZVD_DEBUG_TEXT("less-or-eqal op is unsupported for vectors"));

    if (v1.isInt())
        return v1.getInt() <= v2.getInt();

    if (v1.isFlt())
        return v1.getFlt() <= v2.getFlt();

    if (v1.isPtr())
        return v1.getPtr() <= v2.getPtr();

    if (v1.isStr())
    {
        if (v1.getStr() == v2.getStr())
            return true;

        int rslt = ZvdVariant::cmpStrings(v1.getStr(), v2.getStr());
        if (rslt == -1 || rslt == 0)
            return true;

        return false;
    }
    return false; // avoiding warning
}

//-----------------------------------------------------------------------------

const char* ZvdToString(char* buf, ZvdSize nBufSize, const ZvdVariant& v)
{
    if (!v)
        return "'unknown variant'";

    if (v.isInt())
    {
        int n = sprintf_s(buf, nBufSize, "%i", v.getInt());
        if (n > 0)
            return buf;
        else
            return "";
    }

    if (v.isFlt())
    {
        int n = sprintf_s(buf, nBufSize, "%f", v.getFlt());
        if (n > 0)
            return buf;
        else
            return "";
    }

    if (v.isPtr())
    {
        int n = sprintf_s(buf, nBufSize, "%p", v.getPtr());
        if (n > 0)
            return buf;
        else
            return "";
    }

    if (v.isStr())
    {
        int n = sprintf_s(buf, nBufSize, "\"%s\"", v.getStr());
        if (n > 0)
            return buf;
        else
            return "";
    }

    if (v.isV4b())
    {
        const ZvdVariant::V4b& vv = v.getV4b();
        int n = sprintf_s(buf, nBufSize, "[%i, %i, %i, %i]", vv[0], vv[1], vv[2], vv[3]);
        if (n > 0)
            return buf;
        else
            return "";
    }

    if (v.isV4f())
    {
        const ZvdVariant::V4f& vv = v.getV4f();
        int n = sprintf_s(buf, nBufSize, "[%f, %f, %f, %f]", vv[0], vv[1], vv[2], vv[3]);
        if (n > 0)
            return buf;
        else
            return "";
    }
    return "";
}

