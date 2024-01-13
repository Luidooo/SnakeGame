#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define cols 10
#define rows 10

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


int snakeX = 5;
int snakeY = 5;
void draw_snake(){
    matrix[snakeY*cols + snakeX] = '@';
}

void move_snake(int x, int y){
    clear();
    snakeX += x;
    snakeY += y;
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

    while(1){
        fill_matrix();
        draw_snake();
        print_matrix();
        refresh();
        read_keyboard();
    }
    return 0;
}

