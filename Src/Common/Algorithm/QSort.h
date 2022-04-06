#ifndef _QSORT_H_
#define _QSORT_H_

void Swap(void *array[], int i, int j)
{
    void *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int Partition(void *array[], int left, int right, int (*compare)(const void *, const void *, void *), void *args)
{
    int i = left;
    int j = right;
    void *pivot = array[(left + right) / 2];
    while (i <= j) {
        while (compare(array[i], pivot, args) < 0) {
            i++;
        }
        while (compare(array[j], pivot, args) > 0) {
            j--;
        }
        if (i <= j) {
            Swap(array, i, j);
            i++;
            j--;
        }
    }
    return i;
}

void QSort(void *array[], int left, int right, int (*compare)(const void *, const void *, void *), void *args)
{
    if (left < right) {
        int pivot = Partition(array, left, right, compare, args);
        QSort(array, left, pivot - 1, compare, args);
        QSort(array, pivot + 1, right, compare, args);
    }
}

#endif