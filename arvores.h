#ifndef ARVORES_H
#define ARVORES_H

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

//Funções para manipulação da árvore
No* criar_no(int valor);
int altura(No* no);
int max(int a, int b);
No* rotacao_direita(No* y);
No* rotacao_esquerda(No* x);
int balanceamento(No* no);
No* inserir_binaria(No* raiz, int valor);
No* remover_binaria(No* raiz, int valor);
No* inserir_avl(No* raiz, int valor);
No* remover_avl(No* raiz, int valor);
double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // ARVORES_H