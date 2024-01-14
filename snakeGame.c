#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define cols 20
#define rows 20

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

void print_matrix(){
    int x,y;

    for(y=0; y<rows; y++){
        for(x=0; x < cols; x++){
            addch(matrix[y*cols + x]);
        }
        addch('\n');
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

void draw_snake(){
    for(int i=snake.length-1; i>0; i--){
        matrix[snake.part[i].y*cols + snake.part[i].x] = '*';
    }
    matrix[snake.part[0].y*cols + snake.part[0].x] = '@';
}

void move_snake(int x, int y){

    for(int i=snake.length-1; i>0; i--){
        clear();
        snake.part[i] = snake.part[i-1];
    }
    snake.part[0].x += x;
    snake.part[0].y += y;
}

void read_keyboard(){
    int ch = getch();
    switch(ch){
        case 'w': move_snake(0,-1); break;
        case 's': move_snake(0,1); break;
        case 'a': move_snake(-1,0); break;
        case 'd': move_snake(1,0); break;
    }
}

int main(int argc, char ** argv){

    initscr();
    init_matrix();
    snake.length = 4;
    snake.part[0].x = 5;
    snake.part[0].y = 5;
    snake.part[1].x = 5;
    snake.part[1].y = 6;
    snake.part[2].x = 5;
    snake.part[2].y = 7;
    snake.part[3].x = 5;
    snake.part[3].y = 8;

    while(!gameOver){
        fill_matrix();
        draw_snake();
        print_matrix();
        refresh();
        read_keyboard();
    }
    return 0;
}

