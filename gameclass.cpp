#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

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
};

struct Man
{
    ToaDo td;
    HinhDang hd;
    TrangThai tt;
    int diem = 0;
    int constm = 3;
    int sl = 100;
};

struct Obj
{
    ToaDo td;
    HinhDang hd;
};

class GameProgram
{
    public:
        void resizeConsole()
        {
            HWND console = GetConsoleWindow();
            RECT r;
            GetWindowRect(console, &r);
            MoveWindow(console, r.left, r.top, Width, Height, TRUE);
        }
        void KhoiTaoMan()
        {

            man.td.x = 3;
            man.td.y = ConsoleHeight - 3;
            man.tt = STAND;
            man.hd.a[0][1] = 'U';
            man.hd.a[0][0] = man.hd.a[0][2] = ' ';
            man.hd.a[1][0] = man.hd.a[2][0] = '(';
            man.hd.a[1][2] = man.hd.a[2][2] = ')';
            man.hd.a[1][1] = '|';
            man.hd.a[2][1] = '_';
        }
        void KhoiTaoObj()
        {

            obj.td.x = ConsoleWidth + 1;
            obj.td.y = ConsoleHeight - 3;
            obj.hd.b[0][0] = obj.hd.b[0][2] = obj.hd.b[1][1] = '|';
            obj.hd.b[1][0] = obj.hd.b[1][2] = ' ';
            obj.hd.b[0][1] = '_';

            obj1.td.x = ConsoleWidth + 1;
            obj1.td.y = ConsoleHeight - 3;
            obj1.hd.c[0][0] = 'U' ;
            obj1.hd.c[1][0] = 215;

            obj2.td.x = ConsoleWidth + 1;
            obj2.td.y = ConsoleHeight - 3;
            obj2.hd.c[0][0] = obj2.hd.c[1][0] = 215;

        }
        void HienThi()
        {
            clrscr();
            for ( int i = 0 ; i < ConsoleWidth ; i++)
            {
                gotoXY(i,ConsoleHeight - 1);
                cout << bien;
            }
            for (int i = -1 ; i <= 1 ; i++)
            {
                for (int j = -1 ; j <= 1 ; j++)
                {
                gotoXY(j + man.td.x,i + man.td.y);
                cout << man.hd.a[i+1][j+1];
                }
            }
            if (obj.td.x <= ConsoleWidth - 1)
            {
                for (int i = 0 ; i <= 1 ; i++)
                {
                    for (int j = 0 ; j <= 2 ; j++)
                    {
                    gotoXY(j + obj.td.x,i + obj.td.y);
                    cout << obj.hd.b[i][j];
                    }
                }
            }

            if (obj1.td.x <= ConsoleWidth - 1)
            {
                for (int i = 0 ; i < 2 ; i++)
                {
                    for (int j = 0 ; j < 1 ; j++)
                    {
                    gotoXY(j + obj1.td.x,i + obj1.td.y);
                    cout << obj1.hd.c[i][j];
                    }
                }
            }

            if (obj2.td.x <= ConsoleWidth - 1)
            {
                for (int i = 0 ; i <= 1 ; i++)
                    for (int j = 0 ; j < 1 ; j++)
                {
                    gotoXY(j + obj2.td.x,i + obj2.td.y);
                    cout << obj2.hd.c[i][j];
                }
            }

            gotoXY(15,1);
            cout << " Press Space to Jump";
            gotoXY(60, 1);
            cout << "SCORE: " << man.diem;
        }
        void DieuKhien()
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
            if (man.tt == STAND)
            {
                if (kbhit())
                {
                    fflush(stdin);
                    int key = _getch();
                    if (key == 32  )
                    {
                        man.tt = UP;
                        man.td.y--;
                    }
                }
            }
        }
        void XuLy()
        {
            obj.td.x-=tddichuyen;
            if (obj.td.x < 0)
            {
                man.diem+=man.constm;
                obj.td.x = ConsoleWidth + 1;
            }
            if (obj.td.x == ConsoleWidth / (rand () % 2 + 2 ) || obj1.td.x != ConsoleWidth + 1)
                obj1.td.x -=tddichuyen;
            if (obj1.td.x < 0)
            {
                man.diem+=man.constm;
                obj1.td.x = ConsoleWidth + 1;
                man.sl--;
            }
            if (obj1.td.x == ConsoleWidth / (rand () % 2 + 2 ) || obj2.td.x != ConsoleWidth + 1)
                obj2.td.x -=tddichuyen;
            if (obj2.td.x < 0)
            {
                man.diem+=man.constm;
                obj2.td.x = ConsoleWidth + 1;
            }
            man.diem++;
            Sleep(man.sl);
            if (man.diem % 100 == 0 && man.diem != 0)
                man.sl-=5;
        }

        int VaCham()
        {
            if (abs(man.td.x - obj.td.x) <= 1 && abs(man.td.y - obj.td.y) <= 1)
                return 1;
            else if (abs(man.td.x - obj1.td.x) <= 1 && abs(man.td.y - obj1.td.y) <= 1)
                return 1;
            else if (abs(man.td.x - obj2.td.x) <= 1 && abs(man.td.y - obj2.td.y) <= 1)
                return 1;
            else
                return 0;
        }

        void GameOver()
        {

            gotoXY(ConsoleWidth/2, ConsoleHeight/2);
            cout << "GAME OVER" ;
            gotoXY(ConsoleWidth/2 - 3, ConsoleHeight/2 + 1);
            cout << " YOUR SCORES : " << man.diem;
            _getch();
        }
    private:
        Man man;
        Obj obj, obj1, obj2;
        int Width = 700;
        int Height = 400;
        int ConsoleWidth = 90;
        int ConsoleHeight = 20;
        char bien = 196;
        int tddichuyen = 1;
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

        void gotoXY(int x,int y)
        {
            HANDLE hConsoleOutput;
            COORD Cursor_an_Pos = {x-1,y-1};
            hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
        }
};

int main()
{
    GameProgram gp;
    gp.resizeConsole();
    gp.KhoiTaoMan();
    gp.KhoiTaoObj();
    while (1)
    {
        gp.HienThi();
        gp.DieuKhien();
        gp.XuLy();
        if (gp.VaCham() == 1)
            goto over;
    }
    over:
    gp.GameOver();
    return 0;
}
