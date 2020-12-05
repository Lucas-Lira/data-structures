#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include "tadInterface.h"
#include "tadArvoreRubroNegra.h"

char menu()
{
    system("cls");
    printf("## ARVORE RUBRO-NEGRA ##\n\n");
    printf("[  A  ] - Insere Elemento\n");
    printf("[  B  ] - Busca Elemento\n");
    printf("[ ESC ] - Finalizar\n\n");
    printf("Digite a opcao desejada: ");
    return toupper(getche());
}

int main()
{
    char op, resp, achou;
    int num;
    Tree *raiz = NULL, *no = NULL;
    do
    {
        op = menu();
        system("cls");
        switch(op)
        {
            case 'A':
                do
                {
                    printf("Digite o numero que deseja inserir: ");
                    scanf("%d",&num);
                    insere(&raiz, num);
                    exibe(raiz);
                    printf("Deseja continuar [S/N]: ");
                    fflush(stdin);
                    resp = toupper(getche());
                    system("cls");
                }
                while(resp == 'S');
            break;

            case 'B':
                do
                {
                    printf("Digite o numero que deseja buscar: ");
                    scanf("%d",&num);
                    achou = 0;
                    no = NULL;
                    buscaInfo(raiz, &no, num, &achou);

                    if(no != NULL)
                        printf("\nO elemento [ %d ] foi encontrado!\n\n", num);
                    else
                        printf("\nO elemento [ %d ] nao foi encontrado!\n\n", num);

                    printf("Deseja continuar [S/N]: ");
                    fflush(stdin);
                    resp = toupper(getche());
                    system("cls");
                }
                while(resp == 'S');
            break;
        }
    }while(op != 27);
    killTree(&raiz);
}
