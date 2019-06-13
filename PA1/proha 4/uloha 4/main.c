#include <stdio.h>
#include <math.h>
#define N 10000

int GetMinLength(int cnt_of_billboards, int *billboards, int count)
{
    if(cnt_of_billboards == 0 || cnt_of_billboards == 1)
    {
        return -2;
    }

    if(cnt_of_billboards - 1 > count)
    {
        return -1;
    }

    int ret_value = 0;

    return ret_value;
}

int main()
{
    printf("Mozna umisteni:\n");

    char first_char, second_char;
    int billboards[N];
    int count = 0, cnt_of_billboards;
    int ret_value, control;

    while(1)
    {
        if(count == 0)
        {
            control = scanf("%c %d %c", &first_char, &billboards[count], &second_char);

            if(control != 3)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
        }
        else
        {
            control = scanf(" %d %c", &billboards[count], &second_char);

             if(control != 2)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
        }

        if(billboards[count] < 0 || (second_char != ',' && second_char != '}')
                                 || first_char != '{' || count > 1000000)
        {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if(second_char == '}')
        {
            break;
        }

        count++;

    }

    printf("count: %d\n", count);

        printf("Pocet billboardu:\n");

        while(scanf(" %d", &cnt_of_billboards) != EOF)
        {
            ret_value = GetMinLength(cnt_of_billboards, &billboards[0], count);

            if(ret_value == -1)
            {
               printf("N/A\n");
            }

            if(ret_value == -2)
            {
                printf("Vzdalenost: inf\n");
            }

            if(ret_value >= 0)
            {
                printf("Vzdalenost: %d\n", ret_value);
            }

        }

    return 0;
}
