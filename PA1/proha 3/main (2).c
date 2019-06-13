#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

unsigned long long int OneCase( unsigned long long int length,
                                unsigned int        s1,
                                unsigned int        bulkhead,
                                unsigned int      * c1)
{
    if ( (length - bulkhead) % ( s1 + bulkhead ) != 0 )
    {
        return 0;
    }
    *c1 = (unsigned int)((length - bulkhead) / ( s1 + bulkhead ));

    return 1;
}


unsigned long long int TwoCases( unsigned long long int length,
                                 unsigned int        s1,
                                 unsigned int        s2,
                                 unsigned int        bulkhead,
                                 unsigned int      * c1,
                                 unsigned int      * c2)
{
    int b1, b2, opportunity = 0;

    b1 = (length - bulkhead) / (s1 + bulkhead);

    b2 = (length - bulkhead) / (s2 + bulkhead);

    int i, temp_length = length - bulkhead, c_control;

    for(i = 0; i <= b1; i++)
    {
            double kz;
            kz = (temp_length - (s1 + bulkhead) * i ) / (s2 + bulkhead);
            c_control = kz;

            if(c_control < 0)
            {
                break;
            }

            int cops = i * (s1 + bulkhead) + c_control * (s2 + bulkhead) - temp_length;
            if(c_control == kz && c_control <= b2 && cops == 0)
            {
                *c1 = i;
                *c2 = c_control;
                opportunity++;
            }

    }

    return opportunity;
}

