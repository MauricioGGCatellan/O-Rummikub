#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions_and_struct_dec.h"

void inicializa_deck(char *deck[]){
    char n;
    int i;
    int j;
    n = '1';
    j = 0;
//'1' a '9'
for(i = 0; i<72; i++){
    deck[i][0] = n;
    deck[i][2] =  '\0';
    j++;
    if(j == 8){
        n++;
        j = 0;
    }
}

//'A' a 'D'
n = 'A';
j = 0;
for(i = 72; i < 104; i++){
    deck[i][0] = n;
    deck[i][2] = '\0';
    j++;
    if(j == 8){
        n++;
        j = 0;
    }
}

//símbolos
for(i = 0; i < 8; i += 2){
  for(j = 0; j <104; j+= 8){
    if(i == 0){
        deck[i + j][1] = '!';
        deck[i + j + 1][1] = '!';
    }
    if(i == 2){
        deck[i + j][1] = '@';
        deck[i + j + 1][1] = '@';
    }
    if(i == 4){
        deck[i + j][1] = '#';
        deck[i + j + 1][1] = '#';
    }
    if(i == 6){
        deck[i + j][1] = '$';
        deck[i + j + 1][1] = '$';
    }
  }
  }
  //coringas
    for (i = 104; i<106; i++){
        strcpy(deck[i], "**");
    }
}

void inicializa_deck_controlado(FILE *deck_controlado, char *deck[]){
long int i;
int j;
for(i = 0; i < 106; i++){
        if(i > 0){
        fflush(deck_controlado);
     fseek(deck_controlado, i*3, SEEK_SET);
     }
    for(j = 0; j < 2; j++){
     deck[i][j] = fgetc(deck_controlado);

    }

    deck[i][2] = '\0';
}

}

void shuffle(char *deck[], int n){
int i;
int j;
char t[4];
for(i=0; i < n; i++) {
            strcpy(t, deck[i]);
            j = rand() % n;
            strcpy(deck[i], deck[j]);
            strcpy(deck[j], t);
}
}

//conversão de caracteres presentes no hexadecimal para valores comparáveis.
int conversao(char a){
int b;
    if(a >='0' && a <='9'){
        b = (int) a - '0';
    }
    else if(a >= 'A' && a <= 'D'){
        b = (int) a - 'A' + 10;
    }
    else if(a == '*'){
        b = 20;
    }
    return b;

}

void bubble_sort(int a[], int n){
int swap;
int c;
int d;
 for (c = 0 ; c < n - 1; c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if ( a[d] > a[d+1])
      {
        swap = a[d];
        a[d] = a[d+1];
        a[d+1] = swap;
      }
    }
  }
}

void inicializa_mao(struct s_peca *maos, char *deck[], int *pos){

struct s_peca *mao;
mao = maos;
int position;
position = *pos;
while(mao != NULL){
    strcpy(mao->peca, deck[position]);
    mao = mao->anterior;
    position++;
}

*pos +=14;
}
