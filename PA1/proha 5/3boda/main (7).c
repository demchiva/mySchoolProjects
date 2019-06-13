#include <stdio.h>
#include <stdlib.h>

struct Price{
    double value;
    int from;
    int before;
};

struct Tax{
    char name;
    struct Price * Prices;
    int max;
    int size;
};

void CalculateResult(int Req1, int Req2, struct Tax Taxes[], int number){
    printf("%d - %d:", Req1, Req2);
    if ( Req2 < Req1 ){
        int Req = Req2;
        Req2 = Req1;
        Req1 = Req;
    }
    int cnt = 0;
    int i = 0, j = 0;
    for(i = 0; i < number; i++){
        double result = 0;
        int r1 = Req1;
        int r2 = Req2;
        for(j = 0; j < Taxes[i].size; j++){
            if ( Taxes[i].Prices[j].from <= r1 && Taxes[i].Prices[j].before <= r2 && Taxes[i].Prices[j].before >= r1 ){
                result = result + ( Taxes[i].Prices[j].before - r1 ) * Taxes[i].Prices[j].value;
                r1 = Taxes[i].Prices[j].before;
            }
            else if( Taxes[i].Prices[j].from <= r1 && Taxes[i].Prices[j].before >= r2 ){
                result = result + ( r2 - r1 ) * Taxes[i].Prices[j].value;
                r1 = 0;
                r2 = r1;
            }
            if( r1 == r2 ){
                break;
            }
        }
        if( cnt > 0 && result > 0){
            printf(",");
        }
        if ( result != 0 ){
            printf(" %c=%lf", Taxes[i].name, result);
            cnt++;
        }
    }
    printf("\n");
}

