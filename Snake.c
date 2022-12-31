#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
//direction keys
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
//global variables
typedef struct
{
    int x;
    int y;
    int direction;
}object;

object head,food,body[20];
int board[20][30],count,score;
//functions
void Menu();
void SelectLevel();
void Move();//for total move of snake
void Board();//for updating the board with new values
void Food();//for making food in the board
void Print();//prints the whole board
int Failure();
int Victory();
int Eat();//when eats, adds a part of body
void level1();//starts level1
void level2();//starts level2
void level3();//starts level3
void gotoxy(int x, int y)
{
HANDLE hConsoleOutput;
COORD dwCursorPosition;
dwCursorPosition.X=x;
dwCursorPosition.Y=y;
hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
//moving functions
void up(object* x)
{
    x->y--;
}

void down(object* x)
{
    x->y++;
}

void left(object* x)
{
    x->x--;
}

void right(object* x)
{
    x->x++;
}

int main()
{
    while(1)
    {
        system("cls");
        score=0;
        Menu();


    }
    return 0;
}

void Menu()
{
     while(1)
    {

        printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\t%cSTART GAME%c\n\tSELECT DIFFICULTY\n\tEXIT\n",16,17);
        int c=getch();
        if(c==ENTER)
            level1();
        c=getch();
        if(c==DOWN)
        {
            system("cls");
            printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\tSTART GAME\n\t%cSELECT DIFFICULTY%c\n\tEXIT\n",16,17);
            c=getch();
            if(c==ENTER)
                SelectLevel();
            c=getch();
        }
        if(c==DOWN)
        {
            system("cls");
            printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\tSTART GAME\n\tSELECT DIFFICULTY\n\t%cEXIT%c\n",16,17);
            c=getch();
            if(c==ENTER)
                exit(0);
            c=getch();
        }
        system("cls");
    }
}

void SelectLevel()
{
    system("cls");
    while(1)
    {
        printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\t%cEASY%c\n\tMEDIUM\n\tHARD\n\tBack\n",16,17);
        int c=getch();
        if(c==ENTER)
            level1();
        c=getch();
        if(c==DOWN)
        {
            system("cls");
            printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\tEASY\n\t%cMEDIUM%c\n\tHARD\n\tBack\n",16,17);
            c=getch();
            if(c==ENTER)
                level2();
            c=getch();
        }
        if(c==DOWN)
        {
            system("cls");
            printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\tEASY\n\tMEDIUM\n\t%cHARD%c\n\tBack\n",16,17);
            c=getch();
            if(c==ENTER)
                level3();
            c=getch();
        }
        if(c==DOWN)
        {
            system("cls");
            printf("\n\t .::SUPER SNAKE::.\n\n\n\n\n\tEASY\n\tMEDIUM\n\tHARD\n\t%cBack%c\n",16,17);
            c=getch();
            if(c==ENTER)
                return;
            c=getch();
        }
        system("cls");
    }


}

void Move()
{
    while(_kbhit())
    {
        //gets a key and changes head direction.
        int c=getch();
        switch(c)
        {
            case UP:if(head.direction==DOWN)break;head.direction=UP;break;
            case DOWN:if(head.direction==UP)break;head.direction=DOWN;break;
            case LEFT:if(head.direction==RIGHT)break;head.direction=LEFT;break;
            case RIGHT:if(head.direction==LEFT)break;head.direction=RIGHT;break;
        }
    }
    //changes each body part's coordinates with the one after.
    //starts with the last body part.
    int i;
    for(i=19;i>0;i--)
    {
        if(body[i].direction)
        {
            body[i].x=body[i-1].x;
            body[i].y=body[i-1].y;
        }
    }
    //changes first body part's coordinates with head coordinates.
    body[0].x=head.x;
    body[0].y=head.y;
    //moves head one cell based on head direction using moving functions.
    switch(head.direction)
    {
        case UP: up(&head);break;
        case DOWN: down(&head);break;
        case LEFT: left(&head);break;
        case RIGHT: right(&head);break;
    }
}

void Board()
{
    int i,j,k;
    //changes all but walls to zero.
    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        {
            if(board[i][j]==1)
                continue;
            board[i][j]=0;
        }
    }

    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        {
            //specifies head location with the number 2.
            if(head.y==i&&head.x==j)
            {
                board[i][j]=2;
                continue;
            }
            else
            {
                //specifies body part's locations with the number 3.
                for(k=0;k<20;k++)
                {
                    if(body[k].direction&&body[k].x==j&&body[k].y==i)
                    {
                        board[i][j]=3;
                        break;
                    }
                }
            }
            //specifies food location with the number 4.
            if(food.x==j&&food.y==i)
            {
                board[i][j]=4;
                continue;
            }
        }
    }
}

void Food()
{
    srand(time(NULL));
    while(1)
    {
        food.x=rand()%28+1;//from 1st cell to 29th cell horizontally.
        food.y=rand()%18+1;//from 1st cell to 19th cell vertically.
        if(board[food.y][food.x]==0)
            break;
    }
}

