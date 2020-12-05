#ifndef TADARVORERUBRONEGRA_H_INCLUDED
#define TADARVORERUBRONEGRA_H_INCLUDED
#define BLACK 0
#define RED 1

struct Tree
{
    int info;
    char cor;
    struct Tree *esq, *dir, *pai;
};
typedef struct Tree Tree;

Tree *criaNo(int info)
{
    Tree *novo = (Tree*)malloc(sizeof(Tree));
    novo->cor = RED;
    novo->info = info;
    novo->dir = novo->esq = novo->pai = NULL;
    return novo;
}

void rotacao_Esquerda(Tree **raiz, Tree *x)
{
    Tree *y = x->dir;
    x->dir = y->esq;

    if(y->esq != NULL)
        y->esq->pai = x;

    y->pai = x->pai;
    // VERIFICA SE O PAI DE X É NULO (X == RAIZ)
    if(x->pai == NULL)
        *raiz = y;
    else
    {
        if(x == x->pai->esq)
            x->pai->esq = y;
        else
            x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}

void rotacao_Direita(Tree **raiz, Tree *y)
{
    Tree *x = y->esq;
    y->esq = x->dir;

    if(x->dir != NULL)
        x->dir->pai = y;

    x->pai = y->pai;

    if(y->pai == NULL)
        *raiz = x;
    else
    {
        if(y == y->pai->dir)
            y->pai->dir = x;
        else
            y->pai->esq = x;
    }
    x->dir = y;
    y->pai = x;
}

// FUNÇÕES DE EXIBIÇÃO
void printnode(int c, char cor, int b)
{
    int i;
    for (i = 0; i < b; i++) printf("                ");
    printf("%d->[%d]\n", c, cor);
}

void printnode2(char c, int b)
{
    int i;
    for (i = 0; i < b; i++) printf("                ");
    printf("%c\n", c);
}

void show(Tree *x, int b)
{
    if (x == NULL)
    {
        printnode2('*', b);
        return;
    }
    show(x->dir, b+1);
    if(x->info == NULL)
        printnode2('#', b);
    else
        printnode(x->info, x->cor, b);
    show(x->esq, b+1);
}

void exibe(Tree *raiz)
{
    if(raiz != NULL)
        show(raiz, 1);
}

void exibeTree(Tree *raiz)
{
    if(raiz != NULL)
    {
        printf("Info: %d -> Cor: %d\n", raiz->info, raiz->cor);
        exibeTree(raiz->esq);
        exibeTree(raiz->dir);
    }
}

void atualizaCor(Tree **raiz, Tree *novo)
{
    Tree *x = novo;
    Tree *y = NULL;

    while(novo->pai != NULL && novo->pai->cor == RED)
    {
        // PRIMEIRO LADO
        if(novo->pai == novo->pai->pai->esq)
        {
            y = novo->pai->pai->dir;
            // PRIMEIRO CASO
            if(y != NULL && y->cor == RED)
            {
                novo->pai->cor = BLACK;
                y->cor = BLACK;
                x->pai->pai->cor = RED;
                novo = novo->pai->pai;
            }
            else
            {
                if(novo == novo->pai->dir)
                {
                    novo = novo->pai;
                    rotacao_Esquerda(&(*raiz), novo);
                    novo->pai->cor = BLACK;
                }
                // VERIFICAR
                novo->pai->pai->cor = RED;
                rotacao_Direita(&(*raiz), novo->pai->pai);
                (*raiz)->cor = BLACK;
            }
        }
        else
        {
            y = novo->pai->pai->esq;
            if(y != NULL && y->cor == RED)
            {
                novo->pai->cor = BLACK;
                y->cor = BLACK;
                x->pai->pai->cor = RED;
                novo = novo->pai->pai;
            }
            else
            {
                if(novo == novo->pai->esq)
                {
                    novo = novo->pai;
                    rotacao_Direita(&(*raiz), novo);
                    novo->pai->cor = BLACK;
                }
                // VERIFICAR
                novo->pai->pai->cor = RED;
                rotacao_Esquerda(&(*raiz), novo->pai->pai);
                (*raiz)->cor = BLACK;
            }
        }
        x = novo;
    }
    (*raiz)->cor = BLACK;
}

void insere(Tree **raiz, int info)
{
    Tree *novo = criaNo(info);
    if(*raiz != NULL)
    {
        Tree *aux, *ant;
        aux = ant = *raiz;
        while(aux != NULL)
        {
            ant = aux;
            if(aux->info > info)
                aux = aux->esq;
            else
                aux = aux->dir;
        }
        if(ant->info > info)
            ant->esq = novo;
        else
            ant->dir = novo;
        novo->pai = ant;

        atualizaCor(&(*raiz), novo);
    }
    else
    {
        novo->cor = BLACK;
        *raiz = novo;
    }
}




void killTree(Tree **raiz)
{
    if(*raiz != NULL)
    {
        killTree(&(*raiz)->esq);
        killTree(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}





void buscaInfo(Tree *raiz, Tree **no, int info, char *achou)
{
    if(raiz != NULL)
    {
        if(raiz->info == info)
        {
            *no = raiz;
            *achou = 1;
        }
        else
        {
            buscaInfo(raiz->esq, &(*no), info, &(*achou));
            if(!achou)
                buscaInfo(raiz->dir, &(*no), info, &(*achou));
        }
    }
}

#endif // TADARVORERUBRONEGRA_H_INCLUDED
