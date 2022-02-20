//汉诺塔问题
#include "common.h"

int count = 0;

void move(char x, int n, char y)
{
    printf("move %d from %c to %c, times=%d\n", n, x, y, ++count);
}

void hanoi(int n, char x, char y, char z)
{
    if (n == 1){
        move(x, 1, z);
    }else{
        hanoi(n-1, x, z, y);
        move(x, n, z);
        hanoi(n-1, y, x, z);
    }
}

int main(int argc, char* argv[])
{
    hanoi(10, 'a', 'b', 'c');
    return 0;
}