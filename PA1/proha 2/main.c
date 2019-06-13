#include <stdio.h>

char digit(int num){
    switch (num) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        default: return 'Z';
    }
    return 'Z';
}

int GetInt(int a, int p, char *s)
{
    int num = (int)a;
    int rest = num % p;
    num /= p;
    if (num == 0)
    {
        s[0] = digit(rest); return 1;
    }
    int k = GetInt(num, p, s);
    s[k++] = digit(rest);
    return k;
}

int CalculateAll(int SysNum, int LowerInterval, int UpperInterval, int Type){
    int Result1 = 0;
    int Result2 = 0;
    int Result3 = 0;
    int CounterForResult3 = 0;
    for(int i = LowerInterval; i < UpperInterval + 1; i++){
        char NumberInNewSN[1000] = { 0 };
        int Length = GetInt((int)i, SysNum, NumberInNewSN);
        for (int j = 0; j < Length; j++){
            if ( (NumberInNewSN[j] >= '0' && NumberInNewSN[j] <= '9') || NumberInNewSN[j] == 'Z' ){
                Result1++;
            }
            if ( NumberInNewSN[j] == '0' ){
                CounterForResult3++;
                Result2++;
            }
            if ( NumberInNewSN[j] != '0' ){
                if ( CounterForResult3 > Result3 ){
                    Result3 = CounterForResult3;
                }
                CounterForResult3 = 0;
            }
        }
    }
    if ( Type == 1 ){
        return Result1;
    }
    else if ( Type == 2 ){
        return Result2;
    }

    if ( CounterForResult3 > Result3 ){
        return CounterForResult3;
    }
    return Result3;
}

int CalculateZeros(int SysNum, int LowerInterval, int UpperInterval){
    int Result = 0;
    for(int i = LowerInterval; i < UpperInterval + 1; i++){
        char NumberInNewSN[1000] = { 0 };
        int Length = GetInt((int)i, SysNum, NumberInNewSN);
        for (int i = 0; i < Length; i++){
            if ( NumberInNewSN[i] == '0' ){
                Result++;
            }
        }
    }
    return Result;
}

struct Input{
    int SysNum;
    int UpperInterval;
    int LowerInterval;
    char Command;
    int Erorr;
};

int main(int argc, const char * argv[]) {
    char FirstEl;
    int checkFirstEl;
    int NumberOfIteration = 0;
    printf("Zadejte intervaly:\n");
    checkFirstEl = scanf(" %c", &FirstEl );
    while ( ( checkFirstEl ) != EOF ){
        struct Input input;
        input.Command = 'a';
        input.LowerInterval = 0;
        input.UpperInterval = 0;
        input.SysNum = 10;
        if ( checkFirstEl != 1 ){
            printf("Nespravny vstup.\n");
            return 1;
        }
        if ( FirstEl == 'r' ){
            int SysNum;
            if ( scanf("\n%d", &SysNum) != 1 ){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if ( SysNum <= 36 && SysNum >= 2 ){
                    input.SysNum = SysNum;
                }
                else{
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                int UpperInterval;
                int LowerInterval;
                char Command;
                if ( scanf("\n:\n<\n%d\n; \n%d\n> \n%c", &LowerInterval, &UpperInterval, &Command) != 3 ){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                else{
                    if ( LowerInterval <= UpperInterval ){
                        if ( LowerInterval >= 0 && UpperInterval >= 0 ){
                            input.LowerInterval = LowerInterval;
                            input.UpperInterval = UpperInterval;
                        }else{
                            printf("Nespravny vstup.\n");
                            return 1;
                        }
                    }
                    else{
                        printf("Nespravny vstup.\n");
                        return 1;
                    }
                    if ( Command == 'l' || Command == 'z' || Command == 's' ){
                        input.Command = Command;
                    }
                    else{
                        printf("Nespravny vstup.\n");
                        return 1;
                    }
                }
            }
        }
        if ( FirstEl == '<' ){
            input.SysNum = 10;
            int UpperInterval = 0;
            int LowerInterval = 0;
            char Command;
            if ( scanf("\n%d\n; \n%d\n> \n%c", &LowerInterval, &UpperInterval, &Command ) != 3 ){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if ( LowerInterval <= UpperInterval ){
                    if ( LowerInterval >= 0 && UpperInterval >= 0 ){
                        input.LowerInterval = LowerInterval;
                        input.UpperInterval = UpperInterval;
                    }else{
                        printf("Nespravny vstup.\n");
                        return 1;
                    }
                }
                else{
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                if ( Command == 'l' || Command == 'z' || Command == 's' ){
                    input.Command = Command;
                }
                else{
                    printf("Nespravny vstup.\n");
                    return 1;
                }
            }
        }
        if ( NumberOfIteration == 0 ){
            if ( !( FirstEl == '<' || FirstEl == 'r' ) ){
                printf("Nespravny vstup.\n");
                NumberOfIteration++;
                return 1;
            }

            if ( input.Command == 'l' ){
                printf("Cifer: %d\n", CalculateAll(input.SysNum, input.LowerInterval, input.UpperInterval, 1));
            }
            else if ( input.Command == 'z' ){
                printf("Nul: %d\n", CalculateAll(input.SysNum, input.LowerInterval, input.UpperInterval, 2));
            }
            else{
                printf("Sekvence: %d\n", CalculateAll(input.SysNum, input.LowerInterval, input.UpperInterval, 3));
            }
            NumberOfIteration++;
        }
        else{
            NumberOfIteration = 0;
        }
        checkFirstEl = scanf("%c", &FirstEl );
    }
    return 0;
}
