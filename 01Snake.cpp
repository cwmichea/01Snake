// 01Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//
//int main()
//{
//    std::cout << "Hello World!\n";
//    
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
#include <iostream>
#include <conio.h>

using namespace std;

bool gameover;

const int width = 25;

const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100]; //snake coordinates

int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Controls

eDirecton dir;

void Setup() {
    gameover = false;

    dir = STOP;

    x = width / 2; //Head of the snake placed at the center of the frame in y

    y = height / 2; //Head of the snake placed at the center of the frame in x

    fruitX = rand() % width; //Display fruit in a random place in x

    fruitY = rand() % height; //Display fruit in a random place in y 
    
    score = 0;

}

void Draw() {
    //clean screen
    system("cls");

    for (int i = 0; i < width + 2; i++) //00
        cout << "#";                    // make the upper wall

    cout << endl;

    for (int i = 0; i < height; i++) {// make a number line

        for (int j = 0; j < width; j++) {// make a line

            if (j == 0)        //01
                cout << "#";   // make left walls

            if (j == width - 1)//02
                cout << "#";   // make right walls

            if (i == y && j == x)//03.a
                cout << "*";   // make snake tale

            else if (i == fruitY && j == fruitX)//03.b
                cout << "%";   // make the fruit

            else {//03.c
                bool print = false;
                                                 //03.c   
                for (int k = 0; k < nTail; k++) {//make the body
                    if (tailX[k] == j && tailY[k] == i) {

                        cout << "*"; print = true;

                    }
                }                       //03.d
                if (!print) cout << " ";//print empty space
            }

        }

        cout << endl;

    }

    for (int i = 0; i < width + 2; i++) //
        cout << "#";

    cout << endl;

    cout << "Score:" << score << endl;

}

void Input()
{

    if (_kbhit()) {

        switch (_getch()) {

        case 'a':

            dir = LEFT;

            break;

        case 'd':

            dir = RIGHT;

            break;

        case 'w':

            dir = UP;

            break;

        case 's':

            dir = DOWN;

            break;

        case 'x':

            gameover = true;

            break;

        }

    }

}

void algorithm()
{

    int prevX = tailX[0];

    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;

    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {

        prev2X = tailX[i];

        prev2Y = tailY[i];

        tailX[i] = prevX;

        tailY[i] = prevY;

        prevX = prev2X;

        prevY = prev2Y;

    }

    switch (dir) {

    case LEFT:

        x--;

        break;

    case RIGHT:

        x++;

        break;

    case UP:

        y--;

        break;

    case DOWN:

        y++;

        break;

    default:

        break;

    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;// teletransport to the opposite side in x

    if (y >= height) y = 0; else if (y < 0) y = height - 1;//teletransport to the opposite side in y

    for (int i = 0; i < nTail; i++)//if the snake hit with itself, game over!

        if (tailX[i] == x && tailY[i] == y)
            gameover = true;    

    if (x == fruitX && y == fruitY) {// if the head of the snake reaches the fruit

        score += 10;            //add 10 points to the score

        fruitX = rand() % width;//create a new fruit, x position

        fruitY = rand() % height;// create a new fruit, y position

        nTail++;                // amplify the number/long of the snake, therefore, create a new chaineslabon

    }

}

int main()
{

    Setup();

    while (!gameover) {

        Draw();

        Input();

        algorithm();

    }

    return 0;

}