void Print()
{
    int i,j;

    //board
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);//purple
    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        {
            if((i!=0&&i!=19)&&(j==0 || j==29))
            {
                printf("%c",186);
                continue;
            }

            else if((i==0||i==19)&&(j!=0 && j!=29))
            {
                printf("%c",205);
                continue;
            }
            else if(i==0&&j==0)
            {
                printf("%c",201);
                continue;
            }
            else if(i==0&&j==29)
            {
                printf("%c",187);
                continue;
            }
            else if(i==19&&j==0)
            {
                printf("%c",200);
                continue;
            }
            else if(i==19&&j==29)
            {
                printf("%c",188);
                continue;
            }

            switch(board[i][j])
            {
                case 0:printf(" ");break;//blank space
                case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);printf("%c",177);break;//purple barrier
                case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);printf("%c",2);break;//light blue head
                case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);printf("%c",79);break;//light blue body
                case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);printf("%c",248);break;//red food
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);//purple
        }
        printf("\n");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);//white
    printf("\n\n\tSCORE:  %d\n",score);
}

int Failure()
{
    int flag=0;
    if(board[head.y][head.x]!=2/*head*/&&board[head.y][head.x]!=0/*blank*/&&board[head.y][head.x]!=4/*food*/)
        flag=1;
    return flag;
}

int Eat()
{
    int flag=0;
    if(board[head.y][head.x]==4/*food*/)
        flag=1;
    return flag;
}

int Victory()
{
    int flag=0;
    if(count==18)
        flag=1;
    return flag;
}

void level1()
{
    system("cls");
    count=0;
    int i,j;
    for(i=0;i<20;i++)
    {
        body[i].direction=0;//activates body parts
    }
    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        {
            if(i==0||j==0||i==19||j==29)
                board[i][j]=1;//specifies walls
            else
                board[i][j]=0;
        }
    }
    head.x=15;
    head.y=10;
    head.direction=RIGHT;
    for(i=0;i<2;i++)
    {
        body[i].x=14-i;
        body[i].y=10;
        body[i].direction=RIGHT;
    }
    Food();
    Board();
    Print();
    getch();
    while(1)
    {
        gotoxy(0,0);
        Move();
        if(Failure())
        {
            system("cls");
            printf("Game Over!!!\a\n");
            getch();
            system("cls");
            return;
        }
        if(Victory())
        {
            system("cls");
            printf("\n\tYay!!\n\n\tYou Won%c!!\n\n\tClick Space to go Next Level!\n",2);
            getch();
            system("cls");
            level2();
            return;
        }
        if(Eat())
        {
            for(i=0;i<20;i++)
            {
                if(body[i].direction==0)
                {
                    body[i].direction = 1;
                    break;
                }
            }
            count++;
            score+=10;
            Food();
        }
        Board();
        Print();
        Sleep(250);
    }
}

void level2()
{
    system("cls");
    count=0;
    int i,j;
    for(i=0;i<20;i++)
    {
        body[i].direction=0;
    }
    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        {
            if(i==0||j==0||i==19||j==29)
                board[i][j]=1;
            else
                board[i][j]=0;
        }
    }
    srand(time(NULL));
    int x,y;//barrier
    for(i=0;i<15;i++)
    {
        x=rand()%28+1;
        Sleep(10);
        y=rand()%18+1;
        board[y][x]=1;
    }
    head.x=15;
    head.y=10;
    head.direction=RIGHT;
    for(i=0;i<2;i++)
    {
        body[i].x=14-i;
        body[i].y=10;
        body[i].direction=RIGHT;
    }
    Food();
    Board();
    Print();
    getch();
    while(1)
    {
        gotoxy(0,0);
        Move();
        if(Failure())
        {
            system("cls");
            printf("Game Over!!!\a\n");
            getch();
            system("cls");
            return;
        }
        if(Victory())
        {
            system("cls");
            printf("\n\tYay!!\n\n\tYou Won%c!!\n\n\tClick Space to go Next Level!\n",2);
            getch();
            system("cls");
            level3();
            return;
        }
        if(Eat())
        {
            for(i=0;i<20;i++)
            {
                if(body[i].direction==0)
                {
                    body[i].direction = 1;
                    break;
                }
            }
            count++;
            score+=10;
            Food();
        }
        Board();
        Print();
        Sleep(200);
    }
}

void level3()
{
    system("cls");
    count=0;
    int i,j;
    for(i=0;i<20;i++)
    {
        body[i].direction=0;
    }
    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        {
            if(i==0||j==0||i==19||j==29)
                board[i][j]=1;
            else
                board[i][j]=0;
        }
    }
    srand(time(NULL));
    int x,y;//barrier
    for(i=0;i<35;i++)
    {
        x=rand()%28+1;
        Sleep(10);
        y=rand()%18+1;
        board[y][x]=1;
    }
    head.x=15;
    head.y=10;
    head.direction=RIGHT;
    for(i=0;i<2;i++)
    {
        body[i].x=14-i;
        body[i].y=10;
        body[i].direction=RIGHT;
    }
    Food();
    Board();
    Print();
    getch();
    while(1)
    {
        gotoxy(0,0);
        Move();
        if(Failure())
        {
            system("cls");
            printf("Game Over!!!\a\n");
            getch();
            system("cls");
            return;
        }
        if(Victory())
        {
            system("cls");
            printf("\n\tYay!!\n\n\tYou Won%c!!\n\n\tClick Space to go Next Level!\n",2);
            getch();
            system("cls");
            level2();
            return;
        }
        if(Eat())
        {
            for(i=0;i<20;i++)
            {
                if(body[i].direction==0)
                {
                    body[i].direction = 1;
                    break;
                }
            }
            count++;
            score+=10;
            Food();
        }
        Board();
        Print();
        Sleep(200);
    }
}
