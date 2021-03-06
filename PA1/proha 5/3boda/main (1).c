#include <stdio.h>  /* standart library */
#include <stdlib.h> /* malloc, free, qsort */

/*
 * The program reads information about the boards. After that,
 * there are requests for counting for a particular area where we have to output
 * the result for each type of tax.
 *
 * The program demonstrates the use of structures, mapping and field size (stretching).
 *
 * In this version, the program works well, uses efficient algorithms for both allocation
 * and modality.
 */

/*
 * A structure that represents payment characteristic
 */
struct Price{
    double  value;      // Payment value
    int     from;       // From wich distance is active
    int     before;     // Till wich distance is active
};

/*-----------------------------------------------------------------------------------------------*/

/*
 * A structure that represents tax characteristic
 */
typedef struct Tax{
    char            name;        // Tax name
    struct Price   *Prices;      // Tax's payments dynamic array
    int             max;         // Tax's payments dynamic array max size (size <= max)
    int             size;        // Tax's payments dynamic array size
} Tax;

/*-----------------------------------------------------------------------------------------------*/

/*
 * Function for free memory
 * Complexity O(n)
 *
 * @param[in,out] (*Taxes)[30] - taxes array
 * @param[in] number - taxes array size
 */
void Free(struct Tax *Taxes, int number){
    int i = 0;
    for(i = 0; i < number; i++){
        free(Taxes[i].Prices);
    }
}

/*-----------------------------------------------------------------------------------------------*/

/*
 * Sorting array by letter
 * Complexity O(nˆ2)
 *
 * @param[in,out] (*Taxes)[30] - taxes array
 * @param[in] number - taxes array size
 */
void Sort(struct Tax *Taxes, int number)
{
    int i = 0, j = 0;
    for(i = 0; i < number; ++i){
        for(j = number - 1; j > i; --j){
            if ( Taxes[j].name < Taxes[j-1].name ){
                struct Tax t = Taxes[j - 1];
                Taxes[j - 1] = Taxes[j];
                Taxes[j] = t;
            }
        }
    }
}

/*-----------------------------------------------------------------------------------------------*/

/*
 * Function for reading input
 * Complexity O(n)
 *
 * @param[in,out] *Taxes - taxes array
 * @param[in,out] *number - taxes array size
 * @param[in,out] *CurrentBefore - current before value
 *
 * @return result - succesfull input or not
 */
int ReadInput(Tax *Taxes, int *number, int *CurrentBefore)
{
    char            control = ' ';     // Variable for symbol controlling
    int             Error = 0;         // Variable for error detection
    int             i = 0;             // Variable for array index

    *number = 0;

    scanf(" %c", &control);
    if ( control != '{' ){
        return 1;
    }
    int from = 0;           // Variable for saving previous 'before' value
    *CurrentBefore = 0;     // Variable for current 'till result'

    while( control != '}' ){

        int before = 0;    // Variable for before result
        Error = scanf(" [ %d %c", &before, &control);
        *CurrentBefore = *CurrentBefore + before;
        if( before <= 0 || control != ':' || Error != 2){
            return 1;
        }

        for(i = 0; i < *number; i++){

            /*
             Memory reallocation for tax's payments
             */
            if( Taxes[i].max <= Taxes[i].size ){
                if ( Taxes[i].max < 100 ){
                    Taxes[i].max += 25;
                }
                else{
                    Taxes[i].max += Taxes[i].max / 2;
                }
                Taxes[i].Prices = (struct Price*) realloc(Taxes[i].Prices, Taxes[i].max*sizeof(*Taxes[*number].Prices));
            }

            /*
             Create new payment and
             set the previous values of payment to the current one
             */
            Taxes[i].Prices[Taxes[i].size].from = Taxes[i].Prices[Taxes[i].size - 1].before;
            Taxes[i].Prices[Taxes[i].size].before = *CurrentBefore;
            Taxes[i].Prices[Taxes[i].size].value = Taxes[i].Prices[Taxes[i].size - 1].value;
            Taxes[i].size++;
        }

        while( control != ']' ){
            char    name = ' ';   // Variable for tax name
            double  value = 0;    // Variable for new payment value
            Error = scanf(" %c = %lf", &name, &value);

            if ( name < 'A' || name > 'Z' || value < 0 || Error != 2 ){
                return 1;
            }

            int include = 0; // Variable for detecte tax name including in taxes array

            /*
             Cycle through the array of taxes
             If we already have this type of tax, adding new value
             Set include flag to 1
             */
            for(i = 0; i < *number; i++){
                if( Taxes[i].name == name ){
                    Taxes[i].Prices[Taxes[i].size - 1].value = value;
                    include = 1;
                    break;
                }
            }

            if( include == 0 ){    // Case if we have not this type of tax

                /*
                 Realocate memory for fist elements
                 */
                Taxes[*number].Prices = NULL;
                Taxes[*number].max = 25;
                Taxes[*number].Prices = (struct Price*) realloc(Taxes[*number].Prices, Taxes[*number].max * sizeof(*Taxes[*number].Prices));

                if (Taxes[*number].Prices == NULL){
                    return 1;
                }

                /*
                 Creating new tax type in tax array
                 */
                Taxes[*number].name = name;
                Taxes[*number].Prices[0].before = from;
                Taxes[*number].Prices[0].from = 0;
                Taxes[*number].Prices[0].value = 0;

                Taxes[*number].Prices[1].before = *CurrentBefore;
                Taxes[*number].Prices[1].from = from;
                Taxes[*number].Prices[1].value = value;
                Taxes[*number].size = 2;
                (*number)++;
            }

            Error = scanf(" %c", &control);

            if ( Error != 1 || ( control != ']' && control != ',' ) ){
                return 1;
            }
        }

        /*
         Combine the same payments
         */
        for(i = 0; i < *number; i++){
            if( Taxes[i].size > 1 ){
                if( Taxes[i].Prices[Taxes[i].size - 1].value == Taxes[i].Prices[Taxes[i].size - 2].value ){
                    Taxes[i].Prices[Taxes[i].size - 2].before = Taxes[i].Prices[Taxes[i].size - 1].before;
                    Taxes[i].size--;
                }
            }
        }
        /*
         Change from variable to current before
         for next first elements in tax array
         */
        from = *CurrentBefore;
        Error = scanf(" %c", &control);

        if ( Error != 1 || ( control != '}' && control != ',' ) ){
            return 1;
        }
    }

    return 0;
}

