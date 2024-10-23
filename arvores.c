#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"  // Incluindo o arquivo de cabeçalho

//Funcao que recebe um int e aloca um nó na memoria e retorna o endereço desse nó
No* criar_no(int valor) {
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->valor = valor;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    novo_no->altura = 1;  // Altura inicial para AVL
    return novo_no;
}

//Funcao que calcula a altura de um nó(para AVL)
int altura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

//Funcao que encontra um maior entre 2 numeros
int max(int a, int b) {
    return (a > b) ? a : b;
}

//Funcao que realiza rotacao para direita (AVL)
No* rotacao_direita(No* y) {
    No* x = y->esquerda; //no auxiliar
    No* T2 = x->direita; //no auxiliar
    x->direita = y; //realiza a rotacao
    y->esquerda = T2; //realiza a rotacao
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1; //atualiza altura
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1; //atualiza altura
    return x;
}

//Funcao que realiza rotacao para esquerda (AVL)
No* rotacao_esquerda(No* x) {
    No* y = x->direita; //no auxiliar
    No* T2 = y->esquerda; //no auxiliar
    y->esquerda = x; //realiza a rotacao
    x->direita = T2; //realiza a rotacao
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1; //atualiza altura
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1; //atualiza altura
    return y;
}

//Funcao responsavel calcular o fato de balanceamento da arvore (altura max da esquerda - altura max da direita)
int balanceamento(No* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

//Funcao para insercao na arvore binaria
No* inserir_binaria(No* raiz, int valor) {
    if (raiz == NULL) //se a raiz for nula encontramos o lugar para inserir o novo no
        return criar_no(valor); //alocamos o no com a funcao de criar no e inserimos ele na arvore

    if (valor < raiz->valor)
        raiz->esquerda = inserir_binaria(raiz->esquerda, valor); //se o valor for menor que a raiz andamos para esquerda da arvore
    else if (valor > raiz->valor)
        raiz->direita = inserir_binaria(raiz->direita, valor); //se o valor for maior que a raiz andamos para direita da arvore

    return raiz; //se o valor ja existe na arvore nao acontece nada
}

//Funcao para remocao na arvore binaria
No* remover_binaria(No* raiz, int valor) {
    if (raiz == NULL) //nao encontramos o no a ser removido
        return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover_binaria(raiz->esquerda, valor); //se o no for menor que a raiz andamos para esquerda
    else if (valor > raiz->valor)
        raiz->direita = remover_binaria(raiz->direita, valor); //se o no for maior que a raiz andamos para direita
    else {//encontramos o no a remover
        if (raiz->esquerda == NULL) { //o no nao tem filho a esquerda
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }
        if (raiz->direita == NULL) { //o no nao tem filho a direita
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        //Se houver dois filhos, encontra o menor da sub-arvore a direita
        No* temp = raiz->direita;
        while (temp && temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        raiz->valor = temp->valor; //Substitui o valor do no a ser removido pelo valor do no minimo encontrado
        raiz->direita = remover_binaria(raiz->direita, temp->valor);  //Remove o no minimo na subarvore direita
    }
    return raiz;
}

//Insercao na arvore AVL
No* inserir_avl(No* raiz, int valor) {
    if (raiz == NULL) //se a raiz for nula encontramos o lugar para inserir o no
        return criar_no(valor); //cria o no apontamos para ele

    if (valor < raiz->valor)
        raiz->esquerda = inserir_avl(raiz->esquerda, valor); //se o novo no for menor que a raiz andamos para esquerda
    else if (valor > raiz->valor)
        raiz->direita = inserir_avl(raiz->direita, valor); //se o novo no for maior que a raiz andamos para direita

    //Atualiza a altura do nó atual
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    //Balanceia o nó atual
    int balanco = balanceamento(raiz);

    //Caso necessario realiza uma rotacao para direita, esquerda ou dupla para um dos lados
    //rotacao a direita
    if (balanco > 1 && valor < raiz->esquerda->valor)
        return rotacao_direita(raiz);
    //rotacao a esquerda
    if (balanco < -1 && valor > raiz->direita->valor)
        return rotacao_esquerda(raiz);
    //rotacao dupla a esquerda
    if (balanco > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
    //rotacao dupla a direita
    if (balanco < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }
    //retorna a raiz
    return raiz;
}

//Funcao para remover um no da arvore AVL
No* remover_avl(No* raiz, int valor) {
    if (raiz == NULL) // se a raiz for nula nao encontramos o valor para remover
        return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover_avl(raiz->esquerda, valor); //se a raiz for maior que o no a ser removido andamos para esquerda
    else if (valor > raiz->valor)
        raiz->direita = remover_avl(raiz->direita, valor); //se a raiz for menor que o no a ser removido andamos para direita
    else {//encontramos o valor a ser removido
        if (raiz->esquerda == NULL) {//nao tem filho a esquerda
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }
        if (raiz->direita == NULL) { //nao tem filho a direita
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        //Se houver dois filhos, encontra o menor da sub-arvore a direita
        No* temp = raiz->direita;
        while (temp && temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        raiz->valor = temp->valor; // Substitui o valor do no a ser removido pelo valor do no minimo encontrado.
        raiz->direita = remover_avl(raiz->direita, temp->valor); //Remove o no mínimo na sub-arvore direita.
    }

    //Atualiza a altura do nó atual
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    // Balanceia o nó atual
    int balanco = balanceamento(raiz);

    //Caso necessario realiza uma rotacao para direita, esquerda ou dupla para um dos lados
    //rotacao a direita
    if (balanco > 1 && balanceamento(raiz->esquerda) >= 0)
        return rotacao_direita(raiz);
    //rotacao a esquerda
    if (balanco < -1 && balanceamento(raiz->direita) <= 0)
        return rotacao_esquerda(raiz);
    //rotacao dupla a esquerda
    if (balanco > 1 && balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
    //rotacao dupla a direita
    if (balanco < -1 && balanceamento(raiz->direita) > 0) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

//Funcao que faz as insercoes e remocoes na arvore binaria
double arvore_binaria(int instancia_num) {
    char caminho[50]; //o vetor poderia ser de tamanho 14 considerando que existiram apenas 3 arquivos para foi definido 50 para evitar erro e possibilitar teste em mais arquivos se necessario
    sprintf(caminho, "instancias/%d", instancia_num); //Le o arquivo escolhido
    FILE* arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %d\n", instancia_num); //caso tenha erro ao abrir o arquivo ele avisa
        return -1;
    }

    No* raiz = NULL; //Cria o ponteiro para raiz da nossa arvore binaria
    char operacao;
    int valor;

    clock_t begin = clock(); //inicia o contador
    //Loop que le todas as linhas e colunas do arquivo para realizar as operacoes
    while (fscanf(arquivo, " %c %d", &operacao, &valor) != EOF) {
        if (operacao == 'I') {
            raiz = inserir_binaria(raiz, valor); //se encontrar I realiza insercao do valor na proxima coluna preenchida (binaria)
        } else if (operacao == 'R') {
            raiz = remover_binaria(raiz, valor); //se encontrar R realiza remocao do valor na proxima coluna preenchida (binaria)
        }
    }

    clock_t end = clock(); //finaliza o contador
    fclose(arquivo); //fecha o arquivo
    return (double)(end - begin) / CLOCKS_PER_SEC; //retorna o tempo de execucao em segundos
}

// Função para ler o arquivo e realizar inserções e remoções na árvore AVL
double arvore_balanceada(int instancia_num) {
    char caminho[50]; //o vetor poderia ser de tamanho 14 considerando que existiram apenas 3 arquivos para foi definido 50 para evitar erro e possibilitar teste em mais arquivos se necessario
    sprintf(caminho, "instancias/%d", instancia_num);
    FILE* arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %d\n", instancia_num);
        return -1;
    }

    No* raiz = NULL; //Cria o ponteiro para raiz da nossa arvore AVL
    char operacao;
    int valor;

    clock_t begin = clock(); //Inicia o contador
    //Loop que le todas as linhas e colunas do arquivo para realizar as operacoes
    while (fscanf(arquivo, " %c %d", &operacao, &valor) != EOF) {
        if (operacao == 'I') {
            raiz = inserir_avl(raiz, valor); //se encontrar I realiza insercao do valor na proxima coluna preenchida (AVL)
        } else if (operacao == 'R') {
            raiz = remover_avl(raiz, valor); //se encontrar R realiza remocao do valor na proxima coluna preenchida (AVL)
        }
    }

    clock_t end = clock(); //finaliza o contador
    fclose(arquivo); //fecha o arquivo
    return (double)(end - begin) / CLOCKS_PER_SEC; //retorna o tempo de execucao em segundos
}

int main() {
    int escolha;
    printf("Escolha um arquivo para processar:\n");
    printf("1 - 1\n");
    printf("2 - 2\n");
    printf("3 - 3\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > 3) {
        printf("Escolha invalida, selecione um número de 1 a 3.\n");
        return 1;
    }

    double tempo_binario = arvore_binaria(escolha);
    printf("Tempo de execucao da arvore binaria: %.2f segundos\n", tempo_binario);

    double tempo_avl = arvore_balanceada(escolha);
    printf("Tempo de execucao da arvore AVL: %.2f segundos\n", tempo_avl);

    return 0;
}