int main() {
    struct Tax Taxes[30];
    int number = 0;
    int Error = 0;
    int i = 0, j = 0;
    
    printf("Myto:\n");
    char control;
    scanf(" %c", &control);
    if ( control != '{' ){
        printf("Nespravny vstup.\n");
        for(i = 0; i < number; i++){
            free(Taxes[i].Prices);
        }
        return 1;
    }
    int from = 0;
    int CurrentBefore = 0;
    
    while( 1 ){
        
        int before = 0;
        Error = scanf(" [ %d %c", &before, &control);
        CurrentBefore = CurrentBefore + before;
        if( before <= 0 || control != ':'){
            printf("Nespravny vstup.\n");
            for(i = 0; i < number; i++){
                free(Taxes[i].Prices);
            }
            return 1;
        }
        if( Error != 2 ){
            printf("Nespravny vstup.\n");
            for(i = 0; i < number; i++){
                free(Taxes[i].Prices);
            }
            return 1;
        }
        
        for(i = 0; i < number; i++){
            if( Taxes[i].max <= Taxes[i].size ){
                if ( Taxes[i].max < 100 ){
                    Taxes[i].max += 25;
                }
                else{
                    Taxes[i].max += Taxes[i].max / 2;
                }
                Taxes[i].Prices = (struct Price*) realloc(Taxes[i].Prices, Taxes[i].max*sizeof(*Taxes[number].Prices));
            }
            Taxes[i].Prices[Taxes[i].size].from = Taxes[i].Prices[Taxes[i].size - 1].before;
            Taxes[i].Prices[Taxes[i].size].before = CurrentBefore;
            Taxes[i].Prices[Taxes[i].size].value = Taxes[i].Prices[Taxes[i].size - 1].value;
            Taxes[i].size++;
        }
        
        while( 1 ){
            char name = ' ';
            double value = 0;
            Error = scanf(" %c = %lf", &name, &value);
            if( Error != 2 ){
                printf("Nespravny vstup.\n");
                for(i = 0; i < number; i++){
                    free(Taxes[i].Prices);
                }
                return 1;
            }
            
            if ( name < 'A' || name > 'Z' || value < 0 ){
                printf("Nespravny vstup.\n");
                for(i = 0; i < number; i++){
                    free(Taxes[i].Prices);
                }
                return 1;
            }
            
            int include = 0;
            
            for(i = 0; i < number; i++){
                if( Taxes[i].name == name ){
                    Taxes[i].Prices[Taxes[i].size - 1].value = value;
                    include = 1;
                    break;
                }
            }
            
            if( include == 0 ){
                Taxes[number].Prices = NULL;
                Taxes[number].max = 25;
                Taxes[number].Prices = (struct Price*) realloc(Taxes[number].Prices, Taxes[number].max * sizeof(*Taxes[number].Prices));
                
                if(Taxes[number].Prices == NULL)
                    return 2;
                
                Taxes[number].name = name;
                Taxes[number].Prices[0].before = from;
                Taxes[number].Prices[0].from = 0;
                Taxes[number].Prices[0].value = 0;
                
                Taxes[number].Prices[1].before = CurrentBefore;
                Taxes[number].Prices[1].from = from;
                Taxes[number].Prices[1].value = value;
                Taxes[number].size = 2;
                number++;
            }
            
            Error = scanf(" %c", &control);
            if ( Error != 1 ){
                printf("Nespravny vstup.\n");
                for(i = 0; i < number; i++){
                    free(Taxes[i].Prices);
                }
                return 1;
            }
            if ( control != ']' && control != ',' ){
                printf("Nespravny vstup.\n");
                for(i = 0; i < number; i++){
                    free(Taxes[i].Prices);
                }
                return 1;
            }
            else if( control == ']' ){
                break;
            }
        }
        for(i = 0; i < number; i++){
            
            if( Taxes[i].size > 1 ){
                if( Taxes[i].Prices[Taxes[i].size - 1].value == Taxes[i].Prices[Taxes[i].size - 2].value ){
                    Taxes[i].Prices[Taxes[i].size - 2].before = Taxes[i].Prices[Taxes[i].size - 1].before;
                    Taxes[i].size--;
                }
            }
        }
        from = CurrentBefore;
        Error = scanf(" %c", &control);
        if ( Error != 1 ){
            printf("Nespravny vstup.\n");
            for(i = 0; i < number; i++){
                free(Taxes[i].Prices);
            }
            return 1;
        }
        if ( control != '}' && control != ',' ){
            printf("Nespravny vstup.\n");
            for(i = 0; i < number; i++){
                free(Taxes[i].Prices);
            }
            return 1;
        }
        else if( control == '}' ){
            break;
        }
        
    }
    
    for(i = 0; i < number; ++i)
    {
        for(j = number - 1; j > i; --j)
        {
            if ( Taxes[j].name < Taxes[j-1].name )
            {
                struct Tax t = Taxes[j - 1];
                Taxes[j - 1] = Taxes[j];
                Taxes[j] = t;
            }
        }
    }
    
//        for(int i = 0; i < number; i++){
//            printf("----------------------------------\n");
//            printf("%c:\n", Taxes[i].name);
//            for(int j = 0; j < Taxes[i].size; j++){
//                printf("%d - %d : %lf\n", Taxes[i].Prices[j].from, Taxes[i].Prices[j].before, Taxes[i].Prices[j].value);
//            }
//        }
//        printf("----------------------------------\n\n");
    
    
    printf("Hledani:\n");
    int Req1 = 0, Req2 = 0;
    while ( ( Error = scanf("%d %d", &Req1, &Req2 ) ) != EOF )
    {
        if ( Error != 2 )
        {
            printf("Nespravny vstup.\n");
            for(i = 0; i < number; i++){
                free(Taxes[i].Prices);
            }
            return 1;
        }
        if ( Req1 < 0 || Req2 < 0 || Req1 == Req2 || Req1 > CurrentBefore || Req2 > CurrentBefore )
        {
            printf("Nespravny vstup.\n");
            for(i = 0; i < number; i++){
                free(Taxes[i].Prices);
            }
            return 1;
        }
        CalculateResult(Req1, Req2, Taxes, number);
        
    }
    for(i = 0; i < number; i++){
        free(Taxes[i].Prices);
    }
    return 0;
}
