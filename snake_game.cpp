#include <iostream>
#include <conio.h>
//#include <windows.h>       Only include this library on windows os when you want to uncomment Sleep() function in the main function below.
//#include<unistd.h>         Only include this library on linux os when you want to uncomment sleep() function in the main function below.
using namespace std;
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailX[100],tailY[100];
int ntail;
int stop=0;
int dir;
void setup()
{
    gameover = false;
    dir = stop;
    x = width/2;
    y = height/2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}
/*
#########
#       #    This is how game will look and its logic is in the draw function.
#F      #     F is fruit.
#   O   #     O is head.
#   o   #     o is tail.
#       #     # is a boundary line.
#########*/
void draw()
{
    system("cls");             //For Windows
    //system("clear");         //For Linux
    for(int i =0;i<width+2;i++)
        cout<<"#";
    cout << endl;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout<<"#";
            if(i==y && j==x)
                cout<<"O";
            else if(i==fruity && j==fruitx)
                cout<<"F";
            else
            {
                bool print = false;
                for(int k=0;k<ntail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
            if(j==width-1)
                cout<<"#";
        }
        cout << endl;
    }

    for(int i=0;i<width+2;i++)
        cout<<"#";
    cout<<endl;
    cout<<"Your Score is:"<<score<<endl;
}
void input()
{
    if(_kbhit()) // khbit function is used to take input of the key which is pressed.
    {
        switch(getch())  // getch function gets the value of that key.
        {
        case 'a':
            dir = 'LEFT';
            break;
        case 'd':
            dir = 'RIGHT';
            break;
        case 's':
            dir = 'DOWN';
            break;
        case 'w':
            dir = 'UP';
            break;
        case 'x':
            gameover = true;
            break;

        }
    }
}
void logic()
{
    for (int i = ntail; i > 0; i--) // the tail part should follow the head part.
    {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = x;
    tailY[0] = y;
    switch(dir)
    {
    case 'LEFT': // if user enters 'a' then it should move left therefore x--
        x--;
        break;
    case 'RIGHT':
        x++;
        break;
    case 'UP':
        y--;
        break;
    case 'DOWN':
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x <0 || y>height || y<0)  if snake hits the boundary then terminate the game.
    //    gameover = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;  // if snake hits the boundary then it does not stop the game rather snake emerges from the other side of the wall.
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < ntail; i++)  // if head touches any part of tail then it should terminate the game.
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;

    if (x==fruitx && y==fruity)  // If snake eats fruit then increase its score and generate another fruit at random place.
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;

    }


}
int main()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        //sleep(10);                If you want to slow down the game in linux.
        //Sleep(10);                If you want to slow down the game in windows.
    }
    return 0;
}
