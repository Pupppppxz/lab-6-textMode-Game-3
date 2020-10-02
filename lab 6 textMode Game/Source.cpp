#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void gotoxy(int, int);
void draw_ship(int, int);
void erase_ship(int, int);
void set_color(int, int);
void set_cursor(bool);
void draw_bullet(int, int);
void bullet_ship(int, int);
void draw_star(int x, int y);
void erase_bullet(int x, int y);
char cursor(int x, int y);
void draw_score(int x, int y);
void erase_star(int x, int y);

int main()
{
    set_cursor(0);
    srand(time(NULL));

    char ch = ' ';
    int movee[2], x = 38, y = 20, bullet[5];
    int bullet_x[5];
    int bullet_y[5];
    int x_star[20];
    int y_star[20];
    int score = 0;

    draw_ship(x, y);

    for (int i = 0; i < 20; i++)
    {
        x_star[i] = rand() % 100;
        y_star[i] = rand() % 5;
        y_star[i] += 1;

        draw_star(x_star[i], y_star[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        bullet[i] = 0;
    }

    do {
        draw_score(x, y);
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'w')
            {
                movee[0] = 1;
            }
            if (ch == 'a')
            {
                movee[0] = 2;
            }
            if (ch == 'd')
            {
                movee[0] = 3;
            }
            if (ch == 's')
            {
                movee[0] = 4;
            }
            if (ch == ' ')
            {
                for (int i = 0; i < 5; i++)
                {
                    if (bullet[i] == 0)
                    {
                        bullet[i] = 1;
                        bullet_x[i] = x;
                        bullet_y[i] = y - 2;
                        draw_bullet(bullet_x[i], bullet_y[i]);
                        break;
                    }
                }
            }


            fflush(stdin);

        }
        if (movee[0] == 1)
        {
            erase_ship(x, y), draw_ship(x, y);
        }
        if (movee[0] == 3 && x < 113)
        {
            erase_ship(x, y), draw_ship(++x, y);
        }
        if (movee[0] == 2 && x > 0)
        {
            erase_ship(x, y), draw_ship(--x, y);
        }
        if (movee[0] == 4)
        {
            erase_ship(x, y), draw_ship(x, y);
        }
        for (int i = 0; i < 5; i++)
        {
            if (bullet[i] == 1)
            {
                erase_bullet(bullet_x[i], bullet_y[i]);
                if (bullet_y[i] > 0)
                {
                    if (cursor(bullet_x[i], bullet_y[i]) - 1 == '*')
                    {
                        Beep(1000, 100);
                        bullet[i] = 0;
                        erase_bullet(bullet_x[i], bullet_y[i] - 1);
                        erase_star(bullet_x[i], bullet_y[i] - 1);
                        score++;
                        draw_star(rand() % 100, rand() % 5);
                    }
                    else
                    {
                        erase_bullet(bullet_x[i], bullet_y[i]);
                    }
                }
                else
                {
                    erase_bullet(bullet_x[i], bullet_y[i]);
                    bullet[i] = 0;
                }
            }
        }
        Sleep(100);
        set_color(2, 0);
    } while (ch != 'x');

    return 0;
}
void gotoxy(int x, int y)
{
    COORD c = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
    set_cursor(0);
    set_color(2, 4);
    gotoxy(x, y); printf(" <-0-> ");
}
void erase_ship(int x, int y)
{
    set_color(0, 0);
    gotoxy(x, y); printf("       ");
}
void set_color(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void set_cursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void draw_bullet(int x, int y)
{
    set_color(1, 0);
    gotoxy(x, y);
    printf(" < ^ > ");

}
void bullet_ship(int x, int y)
{
    set_color(0, 0);
    gotoxy(x, y);
    printf("        ");
}
void draw_star(int x, int y)
{
    set_color(5, 0);
    gotoxy(x, y);
    printf("*");
}
void erase_star(int x, int y)
{
    set_color(0, 0);
    gotoxy(x, y);
    printf(" ");
}
void draw_score(int x, int y)
{
    set_color(12, 15);
    gotoxy(105, 1);
    printf("============");
    gotoxy(105, 3);
    set_color(12, 0);
    printf("score : %d", score);
    set_color(12, 15);
    gotoxy(105, 5);
    printf("============");
}
char cursor(int x, int y) {
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (
        !ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

        return '\0';
    else
        return buf[0];

}
void erase_bullet(int x, int y)
{
    set_color(0, 0);
    gotoxy(x, y); printf(" ");
}