#include "common.h"
#include "quicksort.h"

using namespace std;

int main(int argc, char* argv[])
{
    printf("Algorithm Test\n");

    int a[50] = {0};
    for (int i=0; i <=50; i++)
    {
        a[i] = rand() % 50;
    }

    //快速排序
    quick_sort(a, sizeof(a)/sizeof(a[0]));


    for (auto v:a)
    {
        cout << v << endl;
    }

    return 0;
}