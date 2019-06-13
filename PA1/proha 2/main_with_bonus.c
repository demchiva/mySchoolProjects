#include <stdio.h>
#include <math.h>

char digit(int num)
{
    switch (num)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    default:
        return 'Z';
    }
    return 'Z';
}

long long int GetLength(int SysNum, long long int LowerInterval, long long int UpperInterval)
{
    int length = ((int)(log(LowerInterval)/log(SysNum)) + 1);

    if(LowerInterval == 0)
    {
        length = 1;
    }

    long long int i = LowerInterval, k = pow(SysNum, length) - 1;
    long long int total_length = 0;//length;

    if(LowerInterval != UpperInterval)
    {

        while(i <= UpperInterval)
        {
            //i++;

            if(i <= k)
            {
                total_length += length;
            }
            else
            {
                length ++;
                k = pow(SysNum, length) - 1;
                total_length += length;
                //i--;
            }
            i++;
        }

        if(SysNum == 10)
        {
           total_length--;
        }

    } else total_length = length;


    return total_length;
}

long long int GetLengthV2(int SysNum, long long int LowerInterval, long long int UpperInterval)
{
    long long int LowerLength = ((int)(log(LowerInterval)/log(SysNum)) + 1);
    long long int UpperLength = ((int)(log(UpperInterval)/log(SysNum)) + 1);

    if(LowerInterval == 0)
    {
        LowerLength = 1;
    }

    long long int TotalLength = LowerLength;

    if(LowerLength == UpperLength)
    {
        TotalLength = ((UpperInterval - LowerInterval + 1) * LowerLength);
        return TotalLength;
    }

    while(LowerLength <= UpperLength)
    {
       long long int temp = pow(SysNum, LowerLength) - 1;
       // printf("temp: %d\n", temp);

        if(temp < UpperInterval)
        {
           TotalLength = TotalLength + (temp - LowerInterval) * LowerLength;
            //printf("TotalLength: %d\n", TotalLength);

        }
        else
        {
            TotalLength = TotalLength + (UpperInterval - LowerInterval) * LowerLength;
            //printf("TotalLength2: %d\n", TotalLength);
        }

        LowerInterval = temp;

        LowerLength++;
    }

    return TotalLength;

}

int GetInt(int a, int p, char *s)
{
    int num = (int)a;
    int rest = num % p;
    num /= p;
    if (num == 0)
    {
        s[0] = digit(rest);
        return 1;
    }
    int k = GetInt(num, p, s);
    s[k++] = digit(rest);
    return k;
}

int CalculateAll(int SysNum, long long int LowerInterval, long long int UpperInterval, int Type)
{
    int Result1 = 0;
    int Result2 = 0;
    int Result3 = 0;
    int CounterForResult3 = 0;
    for(int i = LowerInterval; i < UpperInterval + 1; i++)
    {
        char NumberInNewSN[1000] = { 0 };
        int Length = GetInt((int)i, SysNum, NumberInNewSN);
        for (int j = 0; j < Length; j++)
        {
            if ( (NumberInNewSN[j] >= '0' && NumberInNewSN[j] <= '9') || NumberInNewSN[j] == 'Z' )
            {
                Result1++;
            }
            if ( NumberInNewSN[j] == '0' )
            {
                CounterForResult3++;
                Result2++;
            }
            if ( NumberInNewSN[j] != '0' )
            {
                if ( CounterForResult3 > Result3 )
                {
                    Result3 = CounterForResult3;
                }
                CounterForResult3 = 0;
            }
        }
    }
    if ( Type == 1 )
    {
        return Result1;
    }
    else if ( Type == 2 )
    {
        return Result2;
    }

    if ( CounterForResult3 > Result3 )
    {
        return CounterForResult3;
    }
    return Result3;
}

