#include <stdio.h>
#include <stdlib.h>
#define N 1000
void Sort(int *data, int size) {
    int i, j;
    for(i = 0; i < size; ++i) {
        for(j = size - 1; j > i; --j) {
            if ( data[j] < data[j-1] ) {
                int t = data[j - 1];
                data[j - 1] = data[j];
                data[j] = t;
            }
        }
    }
}

void FormArray(int *data, int size){
    int dif = data[0];
    for(int i = 0; i < size; i++){
        data[i] = data[i] - dif;
        //printf("%d ", data[i]);
    }
}

int CalculateMin(int data[N], int size, int num){
    int Parts[N];
    int Step = (data[size - 1] / ( num - 1));
    printf(" %d / %d = %d\n",data[size - 1], ( num - 1), Step);
    int CurrentN = 0;
    for (int i = 0; i < num; i++){
        Parts[i] = CurrentN;
        CurrentN = CurrentN + Step;
        //printf("%d ", Parts[i]);
    }
    int Answers[N];

    for(int i = 0; i < num; i++){
        int a = data[0];
        for(int j = 0; j < size; j++){
            if ( abs(data[j] - Parts[i]) < abs(a - Parts[i]) ){
                if ( Answers[i - 1] != data[j]){
                    a = data[j];
                }
            }
        }
        Answers[i] = a;
    }
    int ans = Answers[1] - Answers[0];
    for (int i = 0; i < num - 1; i++){
        if ( ( Answers[i+1] - Answers[i] ) < ans ){
            ans = Answers[i+1] - Answers[i];
        }
    }

    if(ans < 0)
    {
      ans = 0;
    }

    return ans;
}

int main(int argc, const char * argv[]) {

    int ArrayM[N];
    int NumberOfM = 0;
    int NumberOfBill;

    printf("Mozna umisteni:\n");
    char FirstS;
    scanf("%c", &FirstS);
    if ( FirstS != '{' ){
        printf("Nespravny vstup.\n");
        return 1;
    }
    int i = 0;
    while ( 1 ){
        if ( scanf("%d", &ArrayM[i]) != 1 ){
            printf("Nespravny vstup.\n");
            return 1;
        }
        if (ArrayM[i] < 0 || ArrayM[i] > N){
            printf("Nespravny vstup.\n");
            return 1;
        }
        i++;
        char Sym;
        scanf("\n%c", &Sym);
        if ( Sym == '}' ){
            NumberOfM = i;
            break;
        }
        else if ( Sym == ',' ){

        }
        else{
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    if ( NumberOfM == 1 ){
        printf("Nespravny vstup.\n");
        return 1;
    }

    Sort(ArrayM, NumberOfM);
    FormArray(ArrayM, NumberOfM);

    printf("Pocet billboardu:\n");
    int checkFirstEl;
    while ( ( checkFirstEl = scanf("%d", &NumberOfBill ) ) != EOF ){
        if ( checkFirstEl != 1 ){
            printf("Nespravny vstup.\n");
            return 1;
        }
        if ( NumberOfBill < 0 ){
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ( NumberOfBill == 1 || NumberOfBill == 0 ){
            printf("Vzdalenost: inf\n");
        }
        else if ( NumberOfBill > NumberOfM ){
            printf("N/A\n");
        }
        else{
            printf("Vzdalenost: %d\n", CalculateMin(ArrayM, NumberOfM, NumberOfBill));
        }

    }
    return 0;
}
