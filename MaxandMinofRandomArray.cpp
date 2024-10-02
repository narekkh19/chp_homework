#include <iostream>
#include <cstdlib>
#include <ctime>

void FindMaxProductElements(int arr[], int arrSize) {
    int maxProduct = arr[0] * arr[1];
    int a = 0, b = 1;

    for (int i = 0; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if (maxProduct <= arr[i] * arr[j]) {
                maxProduct = arr[i] * arr[j];
                a = i;
                b = j;
            }
        }
    }

    std::cout << "\nFirst element: " << arr[a] << " (index: " << a << ")" << std::endl;
    std::cout << "Second element: " << arr[b] << " (index: " << b << ")" << std::endl;
}

int main() {
    srand(time(0));

    int arrSize;
    do {
        std::cout << "Enter the size of the array: ";
        std::cin >> arrSize;
    } while (arrSize < 2);

    int* array = new int[arrSize];

    std::cout << "Array elements: ";
    for (int i = 0; i < arrSize; i++) {
        array[i] = rand() % 20;
        std::cout << array[i] << " ";
    }

    FindMaxProductElements(array, arrSize);

    delete[] array;
    return 0;
}
