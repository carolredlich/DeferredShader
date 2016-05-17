#ifndef VEC3_H
#define VEC3_H

class Vec3
{
public:

    Vec3()
    {
    }


    Vec3( float x, float y, float z );

    float length();
    Vec3 operator+( const Vec3& v );
    Vec3 operator-( const Vec3& v );
    float operator*( const Vec3& v );
    Vec3 operator%( const Vec3& v );
    Vec3 operator+=( const Vec3& v );

    Vec3 operator+( float f );
    Vec3 operator-( float f );
    Vec3 operator*( float f );
    Vec3 operator/( float f );
    Vec3 operator+=( float f );
    Vec3 operator/=( float f );

    void normalize();

    float x;
    float y;
    float z;
};

#endif