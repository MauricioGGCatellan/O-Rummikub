#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions_and_struct_dec.h"

int main()
{
    struct s_peca *maos[5];
    struct s_peca *mesa;
    struct s_peca *tmp_p;
    struct s_peca *tmp_p_mesa;
    struct s_peca *tmp_tmp_p_mesa;
    struct s_peca **tmp_p2;
    struct s_peca *pecas_a_jogar[13];
    struct s_peca *peca_a_manipular;
    struct s_peca *peca_a_trocar;
    struct s_peca *peca_deslocada;
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
    int num_a_jogar_alone;
    int quantia_mesa;
    int num_a_manipular;
    int num_a_trocar;
    int teste_coloca_a_mesa;
    int teste_manipular_mesa;
    int teste_jogar_uma_na_mesa;
    int tam_sequencias[35];
    int pos_num_sequencias;
    char *deck[106];
    char resposta [3];
    char *a[5];
    char tmp[4];
    char tmp2[4];

peca_a_trocar = NULL;
peca_deslocada = NULL;
tmp_p2 = (struct s_peca **) malloc(sizeof(struct s_peca *));
tmp_p2[0] = (struct s_peca *) malloc(sizeof(struct s_peca));
for(i = 0;i < 13; i++){
    nums_a_jogar[i] = -20;
}


//MENU
while(resposta[0] != '3'){
        printf(">>>RUMMIKUB<<<\n");
        printf("1. Jogar - modo aleatorio\n");
        printf("2. Jogar - modo controlado\n");
        printf("3. Sair\n");
        scanf("%s", resposta);
        fflush(stdin);
        if(resposta[0] == '1' || resposta[0] == '2'){
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

        if(i != n_players && maos[i] == NULL){
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
        if(n_players == 1){
            pos_player = 0;
            first_player = 0;
        }
        //PRIMEIRAS JOGADAS


        soma_points = 0;
        bandeira = 1;
        pos_num_sequencias = 0;
        while(pos_player != first_player || bandeira == 1){
        soma_points = 0;
        printf("Vez do jogador %d\n", pos_player + 1);
        while(resposta[0] != '4' || soma_points < 30){

        //print de mão inclusa na função "prints_de_jogada"
        prints_de_jogada(resposta, maos[pos_player], quantia_mesa, mesa);

        if(resposta[0] == '1'){

        prints_resp_1(&k, nums_a_jogar, quantia_mao[pos_player], &num_a_jogar_alone, &num_a_trocar, resposta);

        //CASO DE JOGAR UMA COMBINAÇÃO NOVA NA MESA
        if(resposta[0] == '1'){
        //peças a jogar salvas em outro vetor
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

        j = teste_combinacao_valida(k-1, pecas_a_jogar);
        printf("Pecas escolhidas: \n");
        for(i = 0; i < k -1; i++){
            printf("%s ", pecas_a_jogar[i]->peca);
        }
        printf("\n");
        if(j == 2){
            printf("Combinacao invalida!\n");
            continue;
        } else if(j == 0 || j == 1){
            if(j == 0){
            printf("Sequencia posta na mesa!\n");
            } else{printf("Grupo posto na mesa!\n");}
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
           teste_coloca_a_mesa = coloca_a_mesa(mesa, pecas_a_jogar, k-1, maos[pos_player], &quantia_mao[pos_player], tam_sequencias, &pos_num_sequencias, &soma_points, 1);
           if(teste_coloca_a_mesa == 1){
            maos[pos_player] = maos[pos_player]->anterior;
           }
            }
        }
        }       //CASO DE JOGAR APENAS UMA PEÇA NA MESA
        else if(resposta[0] == '2'){
                //define a peça escolhida
                   tmp_p = maos[pos_player];
        if(num_a_jogar_alone == 0){
                peca_a_manipular = mesa;
        } else{
        for(j = 0; j < num_a_jogar_alone; j++){
                if(tmp_p == NULL){
                    break;
                }
            tmp_p = tmp_p->anterior;
        }
        if(tmp_p == NULL){
            printf("Numero invalido\n");
            continue;
        }
            peca_a_manipular = tmp_p;
        }

        //define a peça escolhida da mesa
        tmp_tmp_p_mesa = mesa;
        if(num_a_trocar == 0){
            peca_a_trocar= mesa;
        } else{
        for(j = 0; j < num_a_trocar; j++){
            tmp_tmp_p_mesa = tmp_tmp_p_mesa->anterior;
        }
            peca_a_trocar = tmp_tmp_p_mesa;
        }

       teste_jogar_uma_na_mesa =  joga_uma_na_mesa(tam_sequencias, pos_num_sequencias, peca_a_manipular, peca_a_trocar, num_a_trocar, mesa, peca_deslocada, maos[pos_player], &soma_points, tmp_p2, tmp, &quantia_mesa);
        if(teste_jogar_uma_na_mesa == 1){

                tmp_p = tmp_p2[0];
                i = 0;
            while(tmp_p->anterior!= NULL){
                tmp_p = tmp_p->anterior;
                i++;
            }                   //está na última peça (à direita)
            peca_deslocada = (struct s_peca *) malloc(sizeof(struct s_peca));
            if(peca_deslocada == NULL){
                printf("Falha na alocacao de memoria\n");
                continue;
            }
            strcpy(peca_deslocada->peca, tmp_p->peca);
            tmp_p->anterior = peca_deslocada;
            //strcpy(peca_deslocada->peca, tmp_p->peca);
            peca_deslocada->anterior = NULL;

for(j = 0; j < i; j++){
    if(j == 0){
            strcpy(tmp2, tmp_p2[0]->anterior->peca);
            strcpy(tmp_p2[0]->anterior->peca, tmp);
    }else{
            strcpy(tmp ,tmp_p2[0]->anterior->peca);
            strcpy(tmp_p2[0]->anterior->peca, tmp2);
            strcpy(tmp2, tmp);
    }                                                //a string da peça a trocar está em tmp (inicialmente)
            tmp_p2[0] = tmp_p2[0]->anterior;
if(tmp_p2[0]->anterior == NULL){
        break;
}
}

        }

        }
        }
        else if(resposta[0] == '2'){
        if(quantia_mesa == 0){
            printf("Nao ha pecas na mesa!\n");
            continue;
        }
        printf("Que peca deseja manipular? (as pecas estao, da esquerda para a direita, em ordem crescente, e a primeira peca e a 0)\n");
        scanf("%d", &num_a_manipular);
            tmp_tmp_p_mesa = mesa;
        if(num_a_manipular == 0){
            peca_a_manipular= mesa;
        } else{
        for(j = 0; j < num_a_manipular; j++){
            tmp_tmp_p_mesa = tmp_tmp_p_mesa->anterior;
        }
            peca_a_manipular = tmp_tmp_p_mesa;
        }

        printf("A que posicao da mesa deseja leva-la? (as pecas serao deslocadas para a direita)\n");
        scanf("%d", &num_a_trocar);
        if(num_a_trocar != num_a_manipular){
        teste_manipular_mesa = manipular_pecas_da_mesa(mesa, num_a_trocar, peca_a_manipular, peca_a_trocar, tam_sequencias, pos_num_sequencias, num_a_manipular);
        if(teste_manipular_mesa == 2){
            printf("Posicao invalida. Acao sem efeito\n");
        }
        } else{
            printf("Acao sem efeito!\n");
            }

        }

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
  bandeira = 0;
}

//AS JOGADAS RESTANTES!
while(1){
if(bandeira == 0){
printf("Vez do jogador %d\n", pos_player + 1);
bandeira = 1;
}
prints_de_jogada(resposta, maos[pos_player], quantia_mesa, mesa);

if(resposta[0] == '1'){
prints_resp_1(&k, nums_a_jogar, quantia_mao[pos_player], &num_a_jogar_alone, &num_a_trocar, resposta);
if(resposta[0] == '1'){
//peças a jogar salvas em outro vetor
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

j = teste_combinacao_valida(k-1, pecas_a_jogar);
printf("Pecas escolhidas: \n");
for(i = 0; i < k -1; i++){
            printf("%s ", pecas_a_jogar[i]->peca);
}
printf("\n");
if(j == 2){
        printf("Combinacao invalida!\n");
        continue;
} else if(j == 0 || j == 1){
            if(j == 0){
            printf("Sequencia posta na mesa!\n");
            } else{printf("Grupo posto na mesa!\n");}
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
           teste_coloca_a_mesa = coloca_a_mesa(mesa, pecas_a_jogar, k-1, maos[pos_player], &quantia_mao[pos_player], tam_sequencias, &pos_num_sequencias, &soma_points, 0);

            }
        }
}

else if(resposta[0] == '2'){
                //define a peça escolhida
                   tmp_p = maos[pos_player];
        if(num_a_jogar_alone == 0){
                peca_a_manipular = mesa;
        } else{
        for(j = 0; j < num_a_jogar_alone; j++){
                if(tmp_p == NULL){
                    break;
                }
            tmp_p = tmp_p->anterior;
        }
        if(tmp_p == NULL){
            printf("Numero invalido\n");
            continue;
        }
            peca_a_manipular = tmp_p;
        }

        //define a peça escolhida da mesa
        tmp_tmp_p_mesa = mesa;
        if(num_a_trocar == 0){
            peca_a_trocar= mesa;
        } else{
        for(j = 0; j < num_a_trocar; j++){
            tmp_tmp_p_mesa = tmp_tmp_p_mesa->anterior;
        }
            peca_a_trocar = tmp_tmp_p_mesa;
        }

           teste_jogar_uma_na_mesa =  joga_uma_na_mesa(tam_sequencias, pos_num_sequencias, peca_a_manipular, peca_a_trocar, num_a_trocar, mesa, peca_deslocada, maos[pos_player], &soma_points, tmp_p2, tmp, &quantia_mesa);
        if(teste_jogar_uma_na_mesa == 1){

                tmp_p = tmp_p2[0];
                i = 0;
            while(tmp_p->anterior!= NULL){
                tmp_p = tmp_p->anterior;
                i++;
            }                   //está na última peça (à direita)
            peca_deslocada = (struct s_peca *) malloc(sizeof(struct s_peca));
            tmp_p->anterior = peca_deslocada;
            peca_deslocada->anterior = NULL;

for(j = 0; j < i; j++){
    if(j == 0){
            strcpy(tmp2, tmp_p2[0]->anterior->peca);
            strcpy(tmp_p2[0]->anterior->peca, tmp);
    } else{
            strcpy(tmp ,tmp_p2[0]->anterior->peca);
            strcpy(tmp_p2[0]->anterior->peca, tmp2);
            strcpy(tmp2, tmp);
    }                                                //a string da peça a trocar está em tmp (inicialmente)
            tmp_p2[0] = tmp_p2[0]->anterior;
if(tmp_p2[0]->anterior == NULL){
        break;
}
}

        }
}
} else if(resposta[0] == '2'){
     printf("Que peca deseja manipular? (as pecas estao, da esquerda para a direita, em ordem crescente, e a primeira peca e a 0)\n");
        scanf("%d", &num_a_manipular);
            tmp_tmp_p_mesa = mesa;
        if(num_a_manipular == 0){
            peca_a_manipular= mesa;
        } else{
        for(j = 0; j < num_a_manipular; j++){
            tmp_tmp_p_mesa = tmp_tmp_p_mesa->anterior;
        }
            peca_a_manipular = tmp_tmp_p_mesa;
        }

        printf("A que posicao da mesa deseja leva-la? (as pecas serao deslocadas para a direita)\n");
        scanf("%d", &num_a_trocar);
        if(num_a_trocar != num_a_manipular){
        teste_manipular_mesa = manipular_pecas_da_mesa(mesa, num_a_trocar, peca_a_manipular, peca_a_trocar, tam_sequencias, pos_num_sequencias, num_a_manipular);
        if(teste_manipular_mesa == 2){
            printf("Posicao invalida. Acao sem efeito!\n");
        }
        } else{
            printf("Acao sem efeito!\n");
            }
} else if(resposta[0] == '3'){
        tmp_p =maos[pos_player];
        maos[pos_player] = (struct s_peca *) malloc(sizeof(struct s_peca));
        maos[pos_player]->anterior = tmp_p;
        draw(&quantia_mao[pos_player], maos[pos_player], &pos_deck, deck);
} else if(resposta[0] == '4'){
pos_player++;
if(pos_player == n_players){
    pos_player = 0;
}
bandeira = 0;
}
else{
printf("Opcao invalida!\n");
continue;
}
if(quantia_mao[pos_player] == 0){
    printf("O jogador %d venceu! Parabens!\n", pos_player + 1);

    //liberando a memória usada

for(i = 0; i < n_players; i++){
    free(maos[i]);
}

for(i = 0; i < 106; i++){
    free(deck[i]);
}

tmp_tmp_p_mesa = mesa;

while(mesa != NULL){
    tmp_tmp_p_mesa = mesa;
    mesa = mesa->anterior;
    free(tmp_tmp_p_mesa);

}

    break;
}

}


} else if(resposta[0] != '3'){
        printf("Opcao invalida!\n");
        continue;
        }





}
return 0;

}










