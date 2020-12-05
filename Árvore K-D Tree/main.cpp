#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include"tadInterface.h"
#include"tad_Kd_Tree.h"

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
    char op, resp;
    int elem, x, y, raio;
    Lista *no = NULL;
    Tree *raiz = NULL;
    do
    {
        op = menu();
        system("cls");
        switch(op)
        {
            case 'A':
                do
                {
                    printf("Elemento: ");
                    scanf("%c",&elem);
                    printf("Cordenada X: ");
                    scanf("%d",&x);
                    printf("Codernada Y: ");
                    scanf("%d", &y);
                    insere(&raiz, elem, x, y);
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
                    printf("Cordenada X: ");
                    scanf("%d",&x);
                    printf("Cordenada Y: ");
                    scanf("%d",&y);
                    printf("Raio: ");
                    scanf("%d",&raio);

                    if(raio > 0)
                        busca(raiz, &no, (x-raio), (x+raio), (y-raio), (y+raio));
                    else
                        printf("Parametro [ Raio ] invalido!");

                    if(no != NULL)
                    {
                        exibeLista(no);
                    }
                    else
                        printf("Nao foram encontrados elementos nesta area!\n\n");

                    killLista(&no);




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
