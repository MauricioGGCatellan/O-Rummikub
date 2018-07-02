#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions_and_struct_dec.h"

void prints_de_jogada(char resp[], struct s_peca *maos, int quantia_mesa, struct s_peca *mesa){
printf("O que deseja fazer?\n");
printf("1- Usar pecas de sua mao na mesa\n");
printf("2- Manipular as pecas da mesa\n");
printf("3- Comprar uma peca\n");                                    //o problema de prints pós colocar uma peça da mão na mesa pode estar aqui.
printf("4- Encerrar a vez\n");

//prints de mao:
struct s_peca *mao;
mao = maos;

printf("Mao: ");

while(mao != NULL){
printf("%s ", mao->peca);
mao = mao->anterior;
}

printf("\n");

//prints de mesa:
if(quantia_mesa > 0){
mao = mesa;
printf("Mesa: ");
while(mao != NULL){
printf("%s ", mao->peca);
mao = mao->anterior;
}
printf("\n");
}

scanf("%s", resp);
fflush(stdin);

}

void draw(int *quantia_mao, struct s_peca *mao, int *pos_deck, char *deck[]){
int pos;
pos = *pos_deck;
strcpy(mao->peca, deck[pos]);
*pos_deck = pos + 1;
*quantia_mao = *quantia_mao + 1;
}

int teste_combinacao_valida(int k, struct s_peca *pecas_a_jogar[13]){
                                                                                                                                                //13 pois o número máximo de peças em uma combinação é 13
//SE RETORNA 0, É SEQUÊNCIA; SE RETORNA 1, É GRUPO; SE RETORNA 2, NÃO É VÁLIDO

//struct s_peca *tmp_p;
int i;
int j;
int bandeira;
int possivel_sequencia[13];

// (I) Sequência
if(!(k<3)){
bandeira = 1;
for( i = 0; i < k ; i++){
    for(j = k - i - 1; j > 0; j--){
        if(!( (pecas_a_jogar[i]->peca[0] == '*') || (pecas_a_jogar[i+j]->peca[0] == '*') )){
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
//bubble_sort(possivel_sequencia, k);0
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
        if(!( (possivel_sequencia[i] == 20) || (possivel_sequencia[i+j] == 20) )){
        if(possivel_sequencia[i] != possivel_sequencia[i+j]){
        bandeira = 0;
    }
        }
    }
}
    if(bandeira == 1){
        return 1;
    }

    }
    return 2;
}
}

void prints_resp_1(int *k, int nums_a_jogar[], int quantia_mao, int *num_a_jogar, int *num_a_trocar, char resposta[3]){
int j;
int bandeira;

while(1){
printf("Deseja jogar uma nova combinacao (1) ou apenas uma peca(2) ?\n");
scanf("%s", resposta);
if(resposta[0] == '1'){
j = 2;
bandeira = 1;
printf("Diga que pecas deseja jogar (as pecas estao, da esquerda para a direita, em ordem crescente, e a primeira peca e a 0). Entre com -1 para terminar as escolhas\n");;
while(nums_a_jogar[j-2] != -1 && j <13){
        if(bandeira == 1){
            j = 1;
            bandeira = 0;
        }
        scanf("%d", &nums_a_jogar[j-1]);
        if(nums_a_jogar[j-1] < -1 || nums_a_jogar[j-1] >= quantia_mao){
            printf("Numero invalido!\n");
            continue;
        }
        if(nums_a_jogar[j-1] ==  -1){
            break;
        }
        j++;
}
if(j == 13){
        printf("Numero maximo de pecas a jogar atingido!\n");
}
*k = j;
break;
} else if(resposta[0] == '2'){
        printf("Que peca deseja jogar? (as pecas estao, da esquerda para a direita, em ordem crescente, e a primeira peca e a 0)\n");
        scanf("%d", num_a_jogar);

        printf("A que posicao da mesa deseja leva-la? (as pecas serao deslocadas para a direita)\n");
        scanf("%d", num_a_trocar);

        break;
} else{
printf("Opcao invalida\n");
}
}


}

