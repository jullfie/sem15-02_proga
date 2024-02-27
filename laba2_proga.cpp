#include <iostream>
#include <cstdlib> // для генерации случайных чисел

class Matrix {
private:
    int** data; // двумерный массив
    unsigned int m; // количество строк
    unsigned int n; // количество столбцов

public:
    // Конструктор, выделяющий память под двумерный массив
    Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
        data = new int*[m];
        for (unsigned int i = 0; i < m; i++) {
            data[i] = new int[n];
        }
    }

    // Деструктор, освобождающий память
    ~Matrix() {
        for (unsigned int i = 0; i < m; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Заполнение массива случайными значениями от 0 до 9
    void fillRandom() {
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                data[i][j] = rand() % 10;
            }
        }
    }

    // Перегрузка оператора [] для доступа по индексу с возможностью изменения элемента
    int* operator[](unsigned int index) {
        return data[index];
    }

    // Перегрузка оператора вывода в поток <<
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; i++) {
            for (unsigned int j = 0; j < matrix.n; j++) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    // Перегрузка оператора +=
    Matrix& operator+=(const Matrix& other) {
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    // Перегрузка оператора +
    Matrix operator+(const Matrix& other) const {
        Matrix result(m, n);
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора -=
    Matrix& operator-=(const Matrix& other) {
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    // Перегрузка оператора -
    Matrix operator-(const Matrix& other) const {
        Matrix result(m, n);
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора *
    Matrix operator*(const Matrix& other) const {
        Matrix result(m, other.n);
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < other.n; j++) {
                result.data[i][j] = 0;
                for (unsigned int k = 0; k < n; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Перегрузка оператора !=
    bool operator!=(const Matrix& other) const {
        if (m != other.m || n != other.n) {
            return true;
        }
        for (unsigned int i = 0; i < m; i++) {
            for (unsigned int j = 0; j < n; j++) {
                if (data[i][j] != other.data[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }

    // Перегрузка оператора ==
    bool operator==(const Matrix& other) const {
        return !(*this != other);
    }
};

int main() {
    Matrix matrix1(3, 3);
    matrix1.fillRandom();
    std::cout << "Matrix 1:" << std::endl;
    std::cout << matrix1 << std::endl;

    Matrix matrix2(3, 3);
    matrix2.fillRandom();
    std::cout << "Matrix 2:" << std::endl;
    std::cout << matrix2 << std::endl;

    Matrix matrix3 = matrix1 + matrix2;
    std::cout << "Matrix 3 = Matrix 1 + Matrix 2:" << std::endl;
    std::cout << matrix3 << std::endl;

    Matrix matrix4 = matrix1 * matrix2;
    std::cout << "Matrix 4 = Matrix 1 * Matrix 2:" << std::endl;
    std::cout << matrix4 << std::endl;

    if (matrix1 == matrix2) {
        std::cout << "Matrix 1 is equal to Matrix 2" << std::endl;
    } else {
        std::cout << "Matrix 1 is not equal to Matrix 2" << std::endl;
    }

    return 0;
}
