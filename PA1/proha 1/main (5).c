#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <float.h>

#define DBL_EPSILON 0.000000001

struct CCoord{
    double  c_X;
    double  c_Y;
};

struct CTriangle{
    struct  CCoord A;
    struct  CCoord B;
    struct  CCoord C;
    double  FirstSide;
    double  SecondSide;
    double  ThirdSide;
    int     error;
};

struct CTriangle ReadTriangle(){
    double CheckFirstEl = -228;
    struct CTriangle Triangle;
    if( scanf("\n { \n %lf", &CheckFirstEl) != 1)
    {
        Triangle.error = -1;
    }
    if ( CheckFirstEl == -228 ){
        double x1, y1, x2, y2, z1, z2;
        char c1, c2;
        if ( scanf("[\n%lf\n;\n%lf\n]\n,\n[\n%lf\n;\n%lf\n]\n,\n[\n%lf\n;\n%lf\n%c\n%c", &x1, &y1, &x2, &y2, &z1, &z2, &c1, &c2) != 8 || c1 != ']' || c2 != '}' ){
            Triangle.error = -1;
        }
        else{
            Triangle.error = 1;
        }
        Triangle.A.c_X = x1;
        Triangle.A.c_Y = y1;
        Triangle.B.c_X = x2;
        Triangle.B.c_Y = y2;
        Triangle.C.c_X = z1;
        Triangle.C.c_Y = z2;
        Triangle.FirstSide = sqrt( pow( ( Triangle.A.c_X - Triangle.B.c_X ), 2 ) + pow( ( Triangle.A.c_Y - Triangle.B.c_Y ), 2 ) );
        Triangle.SecondSide = sqrt( pow( ( Triangle.C.c_X - Triangle.B.c_X ), 2 ) + pow( ( Triangle.C.c_Y - Triangle.B.c_Y ), 2 ) );
        Triangle.ThirdSide = sqrt( pow( ( Triangle.A.c_X - Triangle.C.c_X ), 2 ) + pow( ( Triangle.A.c_Y - Triangle.C.c_Y ), 2 ) );
    }
    else{
        double B, C;
        char c1;
        if ( scanf("\n,\n%lf\n,\n%lf\n%c", &B, &C, &c1) != 3 || c1 != '}'){
            Triangle.error = -1;
        }
        else if ( CheckFirstEl <= 0 || B <= 0 || C <= 0 ){
            Triangle.error = -1;
        }
        else{
            Triangle.error = 1;
        }
        Triangle.FirstSide = CheckFirstEl;
        Triangle.SecondSide = B;
        Triangle.ThirdSide = C;
    }
    return Triangle;
}

int CheckTriangke(struct CTriangle Triangle){
    if ( fabs( Triangle.FirstSide + Triangle.SecondSide - Triangle.ThirdSide ) <= DBL_EPSILON * fabs(Triangle.FirstSide + Triangle.SecondSide + Triangle.ThirdSide) ){
        return 1;
    }
    if ( fabs( Triangle.FirstSide + Triangle.ThirdSide - Triangle.SecondSide ) <= DBL_EPSILON * fabs(Triangle.FirstSide + Triangle.SecondSide + Triangle.ThirdSide) ){
        return 1;
    }
    if ( fabs( Triangle.ThirdSide + Triangle.SecondSide - Triangle.FirstSide ) <= DBL_EPSILON * fabs(Triangle.FirstSide + Triangle.SecondSide + Triangle.ThirdSide) ){
        return 1;
    }
    return 0;
}

int CheckSidesQuality(double Side1, double Side2){
    if ( fabs(Side1 - Side2) <= DBL_EPSILON * fabs(Side1 + Side2) ){
        return 1;
    }
    return 0;
}

int CheckEquality(struct CTriangle T1, struct CTriangle T2){
    if ( CheckSidesQuality(T1.FirstSide, T2.FirstSide) || CheckSidesQuality(T1.FirstSide, T2.SecondSide) || CheckSidesQuality(T1.FirstSide, T2.ThirdSide) ){
        if ( CheckSidesQuality(T1.SecondSide, T2.FirstSide) || CheckSidesQuality(T1.SecondSide, T2.SecondSide) || CheckSidesQuality(T1.SecondSide, T2.ThirdSide) ){
            if ( CheckSidesQuality(T1.ThirdSide, T2.FirstSide) || CheckSidesQuality(T1.ThirdSide, T2.SecondSide) || CheckSidesQuality(T1.ThirdSide, T2.ThirdSide) ){
                return 0;
            }
        }
    }
    return 1;
}

int CheckPerimeter(struct CTriangle T1, struct CTriangle T2){
    if ( fabs( T1.FirstSide + T1.SecondSide + T1.ThirdSide - T2.FirstSide - T2.SecondSide - T2.ThirdSide ) <= DBL_EPSILON * fabs(T1.FirstSide + T1.SecondSide + T1.ThirdSide + T2.FirstSide + T2.SecondSide + T2.ThirdSide) ){
        return 0;
    }
    return 1;
}

int GetNumberOfTriangleWithBP(struct CTriangle T1, struct CTriangle T2){
    if ( ( T1.FirstSide + T1.SecondSide + T1.ThirdSide ) - ( T2.FirstSide + T2.SecondSide + T2.ThirdSide ) > DBL_EPSILON * fabs (T1.FirstSide + T1.SecondSide + T1.ThirdSide + T2.FirstSide + T2.SecondSide + T2.ThirdSide) ){
        return 1;
    }
    return 2;
}


int main(int argc, const char * argv[]) {
    printf("Trojuhelnik #1:\n");
    struct CTriangle FirstT = ReadTriangle();
    if ( FirstT.error == -1 ){
        printf("Nespravny vstup.\n");
        return 1;
    }
    if ( CheckTriangke(FirstT) == 1 ){
        printf("Neplatny trojuhelnik.\n");
        return 1;
    }
    printf("Trojuhelnik #2:\n");
    struct CTriangle SecondT = ReadTriangle();
    if ( SecondT .error == -1 ){
        printf("Nespravny vstup.\n");
        return 1;
    }
    if ( CheckTriangke(SecondT) == 1 ){
        printf("Neplatny trojuhelnik.\n");
        return 1;
    }
    if ( CheckEquality(FirstT, SecondT) == 0 ){
        printf("Trojuhelniky jsou shodne.\n");
        return 0;
    }
    if ( CheckPerimeter(FirstT, SecondT) == 0 ){
        printf("Trojuhelniky nejsou shodne, ale maji stejny obvod.\n");
        return 0;
    }
    printf("Trojuhelnik #%d ma vetsi obvod.\n", GetNumberOfTriangleWithBP(FirstT, SecondT));
    return 0;
}
