

#include <string.h>
#include "Math4f.h"



Math4f::Math4f( )
{
    loadIdentity( );
}



Math4f::Math4f( const double* m )
{
    memcpy( _matrix, m, 16 * sizeof ( double ) );
}



void Math4f::loadIdentity( )
{
    memset( _matrix, 0, 16 * sizeof (double ) );
    _matrix[0] = 1.0f;
    _matrix[5] = 1.0f;
    _matrix[10] = 1.0f;
    _matrix[15] = 1.0f;
}



void Math4f::setMatrix( const double* m )
{
    memcpy( _matrix, m, 16 * sizeof ( double ) );
}



double& Math4f::at( int x, int y )
{
    return _matrix[x * 4 + y];
}



Math4f Math4f::operator *( Math4f m )
{
    Math4f result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            double n = 0;
            for (int k = 0; k < 4; k++)
                n += m.at( i, k ) * at( k, j );
            result.at( i, j ) = n;
        }
    }
    return result;
}



//Point3Dd Math4f::operator*( const Point3Dd point )
//{
//    double inPonit[4] = {point.x, point.y, point.z, 1.0};
//    double result[4];
//    for (int i = 0; i < 4; i++)
//    {
//        double n = 0.0;
//        for (int k = 0; k < 4; k++)
//        {
//            n += at( k, i ) * inPonit[k];
//        }
//        result[i] = n;
//    }
//    return Point3Dd( result[0] / result[3], result[1] / result[3], result[2] / result[3] );
//}



Math4f Math4f::operator*( double val )
{
    Math4f ret;
    for (int i = 0; i < 16; i++)
        ret._matrix[i] = _matrix[i] * val;
    return ret;
}



