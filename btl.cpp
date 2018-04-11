#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;


#define ConsoleWidth 80
#define ConsoleHeight 20

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
enum TrangThai {UP, DOWN, STAND};
struct ToaDo
{
    int x;
    int y;
};

struct HinhDang
{
    char a[3][3];
    char b[2][3];
    char c[1][2];
    char d;
};

struct Man
{
    ToaDo td;
    HinhDang hd;
    TrangThai tt;
    int diem = 0;
};

struct Fence
{
    ToaDo td;
    HinhDang hd;
};
 struct VatPham
 {
     ToaDo td;
     HinhDang hd;
 };
void KhoiTao(Man &man)
{
    man.td.x = 3;
    man.td.y = ConsoleHeight - 3;
    man.tt = STAND;
    man.hd.a[0][1] = '0';
    man.hd.a[0][0] = man.hd.a[0][2] = man.hd.a[2][1] = ' ';
    man.hd.a[1][0] = man.hd.a[2][0] = '/';
    man.hd.a[1][2] = man.hd.a[2][2] = '\\';
    man.hd.a[1][1] = '|';
}
void KhoiTaoFence(Fence &fence, Fence &fence1, Fence &fence2)
{

    fence.td.x = ConsoleWidth ;
    fence.td.y = ConsoleHeight - 3;
    fence.hd.b[0][0] = fence.hd.b[0][2] = fence.hd.b[1][1] = '|';
    fence.hd.b[1][0] = fence.hd.b[1][2] = ' ';
    fence.hd.b[0][1] = '_';

    fence1.td.x = ConsoleWidth ;
    fence1.td.y = ConsoleHeight - 3;
    fence1.hd.c[0][0] = 202 ;
    fence1.hd.c[1][0] = 182;

    fence2.td.x = ConsoleWidth ;
    fence2.td.y = ConsoleHeight - 3;
    fence2.hd.c[0][0] = fence2.hd.c[1][0] = 215;

}


void HienThi(Man man, Fence fence, Fence fence1, VatPham vp, Fence fence2)
{

    clrscr();
    char a = 196;
    char b = 217;
    char c = 179;
    for ( int i = 0 ; i < ConsoleWidth ; i++)
    {
        gotoXY(i,ConsoleHeight - 1);
        cout << a;
    }
    for ( int i = 0 ; i < ConsoleHeight  ; i++)
    {
        gotoXY(ConsoleWidth, i);
        if (i == ConsoleHeight - 1 )
            cout << b;
        else
            cout << c;
    }

    for (int i = -1 ; i <= 1 ; i++)
    {
        for (int j = -1 ; j <= 1 ; j++)
        {
        gotoXY(j + man.td.x,i + man.td.y);
        cout << man.hd.a[i+1][j+1];
        }
    }

    for (int i = 0 ; i <= 1 ; i++)
    {
        for (int j = 0 ; j <= 2 ; j++)
        {
        gotoXY(j + fence.td.x,i + fence.td.y);
        cout << fence.hd.b[i][j];
        }
    }

    for (int i = 0 ; i < 2 ; i++)
    {
        for (int j = 0 ; j < 1 ; j++)
        {
        gotoXY(j + fence1.td.x,i + fence1.td.y);
        cout << fence1.hd.c[i][j];
        }
    }

    for (int i = 0 ; i <= 1 ; i++)
        for (int j = 0 ; j < 1 ; j++)
    {
        gotoXY(j + fence2.td.x,i + fence2.td.y);
        cout << fence2.hd.c[i][j];
    }
    gotoXY(15,1);
    cout << " Press Space to Jump";
    gotoXY(60, 1);
    cout << "SCORE: " << man.diem;
}

void DieuKhien(Man &man)
{
    if (man.tt == STAND)
    {
        if (kbhit())
        {
            int key = _getch();
            if (key == 32  )
            {
                man.tt = UP;
                man.td.y--;
            }
        }
    }
}

void XuLy(Man &man, Fence &fence, Fence &fence1, VatPham &vp, Fence &fence2)
{

    if (man.tt == UP && man.td.y > ConsoleHeight - 8)
        man.td.y--;
    else if (man.tt == UP && man.td.y == ConsoleHeight - 8)
    {
        man.td.y++;
        man.tt = DOWN;
    }
    else if (man.tt == DOWN && man.td.y < ConsoleHeight - 3)
        man.td.y++;
    else if (man.tt == DOWN && man.td.y == ConsoleHeight - 3)
    {
        man.tt = STAND;
    }

    fence.td.x--;
    srand(time(NULL));
    if (fence.td.x == 20 + rand() % 30 || fence1.td.x != ConsoleWidth)
        fence1.td.x--;
    if (fence1.td.x == 20 + rand() % 30 || fence2.td.x != ConsoleWidth)
        fence2.td.x--;
    if (fence.td.x < 0)
    {
        man.diem++;
        fence.td.x = ConsoleWidth;
    }
    if (fence1.td.x < 0)
    {
        man.diem++;
        fence1.td.x = ConsoleWidth;
    }

    if (fence2.td.x < 0)
    {
        man.diem++;
        fence2.td.x = ConsoleWidth;
    }
}

int VaCham(Man man, Fence fence, Fence fence1, Fence fence2)
{
    if (abs(man.td.x - fence.td.x) <= 1 && abs(man.td.y - fence.td.y) <= 1 || abs(man.td.x - fence1.td.x) <= 1 && abs(man.td.y - fence1.td.y) <= 1)
        return 1;
    else if (abs(man.td.x - fence2.td.x) <= 1 && abs(man.td.y - fence2.td.y) <= 1)
        return 1;
    else
        return 0;
}

void GameOver(Man man)
{
    clrscr();
    gotoXY(ConsoleWidth/2, ConsoleHeight/2);
    cout << "GAME OVER" ;
    gotoXY(ConsoleWidth/2 - 1, ConsoleHeight/2 + 1);
    cout << " BEST: " << man.diem;
    gotoXY(ConsoleWidth/2 - 2, ConsoleHeight/2 + 2);
    cout << "Press X to "
    _getch();
}
int main()
{
    Man man;
    Fence fence, fence1, fence2;
    VatPham vp;
    KhoiTao(man);
    KhoiTaoFence(fence, fence1 , fence2);
    start:
    while (1)
    {
        HienThi(man,fence, fence1, vp, fence2);
        DieuKhien(man);
        XuLy(man,fence, fence1, vp, fence2);
        if (VaCham(man, fence, fence1, fence2) == 1)
           goto over;
        Sleep(100);
    }

    over:
    GameOver(man);

    return 0;
}
