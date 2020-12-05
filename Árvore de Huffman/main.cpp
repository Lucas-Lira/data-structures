#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include"tadInterface.h"
#include"tadHuffman.h"

int main()
{
    Tree *raiz = NULL;
    Lista *l = NULL;
    char strResultado[70];
    char frase[40];
    printf("Digite uma palavra: ");
    fflush(stdin);
    gets(frase);

    insere(&raiz, frase, &l);

    geraTabela(raiz, &l);
    strResultado[0] = '\0';
    montaResultado(l, frase, strResultado);

    printf("RESULTADO: %s\n", strResultado);
    exibe(raiz);
    printf("\n\n");

    killLista(&l);
    killTree(&raiz);
}
