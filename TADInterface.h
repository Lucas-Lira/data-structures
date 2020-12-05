#ifndef TADINTERFACE_H_INCLUDED
#define TADINTERFACE_H_INCLUDED
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>

//--- conio -------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y)
{
  COORD c ;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textattr(int _attr)
{ SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _attr); }

void textbackground(int _color)
{
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0x0F) | (_color<<4));
}

void textcolor(int _color) {
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0xF0) | _color);
}

int wherex()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.X + 1;
}

int wherey()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.Y + 1;
}

void clrscr(void)
{
  COORD coord = { 0, 0 };
  DWORD dwWritten, dwSize;
  HANDLE hScreen=GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO Info;

  if(GetConsoleScreenBufferInfo(hScreen, &Info))
  {
      dwSize = Info.dwSize.X * Info.dwSize.Y;
      FillConsoleOutputCharacter (hScreen, ' ', dwSize, coord, &dwWritten);
      FillConsoleOutputAttribute (hScreen, Info.wAttributes, dwSize, coord, &dwWritten);
      gotoxy (1, 1);
  }
}
//-----------------------------------------------------------------------------------------------------------------------------

void exibe_pos(Tree *raiz, int x, int y, int dist, int variante_dist)
{
    int posX;
    if(raiz != NULL)
    {
        gotoxy(x, y); printf("%d", raiz->caracter);

        posX= x-dist+variante_dist;
        if(posX > x)
           variante_dist= 8;
        exibe_pos(raiz->esq, x-dist+variante_dist, y+3, dist-2, variante_dist+6);

        posX= x+dist-variante_dist;
        if(posX < x)
            variante_dist= 8;
        exibe_pos(raiz->dir, x+dist-variante_dist, y+3, dist-2, variante_dist+6);
    }
}

void exibe(Tree *raiz)
{
    if(!raiz != NULL)
        exibe_pos(raiz, 120, 1, 20, 2);
}