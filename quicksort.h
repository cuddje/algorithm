int partition(int A[], int low, int high)
{
    int pivot = A[low];
    while(low < high)
    {
        while(low < high && A[high] >= pivot) --high;
        A[low] = A[high];

        while (low < high && A[low] <= pivot) ++low;
        A[high] = A[low];
    }

    A[low] = pivot;
    return low;
}

void _quick_sort(int A[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(A, low, high);
        _quick_sort(A, low, pivot - 1);
        _quick_sort(A, pivot + 1, high);
    }
} 

void quick_sort(int A[], int len)
{
    _quick_sort(A, 0, len-1); 
}