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

struct Obj
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
void KhoiTaoobj(Obj &obj, Obj &obj1, Obj &obj2)
{

    obj.td.x = 15 + rand() % (ConsoleWidth/8 );
    obj.td.y = ConsoleHeight - 3;
    obj.hd.b[0][0] = obj.hd.b[0][2] = obj.hd.b[1][1] = '|';
    obj.hd.b[1][0] = obj.hd.b[1][2] = ' ';
    obj.hd.b[0][1] = '_';

    obj1.td.x = 30 + rand() % (ConsoleWidth/8) ;
    obj1.td.y = ConsoleHeight - 3;
    obj1.hd.c[0][0] = 202 ;
    obj1.hd.c[1][0] = 182;

    obj2.td.x = 50 + rand() % (ConsoleWidth /8 ) ;
    obj2.td.y = ConsoleHeight - 3;
    obj2.hd.c[0][0] = obj2.hd.c[1][0] = 215;

}


void HienThi(Man man, Obj obj, Obj obj1, VatPham vp, Obj obj2)
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
        gotoXY(j + obj.td.x,i + obj.td.y);
        cout << obj.hd.b[i][j];
        }
    }

    for (int i = 0 ; i < 2 ; i++)
    {
        for (int j = 0 ; j < 1 ; j++)
        {
        gotoXY(j + obj1.td.x,i + obj1.td.y);
        cout << obj1.hd.c[i][j];
        }
    }

    for (int i = 0 ; i <= 1 ; i++)
        for (int j = 0 ; j < 1 ; j++)
    {
        gotoXY(j + obj2.td.x,i + obj2.td.y);
        cout << obj2.hd.c[i][j];
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

void XuLy(Man &man, Obj &obj, Obj &obj1, VatPham &vp, Obj &obj2)
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
	obj.td.x--;
	obj1.td.x--;
	obj2.td.x--;
	if (obj.td.x < 0)
	{
		man.diem+=3;
		obj.td.x = ConsoleWidth;
	}
	if (obj1.td.x < 0)
	{
		man.diem+=3;
		obj1.td.x = ConsoleWidth;
	}
	if (obj2.td.x < 0)
	{
		man.diem+=3;
		obj2.td.x = ConsoleWidth;
	}
    
}

int VaCham(Man man, Obj obj, Obj obj1, Obj obj2)
{
    if (abs(man.td.x - obj.td.x) <= 1 && abs(man.td.y - obj.td.y) <= 1 || abs(man.td.x - obj1.td.x) <= 1 && abs(man.td.y - obj1.td.y) <= 1)
        return 1;
    else if (abs(man.td.x - obj2.td.x) <= 1 && abs(man.td.y - obj2.td.y) <= 1)
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

}
int main()
{
    Man man;
    Obj obj, obj1, obj2;
    VatPham vp;
    KhoiTao(man);
    KhoiTaoobj(obj, obj1 , obj2);
    start:
    float i = 0.0001;
    float sl = 100;
    while (1)
    {
        HienThi(man,obj, obj1, vp, obj2);
        DieuKhien(man);
        XuLy(man,obj, obj1, vp, obj2);
        if (VaCham(man, obj, obj1, obj2) == 1)
    		goto over;
        Sleep(sl);
        sl=sl - i;
    }

    over:
    GameOver(man);
    return 0;
}

