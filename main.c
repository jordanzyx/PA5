#include <stdio.h>
#include "header.h"
#include <string.h>

void blah(int *x,int *y,int x1,int y1);
int main() {
    int x = 5;
    int y = 2;

    blah(&x,&y,x,y);
    printf("%d, %d\n",x,y);
    startUpMenu();
    return 0;
}
//Swapping since matt wants comments
void blah(int *x,int *y,int x1,int y1){
    *x = y1;
    *y = x1;
}