#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define cols 20
#define rows 20
#define food_qtd 5

int gameOver = 0;

char matrix[cols * rows];

void init_matrix(){
    for(int y=0;y<rows*cols;y++){
            matrix[y] = ' ';
    }
}

void fill_matrix(){
    int x,y;

    for(y=0; y<rows; y++){
        for(x=0; x<cols; x++){
            if(x==0||y==0||x==cols-1||y==rows-1){
                matrix[y*cols + x] = 'x';
            }else
                matrix[y*cols + x] = ' ';
        }
    }
}

#define SNAKE_MAX_LEN 256

struct snakePart{
    int x;
    int y;
};

struct Snake{
    int length;
    struct snakePart part[SNAKE_MAX_LEN];
};

struct Snake snake;

struct Food{
    int x,y;
    int consumed;
};

struct Food foods[food_qtd];

void draw_snake(){

    for(int i=snake.length-1; i>=0; i--){
         matrix[snake.part[i].y*cols + snake.part[i].x] = '*';
    }
    matrix[snake.part[0].y*cols + snake.part[0].x] = '@';
}

void move_snake(int x, int y){

    clear();
    for(int i=snake.length-1; i>0; i--){
        snake.part[i] = snake.part[i-1];
    }
    snake.part[0].x += x;
    snake.part[0].y += y;
}

void read_keyboard(){
    int ch = getch();
    switch(ch){
        case 'w': move_snake(0,-1); break;
        case KEY_UP : move_snake(0,-1); break;
        case 's': move_snake(0,1); break;
        case KEY_LEFT : move_snake(0,1); break;
        case 'a': move_snake(-1,0); break;
        case KEY_RIGHT: move_snake(-1,0); break;
        case 'd': move_snake(1,0); break;
        case KEY_LEFT: move_snake(1,0); break;

    }
}

void draw_food(){
    for(int i=0; i < food_qtd;i++){
        if(!foods[i].consumed){
            matrix[foods[i].y*cols + foods[i].x] = '+';
        }
    }
}

void create_food(){
 for(int i=0; i < food_qtd;i++){
    foods[i].x = 1+rand() %(cols-2);
    foods[i].y = 1+rand() %(rows-2);
    foods[i].consumed = 0;
 }
}

void create_snake(){
    snake.length = 1;
    snake.part[0].x = 1+rand() %(cols-2);
    snake.part[0].y = 1+rand() %(rows-2);
}

void print_matrix(){
    int x,y;

    printw("Snake Game!\n");
    for(y=0; y<rows; y++){
        for(x=0; x < cols; x++){
            addch(matrix[y*cols + x]);
        }
        addch('\n');
        }
    if(!gameOver)
       printw("Score: %d\n", snake.length*100);
    else
        printw("Game Over! Final score: %d\n", snake.length*100);

}

void game_logic(){
    for(int i=0; i<food_qtd; i++){
        if(!foods[i].consumed){
            if(foods[i].x == snake.part[0].x &&
                    foods[i].y == snake.part[0].y){
                        foods[i].consumed = 1;
                        snake.length++;
            }
        }
        if(snake.part[0].x == 0 || snake.part[0].x == cols-1||
           snake.part[0].y == 0 || snake.part[0].y == rows-1)
            gameOver = 1;
        for(int i=1;i<snake.length-1;i++){
            if(snake.part[0].x == snake.part[i].x &&
                snake.part[0].y == snake.part[i].y )
                    gameOver = 1;
        }
    int food_sum = 0;
    for(int i=0; i<food_qtd;i++)
        food_sum += foods[i].consumed;
    if(food_sum==food_qtd)
        create_food();

    }
}

int main(int argc, char ** argv){

    srand(time(0));
    initscr();
    init_matrix();
    create_food();
    create_snake();

        while(!gameOver){
        fill_matrix();
        draw_food();
        draw_snake();
        game_logic();
        print_matrix();
        refresh();
        read_keyboard();
    }

    print_matrix();
    while(1) getch();

    return 0;
}

