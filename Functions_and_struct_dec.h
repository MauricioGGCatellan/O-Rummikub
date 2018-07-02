#ifndef FUNCTIONS_AND_STRUCT_DEC_H_INCLUDED
#define FUNCTIONS_AND_STRUCT_DEC_H_INCLUDED

struct s_peca{
char peca[4];
struct s_peca *anterior;
struct s_peca *proximo;
};

void prints_de_jogada(char resp[], struct s_peca *maos, int quantia_mesa, struct s_peca *mesa);
void draw(int *quantia_mao, struct s_peca *mao, int *pos_deck, char *deck[]);
int teste_combinacao_valida(int k, struct s_peca *pecas_a_jogar[13]);
void prints_resp_1(int *k, int nums_a_jogar[], int quantia_mao, int *num_a_jogar, int *num_a_trocar, char resposta[3]);
int manipular_pecas_da_mesa(struct s_peca *mesa, int num_a_manipular, struct s_peca *peca_a_manipular, struct s_peca *peca_a_trocar, int tam_combinacoes[], int pos_num_combinacoes, int num_a_manipular2);
int joga_uma_na_mesa(int tam_combinacoes[], int pos_num_combinacoes, struct s_peca *peca_a_manipular, struct s_peca *peca_a_trocar, int num_a_trocar, struct s_peca *mesa, struct s_peca *peca_deslocada, struct s_peca *mao, int *soma_points, struct s_peca **tmp_p2, char tmp[4], int *quantia_mesa);
int coloca_a_mesa(struct s_peca *mesa, struct s_peca *pecas_a_jogar[], int k, struct s_peca *mao, int *quantia_mao, int tam_sequencias[], int *pos_num_sequencias, int *soma_points, int bandeira_first_play);

void inicializa_deck(char *deck[]);
void inicializa_deck_controlado(FILE *deck_controlado, char *deck[]);
void shuffle(char *deck[], int n);
int conversao(char a);
void bubble_sort(int a[], int n);
void inicializa_mao(struct s_peca *maos, char *deck[], int *pos);

#endif // FUNCTIONS_AND_STRUCT_DEC_H_INCLUDED
