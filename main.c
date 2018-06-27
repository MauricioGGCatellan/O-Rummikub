#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


struct s_peca{
char peca[4];
struct s_peca *anterior;
};

int main()
{
    struct s_peca **maos;
    struct s_peca *mesa;
    int n_players;
    int a_ints[5];
    int a_ints_sem_ordenar[5];
    int i;
    int j;
    int k;
    int salva_j[5];
    int bandeira;
    char *deck[106];
    char resposta [3];
    char *a[5];




//MENU
while(resposta[0] != '3'){
        printf(">>>RUMMIKUB<<<\n");
        printf("1. Jogar - modo aleatorio\n");
        printf("2. Jogar - modo controlado\n");
        printf("3. Sair\n");
        scanf("%s", resposta);
        fflush(stdin);
        if(resposta[0] == '1'){
//alocação de memória para o deck
for(i = 0; i < 106; i++){
    deck[i] = (char *) malloc(4*sizeof(char));
}

//INICIALIZAÇÃO DAS PEÇAS NO DECK
inicializa_deck(deck);

//PRINTS INICIAIS E CRIACAO DE VETORES DAS MAOS DE JOGADORES!  //obs: o 14 é usado porque os jogadores começam com 14 peças na mão.
        printf("Jogo comecando! Diga o numero de jogadores que participarao (1 a 5): ");
        scanf("%d", &n_players);
        if(n_players > 5 || n_players < 1){
            printf("Numero invalido de jogadores!\n");
            continue;
        }


         maos =(struct s_peca **) malloc(n_players*sizeof(struct s_peca *));
        for(i = 0; i < n_players; i ++){
            maos[i] = (struct s_peca *) malloc(14*sizeof(struct s_peca));
        }

        //EMBARALHAMENTO E TESTES DE QUEM JOGA PRIMEIRO
        //embaralhamento
        shuffle(deck, 106);
        if(n_players != 1){
        //escolha de pecas que decidirao quem joga primeiro
        bandeira = 1;
        printf("Inicio de jogo! Escolham uma peca para que seja decidido o primeiro a jogar (peca de 0 a 105)\n");
        while(bandeira){
        bandeira = 0;
        for(i = 0; i < n_players; i++){
            scanf("%d", &j);
            if( j < 0 || j >105){
                printf("Valor invalido. Escolha novamente\n");
                i--;
                continue;
            }
            salva_j[i] = j;
            a[i] = (char *) malloc(4*sizeof(char));
            a[i][0] = deck[j][0];
        }

        for(k = n_players - 1; k >= 1; k--){
            if(salva_j[k] == salva_j[k-1]){
                printf("Dois jogadores escolheram a mesma peca! Escolham novamente!\n");
                bandeira = 1;
                break;
            }
        }

           if(bandeira == 1){
            continue;
           }

        //testes para ver qual peça é maior, e, portanto, para ver quem joga primeiro.
        //preparação e ordenação
        for(i = 0; i < n_players; i++){
            a_ints[i] = conversao(a[i][0]);
            a_ints_sem_ordenar[i] = a_ints[i];
        }
        bubble_sort(a_ints, n_players);

        //teste de empate
        if(a_ints[n_players - 1] == a_ints[n_players - 2]){
            printf("Empate nas pecas! Escolham novamente!\n");
            bandeira = 1;
            continue;
        }
        }
        //checagem de quem joga primeiro
        bandeira = 1;
        i = 0;
        while(bandeira && i < n_players){
            if(a_ints_sem_ordenar[i] == a_ints[n_players - 1]){
                printf("Jogador %d joga primeiro!\n", i+1);
                bandeira = 0;
                }
        i++;                                      //i JOGA PRIMEIRO
        }
        //liberação de memória do vetor a
        for(j = 0; j < n_players; j++){
            free(a[j]);
        }
        }


           //PRIMEIRAS JOGADAS



           }


}
free(maos);
return 0;
}