unsigned long long int hyperloop                           ( unsigned long long int length,
        unsigned int        s1,
        unsigned int        s2,
        unsigned int        s3,
        unsigned int        bulkhead,
        unsigned int      * c1,
        unsigned int      * c2,
        unsigned int      * c3 )
{
    unsigned long long int opportunity = 0;

    if(bulkhead > length || (s1 > length && s2 > length && s3 > length) || (s1 == 0 && s2 == 0 && s3 == 0 && bulkhead != length) || (s1 == 0 && s2 == 0 && s3 == 0 && bulkhead == 0))
    {
        return 0;
    }

    if((s1 == 0 && s2 == 0 && s3 > length && bulkhead != length) || (s1 == 0 && s2 > length && s3 == 0 && bulkhead != length) || (s1 > length && s2 == 0 && s3 == 0 && bulkhead != length))
    {
        return 0;
    }

    if((s1 == 0 && s2 > length && s3 > length) || (s1 > length && s2 > length && s3 > length && bulkhead != length) || (s1 > length && s2 == 0 && s3 > length && bulkhead != length) || (s1 > length && s2 > length && s3 == 0 && bulkhead != length))
    {
        return 0;
    }

    if((s1 == 0 && s2 == 0 && s3 == 0 && bulkhead == length) || (s1 > length && s2 > length && s3 > length && bulkhead == length ) )
    {
        *c1 = 0;
        *c2 = 0;
        *c3 = 0;
        return 1;
    }

    if(s1 == s2 && s1 == s3)
    {
        unsigned int f1 = 0;
        unsigned long long int Res = OneCase(length, s1, bulkhead, &f1);
        *c1 = f1;

        return Res;
    }

    if ( s1 != 0 && s2 == 0 && s3 == 0 )
    {
        unsigned int f1 = 0;
        unsigned long long int Res = OneCase(length, s1, bulkhead, &f1);
        if(Res)
        {
        * c1 = f1;
        * c2 = 0;
        * c3 = 0;
        }
        return Res;
    }

    if ( s1 == 0 && s2 != 0 && s3 == 0 )
    {
        unsigned int f1 = 0;
        unsigned long long int Res = OneCase(length, s2, bulkhead, &f1);
        if(Res)
        {
        * c1 = 0;
        * c2 = f1;
        * c3 = 0;
        }
        return Res;
    }

    if ( s1 == 0 && s2 == 0 && s3 != 0 )
    {
        unsigned int f1 = 0;
        unsigned long long int Res = OneCase(length, s3, bulkhead, &f1);
        if(Res)
        {
        * c1 = 0;
        * c2 = 0;
        * c3 = f1;
        }
        return Res;
    }

    if ( s1 == s2 )
    {
        if ( s3 == 0 )
        {
            unsigned int f1 = 0;
            unsigned long long int Res = OneCase(length, s1, bulkhead, & f1);
            * c1 = f1;
            * c2 = 0;
            * c3 = 0;
            return Res;
        }
        else
        {
            unsigned int f1 = 0, f2 = 0;
            unsigned long long int Res = TwoCases(length, s1, s3, bulkhead, &f1, &f2);
            * c1 = f1;
            * c2 = 0;
            * c3 = f2;
            return Res;
        }
    }
    else if ( s1 == s3 )
    {
        if ( s2 == 0 )
        {
            unsigned int f1 = 0;
            unsigned long long int Res = OneCase(length, s1, bulkhead, & f1);
            * c1 = f1;
            * c2 = 0;
            * c3 = 0;
            return Res;
        }
        else
        {
            unsigned int f1 = 0, f2 = 0;
            unsigned long long int Res = TwoCases(length, s1, s2, bulkhead, &f1, &f2);
            * c1 = f1;
            * c2 = f2;
            * c3 = 0;
            return Res;
        }
    }
    else if ( s2 == s3 )
    {
        if ( s1 == 0 )
        {
            unsigned int f1 = 0;
            unsigned long long int Res = OneCase(length, s2, bulkhead, & f1);
            * c2 = f1;
            * c1 = 0;
            * c3 = 0;
            return Res;
        }
        else
        {
            unsigned int f1 = 0, f2 = 0;
            unsigned long long int Res = TwoCases(length, s1, s3, bulkhead, &f1, &f2);
            * c1 = f1;
            * c2 = 0;
            * c3 = f2;
            return Res;
        }
    }

    if ( s1 == 0 ){
        unsigned int f1 = 0, f2 = 0;
        unsigned long long int Res = TwoCases(length, s2, s3, bulkhead, &f1, &f2);
        * c1 = 0;
        * c2 = f1;
        * c3 = f2;
        return Res;
    }

    else if ( s2 == 0 ){
        unsigned int f1 = 0, f2 = 0;
        unsigned long long int Res = TwoCases(length, s1, s3, bulkhead, &f1, &f2);
        * c1 = f1;
        * c2 = 0;
        * c3 = f2;
        return Res;
    }
    else if ( s3 == 0 ){
        unsigned int f1 = 0, f2 = 0;
        unsigned long long int Res = TwoCases(length, s1, s2, bulkhead, &f1, &f2);
        * c1 = f1;
        * c2 = f2;
        * c3 = 0;
        return Res;
    }

    int b1, b2, b3;

    if(s1 != 0)
        b1 = (length - bulkhead) / (s1 + bulkhead);
    else
        b1 = 0;

    if(s2 != 0)
        b2 = (length - bulkhead) / (s2 + bulkhead);
    else
        b2 = 0;

    if(s3 != 0)
        b3 = (length - bulkhead) / (s3 + bulkhead);
    else
        b3 = 0;

    int i, j, sum = 0, temp_length = length - bulkhead, c_control;

    for(i = 0; i <= b1; i++)
    {
        sum = temp_length - (s1 + bulkhead) * i;

        for(j = 0; j <= b2; j++)
        {
            double kz;
            kz = (sum - (s2 + bulkhead) * j ) / (s3 + bulkhead);
            c_control = kz;

            if(c_control < 0)
            {
                break;
            }

            int cops = i * (s1 + bulkhead) + j * (s2 + bulkhead) + c_control * (s3 + bulkhead) - temp_length;
            if(c_control == kz && c_control <= b3 && cops == 0)
            {
                *c1 = i;
                *c2 = j;
                *c3 = c_control;
                opportunity++;
            }
        }
    }

    return opportunity;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    unsigned int c1, c2, c3;
    assert ( hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 ) == 42
             && 4 * c1 + 7 * c2 + 5 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 100 );
    assert ( hyperloop ( 12345, 8, 3, 11, 3, &c1, &c2, &c3 ) == 82708
             && 8 * c1 + 3 * c2 + 11 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 12345 );
    c1 = 8;
    c2 = 9;
    c3 = 10;
    assert ( hyperloop ( 127, 12, 8, 10, 0, &c1, &c2, &c3 ) == 0
             && c1 == 8
             && c2 == 9
             && c3 == 10 );
    assert ( hyperloop ( 127, 12, 8, 10, 3, &c1, &c2, &c3 ) == 4
             && 12 * c1 + 8 * c2 + 10 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 127 );
    assert ( hyperloop ( 100, 35, 0, 0, 10, &c1, &c2, &c3 ) == 1
             && c2 == 0
             && c3 == 0
             && 35 * c1 + 10 * ( c1 + 1 ) == 100 );
    assert ( hyperloop(100, 0, 0, 0, 10, &c1, &c2, &c3 ) == 0  );
    assert ( hyperloop ( 100, 35, 0, 35, 10, &c1, &c2, &c3 ) == 1
             && c2 == 0
             && 35 * c1 + 35 * c3 + 10 * ( c1 + c3 + 1 ) == 100 );
    assert ( hyperloop ( 100, 35, 35, 35, 10, &c1, &c2, &c3 ) == 1
             && 35 * c1 + 35 * c2 + 35 * c3 + 10 * ( c1 + c2 + c3 + 1 ) == 100 );

    c1 = 42;
    c2 = 43;
    c3 = 44;
    assert ( hyperloop ( 9, 1, 2, 3, 10, &c1, &c2, &c3 ) == 0
             && c1 == 42
             && c2 == 43
             && c3 == 44 );

    assert ( hyperloop(100, 0, 0, 1, 0, &c1, &c2, &c3) == 1
             && c1 == 0
             && c2 == 0
             && c3 == 100 );
    assert ( hyperloop ( 40, 10, 10, 20, 0, &c1, &c2, &c3 ) == 3 );
    assert ( hyperloop ( 70, 35, 35, 0, 0, &c1, &c2, &c3 ) == 1 );
     assert(hyperloop ( 2556, 852, 1704, 1704, 0, &c1, &c2, &c3 ) == 2 );
     assert(hyperloop ( 504, 0, 0, 0, 504, &c1, &c2, &c3 ) == 1 );

     assert ( hyperloop ( 226, 0, 0, 0, 226, &c1, &c2, &c3 ) == 1 && 0 * c1 + 0 * c2 + 0 * c3 + 226 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 226, 0, 0, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 0 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 0, 226, 0, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 226 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 0, 0, 226, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 0 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 0, 226, 226, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 226 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 226, 0, 226, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 0 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 226, 226, 226, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 226 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
c1 = 42; c2 = 43; c3 = 44;
assert ( hyperloop ( 9, 0, 0, 0, -1, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( -9, 0, 0, 3, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 0, 3, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 12, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 12, 12, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 12, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 12, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 12, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 12, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 4, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 4, 0, 0, 3, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 0, 0, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 0, 4, 5, 2, 7, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 3, 2, 0, 0, &c1, &c2, &c3 ) == 2 && 3 * c1 + 2 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 9, 3, 2, 14, 0, &c1, &c2, &c3 ) == 2 && 3 * c1 + 2 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 9, 3, 3, 3, 0, &c1, &c2, &c3 ) == 1 && 3 * c1 + 3 * c2 + 3 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 9, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 99999999, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 99999999 );
assert ( hyperloop ( 99999999, 99999997, 0, 0, 1, &c1, &c2, &c3 ) == 1 && 99999997 * c1 + 0 * c2 + 0 * c3 + 1 * ( c1 + c2 + c3 + 1 ) == 99999999 );
assert ( hyperloop ( 1869, 623, 1246, 1246, 0, &c1, &c2, &c3 ) == 2 && 623 * c1 + 1246 * c2 + 1246 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
assert ( hyperloop ( 1869, 1246, 623, 1246, 0, &c1, &c2, &c3 ) == 2 && 1246 * c1 + 623 * c2 + 1246 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
assert ( hyperloop ( 1869, 1246, 1246, 623, 0, &c1, &c2, &c3 ) == 2 && 1246 * c1 + 1246 * c2 + 623 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );

    return 0;
}
#endif /* __PROGTEST__ */
