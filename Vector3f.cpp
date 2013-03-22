#include "Vector3f.h"


Vector3f::Vector3f(void)
{
    m_v[0] = 0;
    m_v[1] = 0;
    m_v[2] = 0;
}


Vector3f::Vector3f(float x, float y, float z)
{
    m_v[0] = x;
    m_v[1] = y;
    m_v[2] = z;
}


Vector3f::Vector3f(Vector3f* v)
{
    m_v[0] = v->m_v[0];
    m_v[1] = v->m_v[1];
    m_v[2] = v->m_v[2];
}


float* Vector3f::Get3fv()
{
    return m_v;
}


float Vector3f::GetX()
{
    return m_v[0];
}


float Vector3f::GetY()
{
    return m_v[1];
}


float Vector3f::GetZ()
{
    return m_v[2];
}


Vector3f Vector3f::operator + (const Vector3f& v)
{
    Vector3f result(this);
    
    return result += v;
}


Vector3f Vector3f::operator += (const Vector3f& v)
{
    m_v[0] += v.m_v[0];
    m_v[1] += v.m_v[1];
    m_v[2] += v.m_v[2];

    return *this;
}


Vector3f Vector3f::operator * (const float& f)
{
    Vector3f result(this);

    result.m_v[0] *= f;
    result.m_v[1] *= f;
    result.m_v[2] *= f;

    return result;
}


Vector3f Vector3f::operator *= (const Vector3f& v)
{
    m_v[0] *= v.m_v[0];
    m_v[1] *= v.m_v[1];
    m_v[2] *= v.m_v[2];

    return *this;
}
