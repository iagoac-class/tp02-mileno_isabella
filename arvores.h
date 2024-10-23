#ifndef ARVORES_H
#define ARVORES_H

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    int altura; //campo altura apenas para arvore AVL
} No;

//Funções para manipulação da árvore
No* criar_no(int valor); //Funcao que aloca um no na memoria
int altura(No* no); //funcao que calcula a altura do no
int max(int a, int b); //funcao que retorna o maior entre 2 numeros
No* rotacao_direita(No* y); //funcao que faz rotacao para direita
No* rotacao_esquerda(No* x); //funcao que faz rotacao para esquerda
int balanceamento(No* no); //funcao que obtem o fator de balanceamento de um no
No* inserir_binaria(No* raiz, int valor); //funcao para inserir na arvore binaria
No* remover_binaria(No* raiz, int valor); //funcao para remover na arvore binaria
No* inserir_avl(No* raiz, int valor); //funcao para inserir na arvore AVL
No* remover_avl(No* raiz, int valor); //funcao para remover na arvore AVL
double arvore_binaria(int instancia_num); //funcao que roda as insercoes e remocoes na arvore binaria
double arvore_balanceada(int instancia_num); //funcao que roda as incercoes e remocoes na arvore AVL

#endif // ARVORES_H