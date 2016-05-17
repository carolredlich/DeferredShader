#include "Vec3.h"
#include <cmath>

Vec3::Vec3( float x, float y, float z ) : x( x ), y( y ), z( z )
{
}


float Vec3::length()
{
    return sqrt( x * x + y * y + z * z );
}


Vec3 Vec3::operator+( const Vec3& v )
{
    return Vec3( x + v.x, y + v.y, z + v.z );
}


Vec3 Vec3::operator-( const Vec3& v )
{
    return Vec3( x - v.x, y - v.y, z - v.z );
}


Vec3 Vec3::operator*( float f )
{
    return Vec3( x * f, y * f, z * f );
}


Vec3 Vec3::operator/( float f )
{
    return Vec3( x / f, y / f, z / f );
}


float Vec3::operator*( const Vec3& v )
{
    return x * v.x + y * v.y + z * v.z;
}


Vec3 Vec3::operator%( const Vec3& v )
{
    float uX = x;
    float uY = y;
    float uZ = z;

    float vX = v.x;
    float vY = v.y;
    float vZ = v.z;

    float sX = uY * vZ - uZ * vY;
    float sY = uZ * vX - uX * vZ;
    float sZ = uX * vY - uY * vX;

    return Vec3( sX, sY, sZ );
}


Vec3 Vec3::operator+=( float f )
{
    x += f;
    y += f;
    z += f;
}


Vec3 Vec3::operator/=( float f )
{
    x /= f;
    y /= f;
    z /= f;
}


void Vec3::normalize()
{
    float n = length();

    x /= n;
    y /= n;
    z /= n;
}


Vec3 Vec3::operator+=( const Vec3& v )
{
    x += v.x;
    y += v.y;
    z += v.z;
}


Vec3 Vec3::operator+( float f )
{
    return Vec3( x + f, y + f, z + f );
}


Vec3 Vec3::operator-( float f )
{
    return Vec3( x - f, y - f, z - f );
}