int CalculateZeros(int SysNum, int LowerInterval, int UpperInterval)
{
    int Result = 0;
    for(int i = LowerInterval; i < UpperInterval + 1; i++)
    {
        char NumberInNewSN[1000] = { 0 };
        int Length = GetInt((int)i, SysNum, NumberInNewSN);
        for (int i = 0; i < Length; i++)
        {
            if ( NumberInNewSN[i] == '0' )
            {
                Result++;
            }
        }
    }
    return Result;
}

struct Input
{
    int SysNum;
    long long int UpperInterval;
    long long int LowerInterval;
    char Command;
    int Erorr;
};

int main(int argc, const char * argv[])
{
    char FirstEl;
    int checkFirstEl;
    int NumberOfIteration = 0;
    printf("Zadejte intervaly:\n");
    checkFirstEl = scanf(" %c", &FirstEl );
    while ( ( checkFirstEl ) != EOF )
    {
        struct Input input;
        input.Command = 'a';
        input.LowerInterval = 0;
        input.UpperInterval = 0;
        input.SysNum = 10;
        if ( checkFirstEl != 1 )
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        if ( FirstEl == 'r' )
        {
            int SysNum;
            if ( scanf("\n%d", &SysNum) != 1 )
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            else
            {
                if ( SysNum <= 36 && SysNum >= 2 )
                {
                    input.SysNum = SysNum;
                }
                else
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                long long int UpperInterval;
                long long int LowerInterval;
                char Command;
                if ( scanf("\n:\n<\n%lli\n; \n%lli\n> \n%c", &LowerInterval, &UpperInterval, &Command) != 3 )
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                else
                {
                    if ( LowerInterval <= UpperInterval )
                    {
                        if ( LowerInterval >= 0 && UpperInterval >= 0 )
                        {
                            input.LowerInterval = LowerInterval;
                            input.UpperInterval = UpperInterval;
                        }
                        else
                        {
                            printf("Nespravny vstup.\n");
                            return 1;
                        }
                    }
                    else
                    {
                        printf("Nespravny vstup.\n");
                        return 1;
                    }
                    if ( Command == 'l' || Command == 'z' || Command == 's' )
                    {
                        input.Command = Command;
                    }
                    else
                    {
                        printf("Nespravny vstup.\n");
                        return 1;
                    }
                }
            }
        }
        if ( FirstEl == '<' )
        {
            input.SysNum = 10;
            long long int UpperInterval = 0;
            long long int LowerInterval = 0;
            char Command;
            if ( scanf("\n%lli\n; \n%lli\n> \n%c", &LowerInterval, &UpperInterval, &Command ) != 3 )
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            else
            {
                if ( LowerInterval <= UpperInterval )
                {
                    if ( LowerInterval >= 0 && UpperInterval >= 0 )
                    {
                        input.LowerInterval = LowerInterval;
                        input.UpperInterval = UpperInterval;
                    }
                    else
                    {
                        printf("Nespravny vstup.\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                if ( Command == 'l' || Command == 'z' || Command == 's' )
                {
                    input.Command = Command;
                }
                else
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
            }
        }
        if ( NumberOfIteration == 0 )
        {
            if ( !( FirstEl == '<' || FirstEl == 'r' ) )
            {
                printf("Nespravny vstup.\n");
                NumberOfIteration++;
                return 1;
            }

            if ( input.Command == 'l' )
            {
                printf("Cifer: %lli\n",/* CalculateAll(input.SysNum, input.LowerInterval, input.UpperInterval, 1)*/GetLengthV2(input.SysNum, input.LowerInterval, input.UpperInterval));
            }
            else if ( input.Command == 'z' )
            {
                printf("Nul: %d\n", CalculateAll(input.SysNum, input.LowerInterval, input.UpperInterval, 2));
            }
            else
            {
                printf("Sekvence: %d\n", CalculateAll(input.SysNum, input.LowerInterval, input.UpperInterval, 3));
            }
            NumberOfIteration++;
        }
        else
        {
            NumberOfIteration = 0;
        }
        checkFirstEl = scanf("%c", &FirstEl );
    }
    return 0;
}
