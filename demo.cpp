#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
using namespace std;

#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1

#define ConsoleWidth 114
#define ConsoleHeight 25
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}


//-------------------------Screen-------------------------
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


//screen: goto [x,y]
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

struct ToaDo
{
    int x; // dong
    int y; // cot
};

struct HinhDang
{
    char a[3][3];
};

struct Nguoi
{
    ToaDo td;
    HinhDang hd;
    char t;
};

struct VatCan
{
    ToaDo td;
    HinhDang hd;
};

void KhoiTao(Nguoi &nguoi)
{
    // nguoi
    TextColor(12);
    nguoi.td.x = 3;
    nguoi.td.y = ConsoleHeight - 3;
    nguoi.t = 'd';
    nguoi.hd.a[0][1] = '0';
    nguoi.hd.a[0][0] = nguoi.hd.a[0][2] = nguoi.hd.a[2][1] = ' ';
    nguoi.hd.a[1][0] = nguoi.hd.a[2][0] = '/';
    nguoi.hd.a[1][2] = nguoi.hd.a[2][2] = '\\';
    nguoi.hd.a[1][1] = '|';
}
void KhoiTao(VatCan &vatcan)
{
    // vat can
    TextColor(10);
    vatcan.td.x = rand() % 100 + 33;
    vatcan.td.y = ConsoleHeight - 3;
    vatcan.hd.a[1][0] = vatcan.hd.a[1][2] = vatcan.hd.a[2][1] = '|';
    vatcan.hd.a[0][1] = vatcan.hd.a[2][0] = vatcan.hd.a[2][2] = vatcan.hd.a[0][0] = vatcan.hd.a[0][2] = ' ';
    vatcan.hd.a[1][1] = '_';
}


void HienThi(Nguoi nguoi, VatCan vatcan)
{
    clrscr();
    // hien thi duong di
    for ( int i = 0 ; i < ConsoleWidth ; i++)
    {
        gotoXY(i,ConsoleHeight-1);
        putchar(196);
    }
    // hien thi nguoi
    for (int Dong = -1 ; Dong <= 1 ; Dong++)
    {
        for (int Cot = -1 ; Cot <= 1 ; Cot++)
        {
        int x = Cot + nguoi.td.x ;
        int y = Dong + nguoi.td.y ;
        gotoXY(x,y);
        cout << nguoi.hd.a[Dong+1][Cot+1];
        }
    }
    // hien thi vat can
    for (int Dong = -1 ; Dong <= 1 ; Dong++)
    {
        for (int Cot = -1 ; Cot <= 1 ; Cot++)
        {
        int x = Cot + vatcan.td.x ;
        int y = Dong + vatcan.td.y ;
        gotoXY(x,y);
        cout << vatcan.hd.a[Dong+1][Cot+1];
        }
    }
}

void DieuKhien(Nguoi &nguoi)
{
    if (nguoi.t == 'd')
    {
        int key = inputKey();
        if (key == 32  )
        {
            nguoi.t = 'l';
            nguoi.td.y--;
        }
    }
}

void XuLy(Nguoi &nguoi, VatCan &vatcan)
{
    // nguoi
    if (nguoi.t == 'l' && nguoi.td.y > ConsoleHeight - 8)
        nguoi.td.y--;
    else if (nguoi.t == 'l' && nguoi.td.y == ConsoleHeight - 8)
    {
        nguoi.td.y++;
        nguoi.t = 'x';
    }
    else if (nguoi.t == 'x' && nguoi.td.y < ConsoleHeight - 3)
        nguoi.td.y++;
    else if (nguoi.t == 'x' && nguoi.td.y == ConsoleHeight - 3)
    {
        nguoi.t = 'd';
    }
    // vat can
    vatcan.td.x--;
    if (vatcan.td.x < 0)
        KhoiTao(vatcan);
}

int main()
{
    Nguoi nguoi;
    VatCan vatcan;
    KhoiTao(nguoi);
    KhoiTao(vatcan);
    while (1)
    {
        // Hiển Thị
        HienThi(nguoi,vatcan);
        // Điều Khiển
        DieuKhien(nguoi);
        // Xử Lý
        XuLy(nguoi,vatcan);
        // Game Over

        Sleep(100);
    }

    return 0;
}
