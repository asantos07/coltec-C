#include <stdio.h>
#include <stdlib.h>
//#include "pilha.h"
//#include "listas.h"

typedef struct testes
{
    int* carta;
    int n;
    int cartas;
    int players;
} teste;

typedef struct lista_de_testes
{
    teste data;
    struct lista_de_testes* prev;
} lista_testes;

typedef struct pilha_testes
{
    lista_testes* top;
} p_testes;

typedef struct lst_jogador
{
    int endscore;
    int id;
    struct lst_jogador* prox;
} jogador;

typedef struct lst_carta
{
    int val;
    struct lst_carta* prev;
} carta;

typedef struct p_monte_jogador
{
    carta* top;
} monte_jog;

void push(p_testes* pile, teste v)/// INSERE MAIS UM CASO DE TESTE A SER EXECUTADO
{
    lista_testes* novo= (lista_testes*) malloc(sizeof(lista_testes));
    novo->prev=pile->top;
    novo->data=v;
    pile->top=novo;
}

void push_carta(monte_jog* pile, int val)///INSERE MAIS UMA CARTA NO TOPO DA PILHA
{
    carta* novo= (carta*) malloc(sizeof(carta));
    novo->val=val;
    novo->prev=pile->top;
    pile->top=novo;
}

teste insere_teste(teste caso, FILE* entrada) ///LÊ O CASO DE TESTE POR INTEIRO E SETA AS VARIÁVEIS
{
    printf("\n Lendo o caso de teste #%d", caso.n);
    int cont, carta_num;
    caso.carta=(int*) malloc(sizeof(int)*caso.cartas);
    for(cont=caso.cartas-1; cont>=0; cont--)
    {
        fscanf(entrada, "%d", &carta_num);
        caso.carta[cont]=carta_num;
        printf("\n Carta #%d ---> %d",cont, caso.carta[cont]);
    }
    return caso;
}

jogador* lst_insere(jogador *l, int i)  ///INSERE UM JOGADOR NA LISTA DE JOGADORES
{
    jogador* item= malloc(sizeof(jogador));
    item->prox= l;
    item->id= i;
    return item;
}

jogador* playsetter(int num)  ///CRIA A LISTA CIRCULAR DE JOGADORES
{
    printf("\n Criando a lista circular de jogadores...");
    int i;
    jogador* player_lst= (jogador*) malloc(sizeof(jogador));
    player_lst->id=num;
    jogador* last=player_lst;
    for(i=num-1; i>0; i--)
    {
        player_lst=lst_insere(player_lst, i);
    }
    last->prox=player_lst;
    return player_lst;
}

monte_jog* def_compra(int* carta_i, int cartas) 	///CRIA A PILHA DE CARTAS
{
    int i;
    monte_jog* pile=(monte_jog*) malloc(sizeof(monte_jog));
    pile->top=NULL;
    for(i=0; i<cartas; i++)
    {
        int value=carta_i[i];
        push_carta(pile, value);
    }
    return pile;
}

void pop_transfer(monte_jog* source, monte_jog* dest)
{
    int val=source->top->val;
    carta* swap=source->top;
    source->top=swap->prev;
    free(swap);
    swap=dest->top;
    dest->top=(monte_jog*) malloc(sizeof(monte_jog));
    dest->top->prev=swap;
    dest->top->val=val;
}
void pl_compare(monte_jog* pl_jog[], jogador* player)
{
    monte_jog* atual=&pl_jog[player->id-1];
    jogador* swap;
    for(swap=player->prox; swap!=player; swap=swap->prox)
    {
        monte_jog* comp=&pl_jog[swap->id-1];
        if(comp->top->val==atual->top->val)
        {
            while(comp->top!=NULL)
            {
                pop_transfer(comp, atual);
            }
            return;
        }
    }
    carta* lixo=atual->top;
    atual->top=lixo->prev;
    free(lixo);
}

