#pragma once

class Vector3f
{
private:
    float m_v[3];

public:
    Vector3f(void);
    Vector3f(float x, float y, float z);
    Vector3f(Vector3f* v);

    float* Get3fv();
    float GetX();
    float GetY();
    float GetZ();
    
    Vector3f operator + (const Vector3f& v);
    Vector3f operator += (const Vector3f& v);
    Vector3f operator * (const float& f);
    Vector3f operator *= (const Vector3f& v);

};


static Vector3f operator * (const float f, const Vector3f v)
{
    return f * v;
}