int coloca_a_mesa(struct s_peca *mesa, struct s_peca *pecas_a_jogar[], int k, struct s_peca *mao, int *quantia_mao, int tam_sequencias[], int *pos_num_sequencias, int *soma_points, int bandeira_first_play){
struct s_peca *tmp_p;
struct s_peca *tmp_p2;
//int sequencia[13];
int i;
//int d;
int possivel_sequencia[13];
int ka;
int bandeira;
int bandeira2;
int quantidade_mao;
int pos_num_sequencia;
int soma_pontos;
//char swap[4];

soma_pontos = *soma_points;
bandeira2 = 0;
quantidade_mao = *quantia_mao;
ka = k;
pos_num_sequencia = *pos_num_sequencias;

////parte não funcionando como deveria

if(bandeira_first_play == 1){
 for(i = 0; i < k ; i++){
possivel_sequencia[i] = conversao(pecas_a_jogar[i]->peca[0]);
}

for(i = 0; i < k; i++){
soma_pontos = soma_pontos + possivel_sequencia[i];
}

}

tmp_p = mesa;
i = 0;
while(tmp_p != NULL && k > 0){        //pode estar passando k
strcpy(tmp_p->peca, pecas_a_jogar[i]->peca);
tmp_p = tmp_p->anterior;
i++;
k--;
}

//libera, da mão, as peças usadas
for(i = 0; i < ka; i++){
    tmp_p = mao;
    bandeira = 0;
    while(tmp_p->anterior != NULL){
        if(bandeira == 0){
            if(strcmp(pecas_a_jogar[i]->peca, tmp_p->peca) == 0){
                tmp_p2 = tmp_p;
                mao = mao->anterior;
                free(tmp_p2);
                bandeira2 = 1;
                quantidade_mao--;
                break;
            }

        }
         bandeira = 1;
        if(strcmp(pecas_a_jogar[i]->peca, tmp_p->anterior->peca) == 0){
            tmp_p2 = tmp_p->anterior;
            tmp_p->anterior = tmp_p->anterior->anterior;
            free(tmp_p2);
            quantidade_mao--;
            break;

        }
        tmp_p = tmp_p->anterior;
    }

}

*quantia_mao = quantidade_mao;
tam_sequencias[pos_num_sequencia] = ka;
*pos_num_sequencias = pos_num_sequencia + 1;
if(bandeira_first_play == 1){
*soma_points = soma_pontos;
}
if(bandeira2 == 1){
    return 1;
} else{return 0;}
}

int manipular_pecas_da_mesa(struct s_peca *mesa, int num_a_manipular, struct s_peca *peca_a_manipular, struct s_peca *peca_a_trocar, int tam_combinacoes[], int pos_num_combinacoes, int num_a_manipular2){
struct s_peca *tmp_p;
struct s_peca *tmp_p2;
struct s_peca *possivel_combinacao[13];
struct s_peca *possivel_combinacao2[13];
char tmp[4];
int i;
int j;
int k;
int k2;
int bandeira;
int soma_tam;

    strcpy(tmp, peca_a_trocar->peca);
    strcpy(peca_a_trocar->peca, peca_a_manipular->peca);
    strcpy(peca_a_manipular->peca, tmp);


//escolha do tamanho da combinação a ser analisada, baseada em informações salvas
//PARA PECA_A_TROCAR
soma_tam = 0;
bandeira = 0;
for(i = 0; i < pos_num_combinacoes; i++){

    if(num_a_manipular == soma_tam){
        bandeira = 1;
        k = i;
        break;
    }
  soma_tam = soma_tam + tam_combinacoes[i] ;

  }


if(bandeira == 0){
    return 2;
}

//PARA PECA_A_MANIPULAR
soma_tam = 0;
i = 0;
while(1){
    soma_tam  = soma_tam + tam_combinacoes[i] ;
    if(soma_tam > num_a_manipular2){
        break;
    }
    i++;
}


k2 = i ; //análise da combinação a partir da posição k2


tmp_p = mesa;
if(num_a_manipular == 0){
            peca_a_trocar= mesa;
} else{
for(j = 0; j < num_a_manipular; j++){
            tmp_p = tmp_p->anterior;
}
            peca_a_trocar = tmp_p;
}

//formação de vetor para testes de validez da combinação
//PARA PECA_A_TROCAR
for(i = 0;i < tam_combinacoes[k]; i++){
    tmp_p = peca_a_trocar;
    if(i == 0){
        possivel_combinacao[i] = peca_a_trocar;
    } else{ for(j = 0;j < i; j ++){
    tmp_p = tmp_p->anterior;
    if(tmp_p == NULL){
        break;
    }
    }
    if(tmp_p == NULL){
        i++;
        break;
    }
        possivel_combinacao[i] = tmp_p;

    }    //i é a quantia de peças da combinação possível
}

k = i; //(agora k também é)

//PARA PECA_A_MANIPULAR
tmp_p2 = peca_a_manipular;
tmp_p = mesa;
if(num_a_manipular2 == 0){
            peca_a_manipular= mesa;
            k2 = 0;
} else{
for(j = 0; j < soma_tam - tam_combinacoes[k2]; j++){
            tmp_p = tmp_p->anterior;
}
            peca_a_manipular = tmp_p;
}

                                          //SOMA_TAM - TAM_COMBINACOES[k2]
for(i = 0;i < tam_combinacoes[k2]; i++){
    tmp_p = peca_a_manipular;
    if(i == 0){
        possivel_combinacao2[i] = peca_a_manipular;
    } else{ for(j = 0;j < i; j ++){
    tmp_p = tmp_p->anterior;
    if(tmp_p == NULL){
        i++;
        break;
    }
    }
    if(tmp_p == NULL){
        break;
    }
        possivel_combinacao2[i] = tmp_p;

    }    //i é a quantia de peças da combinação possível
}



if(i < 3 || k < 3){
    //se não é quantia suficiente pra uma combinação válida, destroca as peças
    // falta movimentar os ponteiros antes de destrocar..
    strcpy(tmp, peca_a_trocar->peca);
    strcpy(peca_a_trocar->peca, tmp_p2->peca);
    strcpy(tmp_p2->peca, tmp);
    return 2;
} else
if( (teste_combinacao_valida(k, possivel_combinacao) == 0) && (teste_combinacao_valida(i, possivel_combinacao2) == 0)){

    return 0; //novas sequências obtidas
} else
if ( (teste_combinacao_valida(k, possivel_combinacao) == 1 ) && (teste_combinacao_valida(i, possivel_combinacao2) == 1)){
    return 1; //novos grupos obtidos
} else
if(((teste_combinacao_valida(k, possivel_combinacao) == 1 ) && (teste_combinacao_valida(i, possivel_combinacao2) == 0))   ||   ((teste_combinacao_valida(k, possivel_combinacao) == 0 ) && (teste_combinacao_valida(i, possivel_combinacao2) == 1))){
    return 3; //novo grupo e nova sequência obtidos
} else
{
//se não é uma combinação válida, destroca as peças
    strcpy(tmp, peca_a_trocar->peca);
    strcpy(peca_a_trocar->peca, tmp_p2->peca);
    strcpy(tmp_p2->peca, tmp);

return 2;
}
}