/*-----------------------------------------------------------------------------------------------*/

/*
 * Function for result calculation
 * Complexity O(nˆ2)
 *
 * @param[in] Req1, Req2 - requested range
 * @param[in] Taxes[] - taxes array
 * @param[in] number - taxes array size
 *
 * @note output the answer on stdout
 */
void CalculateResult(int Req1, int Req2, struct Tax Taxes[], int number){
    printf("%d - %d:", Req1, Req2);
    if ( Req2 < Req1 ){             // Switch requested range if first number > second number of range
        int Req = Req2;
        Req2 = Req1;
        Req1 = Req;
    }

    int cnt = 0; // Variable for counting number of answers
    int i = 0, j = 0;

    /*
     Cycle through the array of taxes to calculate the result for each type of tax
     */
    for(i = 0; i < number; i++){

        double      result = 0;     // Variable for result
        int         r1 = Req1;      // Local first request number variable
        int         r2 = Req2;      // Local second request number variable

        /*
         Cycle through the array of payments for current type of tax
         */
        for(j = 0; j < Taxes[i].size; j++){

            /* If payment covers part of the range */
            if ( Taxes[i].Prices[j].from <= r1 && Taxes[i].Prices[j].before <= r2 && Taxes[i].Prices[j].before >= r1 ){
                result = result + ( Taxes[i].Prices[j].before - r1 ) * Taxes[i].Prices[j].value;
                r1 = Taxes[i].Prices[j].before;
            }

            /* If payment covers full range */
            else if( Taxes[i].Prices[j].from <= r1 && Taxes[i].Prices[j].before >= r2 ){
                result = result + ( r2 - r1 ) * Taxes[i].Prices[j].value;
                r1 = r2;
            }

            /* Condition for cycle breaking */
            if( r1 == r2 ){
                break;
            }
        }

        /* Output ',' if we have more than 1 answer */
        if( cnt > 0 && result > 0){
            printf(",");
        }

        /* Output result */
        if ( result != 0 ){
            printf(" %c=%lf", Taxes[i].name, result);
            cnt++;
        }
    }
    printf("\n");
}

/*-----------------------------------------------------------------------------------------------*/

int main() {

    Tax             Taxes[30];      // Taxes array
    int             number;         // Taxes array number
    int             Error = 0;      // Variable for error detection
    int             CurrentBefore;  // Variable for current value of before

    printf("Myto:\n");

    if( ReadInput(Taxes, &number, &CurrentBefore) )
    {
        printf("Nespravny vstup.\n");
        Free(Taxes, number);
        return 1;
    }
    Sort(Taxes, number);
    printf("Hledani:\n");
    int Req1 = 0, Req2 = 0;         // Variable for requested range
    while ( ( Error = scanf("%d %d", &Req1, &Req2 ) ) != EOF )
    {
        if ( Error != 2 )
        {
            printf("Nespravny vstup.\n");
            Free(Taxes, number);
            return 1;
        }
        if ( Req1 < 0 || Req2 < 0 || Req1 == Req2 || Req1 > CurrentBefore || Req2 > CurrentBefore )
        {
            printf("Nespravny vstup.\n");
            Free(Taxes, number);
            return 1;
        }
        CalculateResult(Req1, Req2, Taxes, number);
    }
    Free(Taxes, number);
    return 0;
}
