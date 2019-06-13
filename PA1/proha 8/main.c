#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar
{
    struct TCar              * m_Next;
    char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TCar              * m_Car;
    char                     * m_Name;
} TEMPLOYEE;

typedef struct TOffice
{
    TEMPLOYEE                * m_Emp;
    TCAR                     * m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */

TOFFICE          * initOffice   ()
{
    TOFFICE *n = NULL;

    n = ( TOFFICE * ) malloc( sizeof( TOFFICE ) );

    n->m_Emp = NULL;
    n->m_Car = NULL;

    return n;
}

void               addEmployeeWithCar  ( TOFFICE * office, TCAR * Car, const char * name )
{
    if( office->m_Emp != NULL )
    {
        TEMPLOYEE *n = NULL;

        n = ( TEMPLOYEE * ) malloc( sizeof( TEMPLOYEE ) );

        n->m_Name = strdup( name );
        n->m_Car = Car;
        n->m_Next = office->m_Emp;

        office->m_Emp = n;
    }
    else
    {
        office->m_Emp = ( TEMPLOYEE *) malloc( sizeof( TEMPLOYEE ) );
        office->m_Emp->m_Name = strdup( name );
        office->m_Emp->m_Car = Car;
        office->m_Emp->m_Next = NULL;
    }

}

void               addEmployee  ( TOFFICE         * office,
                                 const char      * name )
{
    if( office->m_Emp != NULL )
    {
        TEMPLOYEE *n = NULL;

        n = ( TEMPLOYEE * ) malloc( sizeof( TEMPLOYEE ) );

        n->m_Name = strdup( name );
        n->m_Car = NULL;
        n->m_Next = office->m_Emp;

        office->m_Emp = n;
    }
    else
    {
        office->m_Emp = ( TEMPLOYEE *) malloc( sizeof( TEMPLOYEE ) );
        office->m_Emp->m_Name = strdup( name );
        office->m_Emp->m_Car = NULL;
        office->m_Emp->m_Next = NULL;
    }

}
void               addCar       ( TOFFICE         * office,
                                 const char      * model )
{
    //printf("---%s---\n", model);
    if(office->m_Car != NULL)
    {
        TCAR *n;

        n = ( TCAR * ) malloc( sizeof( TCAR ) );

        n->m_Model = strdup( model );
        n->m_Next = office->m_Car;

        office->m_Car = n;
    }
    else
    {
        office->m_Car = ( TCAR * ) malloc( sizeof( TCAR ) );
        office->m_Car->m_Model = strdup( model );
        office->m_Car->m_Next = NULL;
    }

}

TOFFICE          * cloneOffice  ( TOFFICE         * office )
{
    TEMPLOYEE * p = office->m_Emp;
    TCAR * p2 = office->m_Car;

    TEMPLOYEE * last_emp = office->m_Emp;
    TCAR * last_car = office->m_Car;


    TOFFICE * new_list = initOffice();

    if ( office == NULL ){
        return NULL;
    }

    int len2 = 0;
    int i = 0, j = 0;

    if( last_car )
    {
        len2 = 1;

        while(last_car->m_Next != 0)
        {
            last_car = last_car->m_Next;
            ++len2;
        }

    }

    for (i = len2; i > 0; --i)
    {
        p2 = office->m_Car;

        for (j = 1; j < i; ++j)
        {
            p2 = p2->m_Next;
        }
        //printf("%s\n", p2->m_Model);
        addCar ( new_list, p2->m_Model);
    }

//    printf("-->%s\n", new_list->m_Car->m_Model);
//    printf("-->%s\n", new_list->m_Car->m_Next->m_Model);
//
//    printf("<--%s\n", office->m_Car->m_Model);
//    printf("<--%s\n", office->m_Car->m_Next->m_Model);


    TCAR * n_p = new_list->m_Car;

//    printf("<--%s\n", n_p->m_Model);
//    printf("<--%s\n", n_p->m_Next->m_Model);

    int len = 0;

    if( last_emp )
   {
       len = 1;

       while(last_emp->m_Next != 0)
       {
           last_emp = last_emp->m_Next;
           ++len;
       }
   }

    for (i = len; i > 0; --i)
    {
        p = office->m_Emp;

        for (j = 1; j < i; ++j)
        {
            p = p->m_Next;
        }

        if( p->m_Car != NULL ){
            TCAR * current_car = office->m_Car;
            TCAR * current_car2 = n_p;
            while( current_car ){
                if ( current_car == p->m_Car ){
                    addEmployeeWithCar(new_list, current_car2, p->m_Name);
                    break;
                }
                current_car = current_car->m_Next;
                current_car2 = current_car2->m_Next;
            }

        }
        else{
            addEmployee ( new_list, p->m_Name );
        }
    }

    return new_list;
}
void               freeOffice   ( TOFFICE         * office )
{
    TEMPLOYEE *tmp_T;
    TCAR *tmp_C;

    while ( office->m_Car )
    {
        tmp_C = office->m_Car->m_Next;

        free( office->m_Car->m_Model );

        office->m_Car->m_Next = NULL;
        free( office->m_Car );

        office->m_Car = tmp_C;
        tmp_C = NULL;

        free( tmp_C );
    }

    while ( office->m_Emp )
    {
        tmp_T = office->m_Emp->m_Next;

        free( office->m_Emp->m_Name );

        office->m_Emp->m_Car = NULL;
        free( office->m_Emp->m_Car );

        office->m_Emp->m_Next = NULL;
        free( office->m_Emp );

        office->m_Emp = tmp_T;
        tmp_T = NULL;

        free( tmp_T );
    }

    free( office );
}

void listprint(TOFFICE *lst)
{
    struct TEmployee *p;
    p = lst->m_Emp;
    do
    {
        printf("%s ", p->m_Name);
        if( p->m_Car != NULL )
        {
            printf(" - %s ", p->m_Car->m_Model);
        }
        p = p->m_Next;
    }
    while (p != NULL);
    printf("\n");
    struct TCar *p1;
    p1 = lst->m_Car;
    if ( p1 == NULL )
    {
        return;
    }
    do
    {
        printf("%s ", p1->m_Model);
        p1 = p1->m_Next;
    }
    while (p1 != NULL);
    printf("\n\n\n\n");
}


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TOFFICE * a, *b;
    char tmp[100];

    assert ( sizeof ( TOFFICE ) == 2 * sizeof ( void * ) );
    assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
    assert ( sizeof ( TCAR ) == 2 * sizeof ( void * ) );
    a = initOffice ();
    addEmployee ( a, "Peter" );
    addEmployee ( a, "John" );
    addEmployee ( a, "Joe" );
    addEmployee ( a, "Maria" );
    addCar ( a, "Skoda Octavia" );
    addCar ( a, "VW Golf" );
    a -> m_Emp -> m_Car = a -> m_Car;
    a -> m_Emp -> m_Next -> m_Next -> m_Car = a -> m_Car -> m_Next;
    a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = a -> m_Car;
    assert ( a -> m_Emp
            && ! strcmp ( a -> m_Emp -> m_Name, "Maria" )
            && a -> m_Emp -> m_Car == a -> m_Car );
    assert ( a -> m_Emp -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Joe" )
            && a -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
            && a -> m_Emp -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
            && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( a -> m_Car
            && ! strcmp ( a -> m_Car -> m_Model, "VW Golf" ) );
    assert ( a -> m_Car -> m_Next
            && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( a -> m_Car -> m_Next -> m_Next == NULL );
    b = cloneOffice ( a );
    strncpy ( tmp, "Moe", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Victoria", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Peter", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Citroen C4", sizeof ( tmp ) );
    addCar ( a, tmp );
  //  listprint(a);
//    listprint(b);
    b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = b -> m_Car -> m_Next -> m_Next;
   // listprint(a);
//    //listprint(b);
    assert ( a -> m_Emp
            && ! strcmp ( a -> m_Emp -> m_Name, "Peter" )
            && a -> m_Emp -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Victoria" )
            && a -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "Moe" )
            && a -> m_Emp -> m_Next -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
            && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
            && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
            && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
            && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next -> m_Next );
////    listprint(a);
////    listprint(b);
      assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
     && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
     && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( a -> m_Car
            && ! strcmp ( a -> m_Car -> m_Model, "Citroen C4" ) );
    assert ( a -> m_Car -> m_Next
            && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "VW Golf" ) );
    assert ( a -> m_Car -> m_Next -> m_Next
            && ! strcmp ( a -> m_Car -> m_Next -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( a -> m_Car -> m_Next -> m_Next -> m_Next == NULL );
      assert ( b -> m_Emp
     && ! strcmp ( b -> m_Emp -> m_Name, "Maria" )
     && b -> m_Emp -> m_Car == b -> m_Car );
     assert ( b -> m_Emp -> m_Next
     && ! strcmp ( b -> m_Emp -> m_Next -> m_Name, "Joe" )
     && b -> m_Emp -> m_Next -> m_Car == NULL );
     assert ( b -> m_Emp -> m_Next -> m_Next
     && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
     && b -> m_Emp -> m_Next -> m_Next -> m_Car == b -> m_Car -> m_Next );
     assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next
     && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
     && b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
     assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     assert ( b -> m_Car
     && ! strcmp ( b -> m_Car -> m_Model, "VW Golf" ) );
     assert ( b -> m_Car -> m_Next
     && ! strcmp ( b -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
     assert ( b -> m_Car -> m_Next -> m_Next == NULL );
    freeOffice ( a );
    freeOffice ( b );
    return 0;
}
#endif /* __PROGTEST__ */