void player_move(jogador* player, monte_jog* pl_compra, monte_jog* pl_jog[]) ///FAZ CADA JOGADA INDIVUAL
{
    monte_jog* atual=&pl_jog[player->id-1];
    if(atual->top==NULL)
    {
        pop_transfer(pl_compra, atual);
        pop_transfer(pl_compra, atual);
        pop_transfer(pl_compra, atual);
        pop_transfer(pl_compra, atual);
    }
    else if(atual->top->val==pl_compra->top->val)
        pop_transfer(pl_compra, atual);
    else pl_compare(pl_jog, player);
}

void podio(jogador* player, monte_jog* pl_jog, FILE* output, p_testes* pile) ///CALCULA OS RANKINGS E IMPRIME PARA O .TXT
{
    int result=0, i=0, j=0;
    while(player->id!=1)
        player=player->prox;
    jogador* swap=player->prox;
    do{
        swap=swap->prox;
        monte_jog* score=&pl_jog[swap->id-1];
        while(score->top!=NULL)
        {
            result++;
            carta* lixo=score->top;
            score->top=lixo->prev;
            free(lixo);
        }
        swap->endscore=result;
        printf("\n Jogador #%d : %d pontos", swap->id, swap->endscore);
        if (result>j)
            j=result;
        result=0;
    }while(swap!=player->prox);
    printf("\n Top da rodada: %d", j);
    fprintf(output, "CASO %d\n", pile->top->data.n);
    while(player->id!=1)
        player=player->prox;
    swap=player->prox;
    do{
        swap=swap->prox;
        if(swap->endscore==j)
            fprintf(output, "%d ", swap->id);
    }while(swap!=player->prox);
    fprintf(output, "\n");
}

void game(FILE* output, monte_jog* compra, monte_jog* pl_jog, jogador* jogadores, p_testes* pile)  ///FAZ OS CÁLCULOS DO JOGO EM SI E DETERMINA O VENCEDOR
{
    jogador* i=jogadores;

    while(compra->top!= NULL)
    {
        player_move(i, compra, pl_jog);
        i=i->prox;
    }
    podio(jogadores, pl_jog, output, pile);
}

FILE* executor(p_testes* pile) ///EXECUTA AS TAREFAS FINAIS E OS CASOS DE TESTE SEQUENCIALMENTE
{
    jogador* lst_jog;
    monte_jog* pl_jog;
    monte_jog* pl_compra;
    monte_jog* swap;
    FILE* saida;
    saida=fopen("saida.txt", "w");

    while(pile->top!=NULL)
    {
        printf("\n TESTE\n");
        lst_jog=playsetter(pile->top->data.players);
        pl_compra=def_compra(pile->top->data.carta, pile->top->data.cartas);
        pl_jog=(monte_jog*) malloc(sizeof(monte_jog)*pile->top->data.players);
        game(saida, pl_compra, pl_jog, lst_jog, pile);
        swap=pile->top;
        pile->top=pile->top->prev;
        free(swap);
    }
}

int main()
{
    printf("Regras adaptadas de -https://pt.wikipedia.org/wiki/Rouba-monte- e o que consegui me lembrar da prova ao chegar em casa");
    FILE* testes;
    int count=0;
    testes=fopen("entrada.txt", "r");
    ftell(testes);
    teste atual;

    p_testes* pile= (p_testes*) malloc(sizeof(p_testes));
    pile->top= NULL;

    while(1)
    {
        count++;
        fscanf(testes, "%i %i", &atual.cartas, &atual.players);
        if(atual.cartas==0 && atual.players==0)
        {
            printf("\n Arquivo terminado, saindo do modo de leitura.");
            break;
        }
        if(atual.cartas<atual.players || atual.players<2 || atual.players>20 || atual.cartas>10000 || atual.cartas<2){
            printf("Erro de sintaxe, abortando");
            exit(-1);
        }
        atual.n=count;
        atual=insere_teste(atual, testes);
        push(pile, atual);
    }
    executor(pile);
    return 0;
}
