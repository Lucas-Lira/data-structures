#ifndef TAD_KD_TREE_H_INCLUDED
#define TAD_KD_TREE_H_INCLUDED
#define X 0
#define Y 1

struct Tree
{
    int x, y;
    char id, disc;
    struct Tree *esq, *dir;
};

struct Lista
{
    struct Tree *no;
    struct Lista *prox;
};

Tree *criaNo(char info, int x, int y)
{
    Tree *novo = (Tree*)malloc(sizeof(Tree));
    novo->id = info;
    novo->x = x;
    novo->y = y;
    novo->disc = X;
    novo->esq = novo->dir = NULL;
    return novo;
}


void printnode(char c, int b, int x, int y)
{
    int i;
    for (i = 0; i < b; i++) printf("                ");
    printf("%c(%d, %d)\n", c, x, y);
}


void printnode(char c, int b)
{
    int i;
    for (i = 0; i < b; i++) printf("                ");
    printf("%c\n", c);
}

void show(Tree *x, int b)
{
    if (x == NULL)
    {
        printnode('*', b);
        return;
    }

    show(x->dir, b+1);

    if(x->id == NULL)
        printnode('#', b);
    else
        printnode(x->id, b, x->x, x->y);

    show(x->esq, b+1);
}

void exibe(Tree *raiz)
{
    if(raiz != NULL)
        show(raiz, 1); //exibeTree(raiz, 1, 30, 8, 2);
}




void insere(Tree **raiz, char info, int x, int y)
{
    Tree *nova = criaNo(info, x, y);
    if(*raiz == NULL)
        *raiz = nova;
    else
    {
        Tree *aux, *ant;
        aux = *raiz;
        ant = *raiz;

        while(aux != NULL)
        {
            ant = aux;
            if(aux->disc == X)
            {
                if(x > aux->x)
                    aux = aux->dir;
                else
                    aux = aux->esq;
            }
            else
            {
                if(y > aux->y)
                    aux = aux->dir;
                else
                    aux = aux->esq;
            }
        }

        if(ant->disc == X)
        {
            nova->disc = Y;
            if(x > ant->x)
                ant->dir = nova;
            else
                ant->esq = nova;
        }
        else
        {
            if(y > ant->y)
                ant->dir = nova;
            else
                ant->esq = nova;
        }
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


void exibeLista(Lista *l)
{
    Lista *aux = l;
    while(aux != NULL)
    {
        printf("%c(%d, %d)\n", aux->no->id, aux->no->x, aux->no->y);
        aux = aux->prox;
    }
    printf("\n");
}



void killLista(Lista **l)
{
    Lista *aux = *l;
    while(aux != NULL)
    {
        *l = aux->prox;
        free(aux);
        aux = *l;
    }
}

void push(Lista **l, Tree *info)
{
    Lista *nova = (Lista*)malloc(sizeof(Tree));
    nova->prox = *l;
    nova->no = info;
    *l = nova;
}

void busca(Tree *raiz, Lista **no, int xi, int xf, int yi, int yf)
{
    if(raiz != NULL)
    {
        if((raiz->x >= xi && raiz->x <= xf) && (raiz->y >= yi && raiz->y <= yf))
            push(&(*no), raiz);
        busca(raiz->esq, &(*no), xi, xf, yi, yf);
        busca(raiz->dir, &(*no), xi, xf, yi, yf);
    }
}
#endif // TAD_KD_TREE_H_INCLUDED
