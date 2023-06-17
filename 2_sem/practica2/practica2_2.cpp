#include <iostream>

const int N = 1000;

void copy(int* arr1, int* arr2, size_t size)
{
    // how much fits in one unit, how many units
    size_t unitSize = sizeof(size_t) / sizeof(int);        // 8/4=2
    size_t amountOfUnits = size / unitSize;

    // copy the units
    size_t* temp1 = reinterpret_cast<size_t*>(arr1);     // reinterpret_cast converts between types by reinterpreting the underlying bit pattern
    size_t* temp2 = reinterpret_cast<size_t*>(arr2);
    for (size_t i = 0; i < amountOfUnits; i++)
    {
        *temp1++ = *temp2++;
    }

    // copy the remaining elements
    char* temp1char = reinterpret_cast<char*>(temp1);
    char* temp2char = reinterpret_cast<char*>(temp2);
    size_t bytesLeft = (size - amountOfUnits * unitSize) * sizeof(int);
    for (size_t i = 0; i < bytesLeft; i++)
    {
        *temp1char++ = *temp2char++;
    }
}

void output(int* array) {
    for (int i = 0; i < 7; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int arr1[N] = { 2, 4, 6, 8, 10, 12, 14};
    int arr2[N] = { 1, 3, 5, 7 };

    copy(arr2, arr1, N);
    output(arr2);
    output(arr1);

    return 0;
}