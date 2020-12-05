#ifndef TADHUFFMAN_H_INCLUDED
#define TADHUFFMAN_H_INCLUDED

struct Tree
{
    char info;
    int qtd;
    struct Tree *dir, *esq;
};

struct tpLista
{
    char info, codigo[30];
    int qtd;
    struct tpLista *prox;
};
typedef struct tpLista Lista;

Lista *criaListaNo(char info, int qtd)
{
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    nova->info = info;
    nova->qtd = qtd;
    nova->prox = NULL;
    strcpy(nova->codigo, "");
    return nova;
}

Tree *criaNo(char info, int qtd)
{
    Tree *novo = (Tree*)malloc(sizeof(Tree));
    novo->info = info;
    novo->qtd = qtd;
    novo->dir = novo->esq = NULL;
    return novo;
}

Lista* buscaListaNo(Lista *l, char info)
{
    while(l->prox != NULL && l->info != info)
        l = l->prox;
    return l;
}

void contaLetras(Lista **l, char str[])
{
    int i = 0;
    Lista *posi = NULL;
    for(i = 0; i < strlen(str); i++)
    {
        if((*l) != NULL)
        {
            posi = buscaListaNo( (*l), str[i]);
            if(posi->info == str[i])
                posi->qtd++;
            else
            {
                if(str[i] != '\n')
                    posi->prox = criaListaNo(str[i], 1);
                else
                    posi->prox = criaListaNo(185, 1);
            }
        }
        else
        {
            if(str[i] != '\n')
                (*l) = criaListaNo(str[i], 1);
            else
                (*l) = criaListaNo(185, 1);
        }

    }
}

int contaNosLista(Lista *l)
{
    int qtd = 0;
    while(l != NULL)
    {
        qtd++;
        l = l->prox;
    }
    return qtd;
}

void geraVetor(Tree *vet[], Lista *l)
{
    int i = 0;
    while(l != NULL)
    {
        vet[i++] = criaNo(l->info, l->qtd);
        l = l->prox;
    }
}

void ordenaVet(Tree *vet[], int tl)
{
    int i = 0, j = 0;
    Tree *posiI, *posiJ;
    for(i = 0; i < tl-1; i++)
    {
        for(j = i + 1; j < tl; j++)
        {
            posiI = vet[i];
            posiJ = vet[j];
            if(posiI->qtd < posiJ->qtd)
            {
                vet[i] = posiJ;
                vet[j] = posiI;
            }
        }
    }
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

    if(x->info == NULL)
        printnode('#', b);
    else
        printnode(x->info, b);

    show(x->esq, b+1);
}

void exibe(Tree *raiz)
{
    if(raiz != NULL)
        show(raiz, 1); //exibeTree(raiz, 1, 30, 8, 2);
}

void geraArvore(Tree **raiz, Tree *vet[], int tl)
{
    Tree *nova, *ultima, *penultima;
    int qtdU, qtdP;

    if(tl > 1)
    {
        while(tl > 1)
        {
            ultima = vet[tl];
            penultima = vet[tl-1];
            qtdU = ultima->qtd;
            qtdP = penultima->qtd;
            // MANDANDO NULL NO CRIA NÓ
            nova = criaNo(NULL, qtdU+qtdP);

            if(qtdU > qtdP)
            {
                nova->dir = ultima;
                nova->esq = penultima;
            }
            else
            {
                nova->dir = penultima;
                nova->esq = ultima;
            }

            vet[tl] = NULL;

            vet[tl-1] = nova;
            nova = NULL;

            if(tl > 1)
                ordenaVet(vet, tl);
            tl--;
        }
        ordenaVet(vet, tl);

        ultima = vet[tl];
        penultima = vet[tl-1];
        qtdU = ultima->qtd;  qtdP = penultima->qtd;
        // MANDANDO NULL NO CRIA NÓ
        nova = criaNo(NULL, qtdU+qtdP);
        nova->dir = penultima;
        nova->esq =ultima ;
        *raiz = nova;
    }
    else
    {
        ultima = vet[tl];
        penultima = vet[tl-1];
        qtdU = ultima->qtd;  qtdP = penultima->qtd;
        nova = criaNo(NULL, qtdU+qtdP);
        if(qtdU > qtdP)
        {
            nova->dir = ultima;
            nova->esq = penultima;
        }
        else
        {
            nova->dir = penultima;
            nova->esq = ultima;
        }
        *raiz = nova;
    }
}

void geraCodigo(Tree *raiz, char info, char str[], int tl, char *achou)
{
    if(raiz != NULL)
    {
        if(raiz->info == info)
        {
            *achou = 1;
            str[tl] = '\0';
        }
        else
        {
            str[tl] = '0';
            geraCodigo(raiz->esq, info, str, tl+1, &(*achou));
            if(!(*achou))
            {
                str[tl] = '1';
                geraCodigo(raiz->dir, info, str, tl+1, &(*achou));
            }
        }
    }
}

void geraTabela(Tree *raiz, Lista **l)
{
    Lista *aux = *l;
    char str[30], achou;
    while(aux != NULL)
    {
        achou = 0;
        str[0] = '\0';
        geraCodigo(raiz, aux->info, str, 0, &achou);
        strcpy(aux->codigo, str);
        aux = aux->prox;
    }
}


void montaResultado(Lista *l, char strInfo[], char strResultado[])
{
    int i;
    Lista *aux = NULL;
    for(i = 0; i < strlen(strInfo); i++)
    {
        aux = buscaListaNo(l, strInfo[i]);
        strcat(strResultado, aux->codigo);
    }
}

void insere(Tree **raiz, char str[], Lista **l)
{
    Tree *ultima, *nova;
    int qtdU;

    contaLetras(&(*l), str);

    int tl = contaNosLista(*l);

    Tree *vet[tl];
    geraVetor(vet, *l);

    ordenaVet(vet, tl);
    if(tl > 1)
        geraArvore(&(*raiz), vet, tl-1);
    else
    {
        ultima = vet[tl-1];
        qtdU = ultima->qtd;
        nova = criaNo(NULL, qtdU);
        *raiz = nova;
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




void killLista(Lista **l)
{
    Lista *aux = *l;
    while(*l != NULL)
    {
        *l = (*l)->prox;
        free(aux);
        aux = *l;
    }
}

#endif // TADHUFFMAN_H_INCLUDED