Math4f Math4f::inverse( )
{
    Math4f inverseMatrix;

    inverseMatrix.at( 0, 0 ) =
        +at( 2, 1 ) * at( 3, 2 ) * at( 1, 3 )
        - at( 3, 1 ) * at( 2, 2 ) * at( 1, 3 )
        + at( 3, 1 ) * at( 1, 2 ) * at( 2, 3 )
        - at( 1, 1 ) * at( 3, 2 ) * at( 2, 3 )
        - at( 2, 1 ) * at( 1, 2 ) * at( 3, 3 )
        + at( 1, 1 ) * at( 2, 2 ) * at( 3, 3 );

    inverseMatrix.at( 1, 0 ) =
        +at( 3, 0 ) * at( 2, 2 ) * at( 1, 3 )
        - at( 2, 0 ) * at( 3, 2 ) * at( 1, 3 )
        - at( 3, 0 ) * at( 1, 2 ) * at( 2, 3 )
        + at( 1, 0 ) * at( 3, 2 ) * at( 2, 3 )
        + at( 2, 0 ) * at( 1, 2 ) * at( 3, 3 )
        - at( 1, 0 ) * at( 2, 2 ) * at( 3, 3 );

    inverseMatrix.at( 2, 0 ) =
        +at( 2, 0 ) * at( 3, 1 ) * at( 1, 3 )
        - at( 3, 0 ) * at( 2, 1 ) * at( 1, 3 )
        + at( 3, 0 ) * at( 1, 1 ) * at( 2, 3 )
        - at( 1, 0 ) * at( 3, 1 ) * at( 2, 3 )
        - at( 2, 0 ) * at( 1, 1 ) * at( 3, 3 )
        + at( 1, 0 ) * at( 2, 1 ) * at( 3, 3 );

    inverseMatrix.at( 3, 0 ) =
        +at( 3, 0 ) * at( 2, 1 ) * at( 1, 2 )
        - at( 2, 0 ) * at( 3, 1 ) * at( 1, 2 )
        - at( 3, 0 ) * at( 1, 1 ) * at( 2, 2 )
        + at( 1, 0 ) * at( 3, 1 ) * at( 2, 2 )
        + at( 2, 0 ) * at( 1, 1 ) * at( 3, 2 )
        - at( 1, 0 ) * at( 2, 1 ) * at( 3, 2 );

    inverseMatrix.at( 0, 1 ) =
        +at( 3, 1 ) * at( 2, 2 ) * at( 0, 3 )
        - at( 2, 1 ) * at( 3, 2 ) * at( 0, 3 )
        - at( 3, 1 ) * at( 0, 2 ) * at( 2, 3 )
        + at( 0, 1 ) * at( 3, 2 ) * at( 2, 3 )
        + at( 2, 1 ) * at( 0, 2 ) * at( 3, 3 )
        - at( 0, 1 ) * at( 2, 2 ) * at( 3, 3 );

    inverseMatrix.at( 1, 1 ) =
        +at( 2, 0 ) * at( 3, 2 ) * at( 0, 3 )
        - at( 3, 0 ) * at( 2, 2 ) * at( 0, 3 )
        + at( 3, 0 ) * at( 0, 2 ) * at( 2, 3 )
        - at( 0, 0 ) * at( 3, 2 ) * at( 2, 3 )
        - at( 2, 0 ) * at( 0, 2 ) * at( 3, 3 )
        + at( 0, 0 ) * at( 2, 2 ) * at( 3, 3 );

    inverseMatrix.at( 2, 1 ) =
        +at( 3, 0 ) * at( 2, 1 ) * at( 0, 3 )
        - at( 2, 0 ) * at( 3, 1 ) * at( 0, 3 )
        - at( 3, 0 ) * at( 0, 1 ) * at( 2, 3 )
        + at( 0, 0 ) * at( 3, 1 ) * at( 2, 3 )
        + at( 2, 0 ) * at( 0, 1 ) * at( 3, 3 )
        - at( 0, 0 ) * at( 2, 1 ) * at( 3, 3 );

    inverseMatrix.at( 3, 1 ) =
        +at( 2, 0 ) * at( 3, 1 ) * at( 0, 2 )
        - at( 3, 0 ) * at( 2, 1 ) * at( 0, 2 )
        + at( 3, 0 ) * at( 0, 1 ) * at( 2, 2 )
        - at( 0, 0 ) * at( 3, 1 ) * at( 2, 2 )
        - at( 2, 0 ) * at( 0, 1 ) * at( 3, 2 )
        + at( 0, 0 ) * at( 2, 1 ) * at( 3, 2 );

    inverseMatrix.at( 0, 2 ) =
        +at( 1, 1 ) * at( 3, 2 ) * at( 0, 3 )
        - at( 3, 1 ) * at( 1, 2 ) * at( 0, 3 )
        + at( 3, 1 ) * at( 0, 2 ) * at( 1, 3 )
        - at( 0, 1 ) * at( 3, 2 ) * at( 1, 3 )
        - at( 1, 1 ) * at( 0, 2 ) * at( 3, 3 )
        + at( 0, 1 ) * at( 1, 2 ) * at( 3, 3 );

    inverseMatrix.at( 1, 2 ) =
        +at( 3, 0 ) * at( 1, 2 ) * at( 0, 3 )
        - at( 1, 0 ) * at( 3, 2 ) * at( 0, 3 )
        - at( 3, 0 ) * at( 0, 2 ) * at( 1, 3 )
        + at( 0, 0 ) * at( 3, 2 ) * at( 1, 3 )
        + at( 1, 0 ) * at( 0, 2 ) * at( 3, 3 )
        - at( 0, 0 ) * at( 1, 2 ) * at( 3, 3 );

    inverseMatrix.at( 2, 2 ) =
        +at( 1, 0 ) * at( 3, 1 ) * at( 0, 3 )
        - at( 3, 0 ) * at( 1, 1 ) * at( 0, 3 )
        + at( 3, 0 ) * at( 0, 1 ) * at( 1, 3 )
        - at( 0, 0 ) * at( 3, 1 ) * at( 1, 3 )
        - at( 1, 0 ) * at( 0, 1 ) * at( 3, 3 )
        + at( 0, 0 ) * at( 1, 1 ) * at( 3, 3 );

    inverseMatrix.at( 3, 2 ) =
        +at( 3, 0 ) * at( 1, 1 ) * at( 0, 2 )
        - at( 1, 0 ) * at( 3, 1 ) * at( 0, 2 )
        - at( 3, 0 ) * at( 0, 1 ) * at( 1, 2 )
        + at( 0, 0 ) * at( 3, 1 ) * at( 1, 2 )
        + at( 1, 0 ) * at( 0, 1 ) * at( 3, 2 )
        - at( 0, 0 ) * at( 1, 1 ) * at( 3, 2 );

    inverseMatrix.at( 0, 3 ) =
        +at( 2, 1 ) * at( 1, 2 ) * at( 0, 3 )
        - at( 1, 1 ) * at( 2, 2 ) * at( 0, 3 )
        - at( 2, 1 ) * at( 0, 2 ) * at( 1, 3 )
        + at( 0, 1 ) * at( 2, 2 ) * at( 1, 3 )
        + at( 1, 1 ) * at( 0, 2 ) * at( 2, 3 )
        - at( 0, 1 ) * at( 1, 2 ) * at( 2, 3 );

    inverseMatrix.at( 1, 3 ) =
        +at( 1, 0 ) * at( 2, 2 ) * at( 0, 3 )
        - at( 2, 0 ) * at( 1, 2 ) * at( 0, 3 )
        + at( 2, 0 ) * at( 0, 2 ) * at( 1, 3 )
        - at( 0, 0 ) * at( 2, 2 ) * at( 1, 3 )
        - at( 1, 0 ) * at( 0, 2 ) * at( 2, 3 )
        + at( 0, 0 ) * at( 1, 2 ) * at( 2, 3 );

    inverseMatrix.at( 2, 3 ) =
        +at( 2, 0 ) * at( 1, 1 ) * at( 0, 3 )
        - at( 1, 0 ) * at( 2, 1 ) * at( 0, 3 )
        - at( 2, 0 ) * at( 0, 1 ) * at( 1, 3 )
        + at( 0, 0 ) * at( 2, 1 ) * at( 1, 3 )
        + at( 1, 0 ) * at( 0, 1 ) * at( 2, 3 )
        - at( 0, 0 ) * at( 1, 1 ) * at( 2, 3 );

    inverseMatrix.at( 3, 3 ) =
        +at( 1, 0 ) * at( 2, 1 ) * at( 0, 2 )
        - at( 2, 0 ) * at( 1, 1 ) * at( 0, 2 )
        + at( 2, 0 ) * at( 0, 1 ) * at( 1, 2 )
        - at( 0, 0 ) * at( 2, 1 ) * at( 1, 2 )
        - at( 1, 0 ) * at( 0, 1 ) * at( 2, 2 )
        + at( 0, 0 ) * at( 1, 1 ) * at( 2, 2 );

    return inverseMatrix * ( 1.0 / determinant( ) );
}



