#pragma once
class Vector3f
{
private:
    float m_v[3];// m_x, m_y, m_z;

public:
    Vector3f(void);
    Vector3f(float x, float y, float z);
    Vector3f(Vector3f* v);
    ~Vector3f(void);

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
