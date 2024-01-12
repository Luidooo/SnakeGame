#include <stdio.h>
//#include <conio.h>

#define cols 10
#define rows 10



char matrix[cols * rows];

void fill_matrix(){
    int x,y;

    for(y=0; y<rows; y++){
        for(x=0; y<cols; x++){
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
            //printf(matrix[y+cols + x]);
            printf(" # ");
            }
        printf("\n");
        }
}

int main(int argc, char ** argv){

    fill_matrix();
    print_matrix();

    return 0;
}