double Math4f::determinant( )
{
    return
    +at( 3, 0 ) * at( 2, 1 ) * at( 1, 2 ) * at( 0, 3 )
        - at( 2, 0 ) * at( 3, 1 ) * at( 1, 2 ) * at( 0, 3 )
        - at( 3, 0 ) * at( 1, 1 ) * at( 2, 2 ) * at( 0, 3 )
        + at( 1, 0 ) * at( 3, 1 ) * at( 2, 2 ) * at( 0, 3 )

        + at( 2, 0 ) * at( 1, 1 ) * at( 3, 2 ) * at( 0, 3 )
        - at( 1, 0 ) * at( 2, 1 ) * at( 3, 2 ) * at( 0, 3 )
        - at( 3, 0 ) * at( 2, 1 ) * at( 0, 2 ) * at( 1, 3 )
        + at( 2, 0 ) * at( 3, 1 ) * at( 0, 2 ) * at( 1, 3 )

        + at( 3, 0 ) * at( 0, 1 ) * at( 2, 2 ) * at( 1, 3 )
        - at( 0, 0 ) * at( 3, 1 ) * at( 2, 2 ) * at( 1, 3 )
        - at( 2, 0 ) * at( 0, 1 ) * at( 3, 2 ) * at( 1, 3 )
        + at( 0, 0 ) * at( 2, 1 ) * at( 3, 2 ) * at( 1, 3 )

        + at( 3, 0 ) * at( 1, 1 ) * at( 0, 2 ) * at( 2, 3 )
        - at( 1, 0 ) * at( 3, 1 ) * at( 0, 2 ) * at( 2, 3 )
        - at( 3, 0 ) * at( 0, 1 ) * at( 1, 2 ) * at( 2, 3 )
        + at( 0, 0 ) * at( 3, 1 ) * at( 1, 2 ) * at( 2, 3 )

        + at( 1, 0 ) * at( 0, 1 ) * at( 3, 2 ) * at( 2, 3 )
        - at( 0, 0 ) * at( 1, 1 ) * at( 3, 2 ) * at( 2, 3 )
        - at( 2, 0 ) * at( 1, 1 ) * at( 0, 2 ) * at( 3, 3 )
        + at( 1, 0 ) * at( 2, 1 ) * at( 0, 2 ) * at( 3, 3 )

        + at( 2, 0 ) * at( 0, 1 ) * at( 1, 2 ) * at( 3, 3 )
        - at( 0, 0 ) * at( 2, 1 ) * at( 1, 2 ) * at( 3, 3 )
        - at( 1, 0 ) * at( 0, 1 ) * at( 2, 2 ) * at( 3, 3 )
        + at( 0, 0 ) * at( 1, 1 ) * at( 2, 2 ) * at( 3, 3 );
}



Math4f Math4f::transposed( )
{
    Math4f matrixTransposed;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrixTransposed.at( i, j ) = at( j, i );
        }
    }
    return matrixTransposed;
}



Math4f::~Math4f( )
{
}
