#include <iostream>
#include <algorithm>

class CoderEncoder {
public:
    static const int N = 3;

    void rotate_90_degrees(int matrix[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N / 2; j++) {
                std::swap(matrix[i][j], matrix[i][N - 1 - j]);
            }
        }
    }

    void printMatrix(int matrix[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    CoderEncoder ce;
    int matrix[CoderEncoder::N][CoderEncoder::N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::cout << "Original Matrix:" << std::endl;
    ce.printMatrix(matrix);

    ce.rotate_90_degrees(matrix);

    std::cout << "\nMatrix after 90 degree rotation:" << std::endl;
    ce.printMatrix(matrix);

    return 0;
}