int joga_uma_na_mesa(int tam_combinacoes[], int pos_num_combinacoes, struct s_peca *peca_a_manipular, struct s_peca *peca_a_trocar, int num_a_trocar, struct s_peca *mesa, struct s_peca *peca_deslocada, struct s_peca *mao, int *soma_points, struct s_peca **tmp_p2, char tmp[4], int *quantia_mesa){
int soma_tam;
int i;
int j;
int k;
int soma_pontos;
int teste_combinacao;
int quantidade_mesa;
struct s_peca *tmp_p;
struct s_peca *possivel_combinacao[13];
struct s_peca *tmp_pp2;
//char tmp2[4];


soma_tam = 0;
i = 0;
quantidade_mesa = *quantia_mesa;
while(1){
    soma_tam  = soma_tam + tam_combinacoes[i];
    if(soma_tam > num_a_trocar){
        break;
    }
    i++;

}

k = i;

//muda a peça
strcpy(tmp, peca_a_trocar->peca);
strcpy(peca_a_trocar->peca, peca_a_manipular->peca);

//NOVA DEFINIÇÃO DA PEÇA A TROCAR
tmp_pp2 = peca_a_trocar;
tmp_p = mesa;
if(num_a_trocar == 0){
            peca_a_trocar= mesa;
            k = 0;
} else{
for(j = 0; j < soma_tam - tam_combinacoes[k]; j++){
            tmp_p = tmp_p->anterior;
}
            peca_a_trocar = tmp_p;
}



//cria um vetor para testar se a nova combinação é válida
for(i = 0;i < tam_combinacoes[k]; i++){
    tmp_p = peca_a_trocar;
    if(i == 0){
        possivel_combinacao[i] = peca_a_trocar;
    } else{ for(j = 0;j < i; j ++){
    tmp_p = tmp_p->anterior;
    if(tmp_p == NULL){
        break;
    }
    }
    if(tmp_p == NULL){
        i++;
        break;
    }
        possivel_combinacao[i] = tmp_p;

    }    //i é a quantia de peças da combinação possível
}

teste_combinacao = teste_combinacao_valida(i, possivel_combinacao);
if(teste_combinacao == 1 || teste_combinacao == 0){
//arrumando a mesa

soma_pontos = *soma_points;
//acrescentando ao soma_points
if(soma_pontos < 30){
soma_pontos = soma_pontos + conversao(peca_a_manipular->peca[0]);
*soma_points = soma_pontos;

}


//arrumando a mão
tmp_p = mao;

while(tmp_p->anterior != peca_a_manipular){
    tmp_p = tmp_p->anterior;
}

tmp_p->anterior = tmp_p->anterior->anterior;
free(peca_a_manipular);



printf("Peca colocada na mesa!\n");

tmp_p2[0] = tmp_pp2;
quantidade_mesa++;
*quantia_mesa = quantidade_mesa;
return 1;
} else{
//destrocando as peças
strcpy(tmp_pp2->peca ,tmp);

printf("Combinacoes validas nao foram formadas! Acao sem efeito!\n");
return 0;
}
}

