//#include <stdio.h>
#include <ncurses.h>

#define cols 10
#define rows 10



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
            }
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

int main(int argc, char ** argv){

    initscr();
    init_matrix();
    fill_matrix();
    print_matrix();
    refresh();
    getch();
    endwin();
    return 0;
}

