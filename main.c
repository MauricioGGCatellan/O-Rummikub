#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_peca{
char peca[4];
struct s_peca *anterior;
struct s_peca *proximo;
};

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




void prints_de_jogada(char resp[], struct s_peca *maos){
printf("O que deseja fazer?\n");
printf("1. Usar pecas de sua mao na mesa\n");
printf("2. Manipular as pecas da mesa\n");
printf("3. Comprar uma peca\n");
printf("4. Encerrar a vez\n");

//prints de mao:
struct s_peca *mao;
mao = maos;

printf("Mao: ");

while(mao != NULL){
printf("%s ", mao->peca);
mao = mao->anterior;
}

printf("\n");
scanf("%s", resp);
fflush(stdin);
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

void draw(int *quantia_mao, struct s_peca *mao, int *pos_deck, char *deck[]){
int pos;
pos = *pos_deck;
strcpy(mao->peca, deck[pos]);
*pos_deck = pos + 1;
*quantia_mao = *quantia_mao + 1;
}

int teste_combinacao_valida(int nums_a_jogar[], int k, struct s_peca *mao, int *soma_points, struct s_peca *pecas_a_jogar[13]){
                                                                                                                                                //13 pois o número máximo de peças em uma combinação é 13
//SE RETORNA 0, É SEQUÊNCIA; SE RETORNA 1, É GRUPO; SE RETORNA 2, NÃO É VÁLIDO

//struct s_peca *tmp_p;
int i;
int j;
int bandeira;
int possivel_sequencia[13];


/*for(i = 0; i < k; i++){
        tmp_p = mao;
    if(nums_a_jogar[i] == 0){
        pecas_a_jogar[i] = mao;
    } else{
    for(j = 0; j < nums_a_jogar[i]; j++){
    tmp_p = tmp_p->anterior;
    }
    pecas_a_jogar[i] = tmp_p;
    }
}*/

// (I) Sequência
if(!(k<3)){
bandeira = 1;
for( i = 0; i < k ; i++){
    for(j = k - i - 1; j > 0; j--){
        if(!( (pecas_a_jogar[i]->peca[0] == '*') || (pecas_a_jogar[i]->peca[0] == '*') )){
        if(pecas_a_jogar[i]->peca[1] != pecas_a_jogar[i+j]->peca[1]){
        bandeira = 0;
    }
        }
    }
}
if(bandeira == 1){
for(i = 0; i < k ; i++){
possivel_sequencia[i] = conversao(pecas_a_jogar[i]->peca[0]);
}
//bubble_sort(possivel_sequencia, k);
int swap;
int c;
int d;
 for (c = 0 ; c < k - 1; c++)
  {
    for (d = 0 ; d < k - c - 1; d++)
    {
      if ( possivel_sequencia[d] > possivel_sequencia[d+1])
      {
        swap = possivel_sequencia[d];
        possivel_sequencia[d] = possivel_sequencia[d+1];
        possivel_sequencia[d+1] = swap;
      }
    }
  }

for(i = 1; i < k ; i++){
    if(!( (possivel_sequencia[i] == 20) || (possivel_sequencia[i-1] == 20) )){ //teste só realizado para caso nenhuma das peças seja coringa.
    if(possivel_sequencia[i] - possivel_sequencia[i-1] != 1){
        bandeira = 0;
    }
    }
}
if(bandeira == 1){
    for(i = 0; i < k; i++){
        *soma_points = *soma_points + possivel_sequencia[i];
    }
    return 0;
}
}
}

//(II)Grupo
if(k != 3 && k != 4){
    return 2;
}
else{
    bandeira = 1;
    for( i = 0; i < k ; i++){
    for(j = k - i - 1; j > 0; j--){
        if(pecas_a_jogar[i]->peca[1] == pecas_a_jogar[i+j]->peca[1]){
        bandeira = 0;
    }

    }
}
    if(bandeira == 1){
    for(i = 0; i < k ; i++){
        possivel_sequencia[i] = conversao(pecas_a_jogar[i]->peca[0]);
}
    for( i = 0; i < k ; i++){
    for(j = k - i - 1; j > 0; j--){
        if(!( (possivel_sequencia[i] == 20) || (possivel_sequencia[i] == 20) )){
        if(possivel_sequencia[i] != possivel_sequencia[i+j]){
        bandeira = 0;
    }
        }
    }
}
    if(bandeira == 1){
        for(i = 0; i < k ; i++){
            *soma_points = *soma_points + possivel_sequencia[i];
        }
        return 1;
    }

    }
    return 2;
}
}

void coloca_e_printa_a_mesa(struct s_peca *mesa, struct s_peca *pecas_a_jogar[], int k){
struct s_peca *tmp_p;
int sequencia[13];
int i;
int d;
char swap[4];


for(i = 0; i < k; i++){
sequencia[i] = conversao(pecas_a_jogar[i]->peca[0]);
}

//bubble sort que ordena o vetor de peças
 for (i = 0 ; i < k-1; i++)
  {
    for (d = 0 ; d < k - i - 1 ; d++)
    {
      if ( sequencia[d] > sequencia[d+1])
      {
        strcpy(swap, pecas_a_jogar[d]->peca);
        strcpy(pecas_a_jogar[d]->peca, pecas_a_jogar[d+1]->peca);
        strcpy(pecas_a_jogar[d+1]->peca, swap);
      }
    }
  }

tmp_p = mesa;
i = 0;
//prints:
printf("Mesa: ");
while(tmp_p != NULL){
strcpy(tmp_p->peca, pecas_a_jogar[i]->peca);
printf("%s", tmp_p->peca);
tmp_p = tmp_p->anterior;
i++;
}
}


int main()
{
    struct s_peca *maos[5];
    struct s_peca *mesa;
    struct s_peca *tmp_p;
    struct s_peca *tmp_p_mesa;
    struct s_peca *pecas_a_jogar[13];
    int n_players;
    int a_ints[5];
    int a_ints_sem_ordenar[5];
    int i;
    int j;
    int k;
    int salva_j[5];
    int bandeira;
    int pos_deck;
    int first_player;
    int pos_player;
    int quantia_mao[5];
    int soma_points;
    int nums_a_jogar[13];
    int quantia_mesa;
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

        //alocação inicial de memória para as mãos dos jogadores.
        for(i = 0; i < n_players; i ++){
            for(j = 0; j < 14; j++){
            maos[i] = (struct s_peca *) malloc(sizeof(struct s_peca));
            if(maos[i] == NULL){
            printf("Problemas na alocacao de memoria\n");
            break;
            }
            if(j == 0){
                maos[i]->anterior = NULL;
            } else{
                maos[i]->anterior = tmp_p;
            }
            tmp_p = maos[i];
            }
            if(maos[i] == NULL){
                break;
            }
        }

        if(maos[i] == NULL){
            continue;
        }

        //EMBARALHAMENTO E TESTES DE QUEM JOGA PRIMEIRO
        if(n_players != 1){
        //escolha de pecas que decidirao quem joga primeiro
        bandeira = 1;
        shuffle(deck, 106);
        printf("As pecas estao na mesa! Escolham uma peca para que seja decidido o primeiro a jogar (peca de 0 a 105)\n");
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

        printf("Pecas escolhidas: \n");
        for(i = 0; i < n_players; i++){
            printf("Jogador %d: ", i+1);
            printf("%s\n", deck[salva_j[i]]);
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
            for(j = 0; j < n_players; j++){
                free(a[j]);
            }
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
                pos_player = i;
                first_player = i;
                }
        i++;                                      //i JOGA PRIMEIRO
        }
        //liberação de memória do vetor a
        for(j = 0; j < n_players; j++){
            free(a[j]);
        }
 }

        //OS JOGADORES RECEBEM AS MÃOS INICIAIS
        shuffle(deck, 106);
        pos_deck = 0;

        for(i = 0; i < n_players; i++){
            inicializa_mao(maos[i], deck, &pos_deck);
            quantia_mao[i] = 14;
        }

        printf("Jogadores preencheram as maos alternadamente! Inicio das jogadas!\n");
        quantia_mesa = 0;

        //PRIMEIRAS JOGADAS

        printf("Vez do jogador %d\n", pos_player + 1);
        soma_points = 0;
        bandeira = 1;
        while(pos_player != first_player || bandeira == 1){
        bandeira = 0;
        while(resposta[0] != '4' && soma_points < 30){

        //print de mão inclusa na função "prints_de_jogada"
        prints_de_jogada(resposta, maos[pos_player]);
        if(resposta[0] == '1'){
        printf("Diga que pecas deseja jogar (as pecas estao, da esquerda para a direita, em ordem crescente, e a primeira peca e a 0). Entre com -1 para terminar as escolhas\n");
        k = 0;
        while(nums_a_jogar[k-1] != -1 && k <13){
        scanf("%d", &nums_a_jogar[k]);
        k++;
        }
        if(k == 13){
            k++;
            printf("Numero maximo de pecas a jogar atingido!\n");
        }

        for(i = 0; i < k-1; i++){
        tmp_p = maos[pos_player];
    if(nums_a_jogar[i] == 0){
        pecas_a_jogar[i] = maos[pos_player];
    } else{
    for(j = 0; j < nums_a_jogar[i]; j++){
        tmp_p = tmp_p->anterior;
    }
        pecas_a_jogar[i] = tmp_p;
    }
}

        j = teste_combinacao_valida(nums_a_jogar, k-1, maos[pos_player], &soma_points, pecas_a_jogar);
        for(i = 0; i < k -1; i++){
            printf("%s", pecas_a_jogar[i]->peca);
        }
        if(j == 2){
            printf("Combinacao invalida!\n");
            continue;
        } else if(j == 0){
            printf("Sequencia posta na mesa!\n");
            //alocação de memória para peça na mesa
            for(i = 0; i < k - 1; i++){
            mesa = (struct s_peca*) malloc(sizeof(struct s_peca));
            if(mesa == NULL){
                printf("Problema na alocacao de memoria\n");
                break;
            }
            quantia_mesa++;
            if(quantia_mesa == 1){
                mesa->anterior = NULL;
            } else{
            mesa->anterior = tmp_p_mesa;
            }
            tmp_p_mesa = mesa;
            }
                //criar função que coloca na mesa e a printa
            if(mesa != NULL){
            coloca_e_printa_a_mesa(mesa, pecas_a_jogar, k-1);
            }
        } else if(j == 1){
            printf("Grupo posto na mesa!\n");
              //alocação de memória para peça na mesa
               for(i = 0; i < k - 1; i++){
            mesa = (struct s_peca*) malloc(sizeof(struct s_peca));
            if(mesa == NULL){
                printf("Problema na alocacao de memoria\n");
                break;
            }
            quantia_mesa++;
            if(quantia_mesa == 1){
                mesa->anterior = NULL;
            } else{
            mesa->anterior = tmp_p_mesa;
            }
            tmp_p_mesa = mesa;
            }
            //criar a função citada acima
            if(mesa != NULL){
            coloca_e_printa_a_mesa(mesa, pecas_a_jogar, k-1);
            }
        }
        }
        /*else if(resposta[0] == '2'){


        }*/
        //compra de peça
        else if(resposta[0] == '3'){
        tmp_p =maos[pos_player];
        maos[pos_player] = (struct s_peca *) malloc(sizeof(struct s_peca));
        maos[pos_player]->anterior = tmp_p;
        draw(&quantia_mao[pos_player], maos[pos_player], &pos_deck, deck);
        } else if(resposta[0] == '4'){
        if(soma_points < 30){
            printf("Acao invalida! A primeira jogada deve somar pelo menos 30 pontos!\n");
        }

        }
  }
  pos_player++;
  if(pos_player == n_players){
    pos_player = 0;
  }
}

//AS JOGADAS RESTANTES!
/*while(1){

}*/


}
        }





for(i = 0; i < n_players; i++){
    free(maos[i]);
}

return 0;
}













