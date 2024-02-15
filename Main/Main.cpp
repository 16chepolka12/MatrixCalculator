#include <iostream>

using namespace std;

double** addMatrix(double** matrix, double** matrix2, int rows, int cols);
double** minusMatrix(double** matrix, double** matrix2, int rows, int cols);
double** multiplyMatrix(double** matrix1, double** matrix2, int rows1, int cols1, int rows2, int cols2);
void print_matrix(double** matrix, int rows, int cols);
double** matrixT(double** matrix, int rows1, int cols1);
void delete_matrix(double** matrix, int rows);

int main() {
    system("chcp 1251");
    int rows1, cols1, rows2, cols2;
    // Выбор операции над матрицами
    cout << "Выберите операцию над матрицами:" << endl;
    cout << "\t1: СЛОЖЕНИЕ" << endl;
    cout << "\t2: ВЫЧИТАНИЕ" << endl;
    cout << "\t3: УМНОЖЕНИЕ" << endl;
    cout << "\t4: ТРАНСПОНИРОВАНИЕ" << endl;

    int oper;
    cin >> oper;

    if (oper >= 1 && oper <= 3) {
        cout << "Введите количество строк первой матрицы:" << "\t";
        cin >> rows1;
        cout << "Введите количество столбцов первой матрицы:" << "\t";
        cin >> cols1;
        cout << "Введите количество строк второй матрицы:" << "\t";
        cin >> rows2;
        cout << "Введите количество столбцов второй матрицы:" << "\t";
        cin >> cols2;

        if (cols1 != rows2) {
            cout << "Невозможно выполнить умножение матриц: Количество столбцов первой матрицы не равно количеству строк второй матрицы!" << endl;
            return 1;
        }
    }
    else if (oper == 4) {
        cout << "Введите количество строк матрицы: " << "\t";
        cin >> rows1;
        cout << "Введите количество столбцов матрицы: " << "\t";
        cin >> cols1;
    }
    else {
        cout << "Неправильный ввод операции!";
        return 1;
    }
    // Выделение динамической памяти под матрицы
    double** matrix = new double* [rows1];
    for (int i = 0; i < rows1; i++) {
        matrix[i] = new double[cols1];
    }

    double** matrix2 = nullptr;
    if (oper >= 1 && oper <= 3) {
        matrix2 = new double* [rows2];
        for (int i = 0; i < rows2; i++) {
            matrix2[i] = new double[cols2];
        }
    }

    // Заполнение первой матрицы
    cout << "Введите первую матрицу: " << endl;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            cin >> matrix[i][j];
        }
    }

    // Заполнение второй матрицы
    if (oper >= 1 && oper <= 3) {
        cout << "Введите вторую матрицу : " << endl;
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < cols2; j++) {
                cin >> matrix2[i][j];
            }
        }
    }

    // Вывод изначальных матриц
    cout << "Первая матрица:" << endl;
    print_matrix(matrix, rows1, cols1);

    if (oper >= 1 && oper <= 3) {
        cout << "Вторая матрица:" << endl;
        print_matrix(matrix2, rows2, cols2);
    }


    switch (oper) {
    case 1: {
        double** result_Add = addMatrix(matrix, matrix2, rows1, cols1);
        cout << "Результат сложения: " << endl;
        print_matrix(result_Add, rows1, cols1);
        delete_matrix(result_Add, rows1);
        break;
    }
    case 2: {
        double** result_minus = minusMatrix(matrix, matrix2, rows1, cols1);
        cout << "Результат вычитания матриц: " << endl;
        print_matrix(result_minus, rows1, cols1);
        delete_matrix(result_minus, rows1);
        break;
    }
    case 3: {
        double** result_multiply = multiplyMatrix(matrix, matrix2, rows1, cols1, rows2, cols2);
        cout << "Результат умножения матриц: " << endl;
        print_matrix(result_multiply, rows1, cols2);
        delete_matrix(result_multiply, rows1);
        break;
    }
    case 4: {
        double** result_T = matrixT(matrix, rows1, cols1);
        cout << "Результат транспонирования: " << endl;
        print_matrix(result_T, cols1, rows1);
        delete_matrix(result_T, cols1);
        break;
    }
    default:
        cout << "Неверный выбор операции!" << endl;
        break;
    }

    // Освобождение памяти
    delete_matrix(matrix, rows1);
    if (matrix2 != nullptr) {
        delete_matrix(matrix2, rows2);
    }

    return 0;
}

// Функция вывода матриц
void print_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция освобождения памяти, выделенной под матрицу
void delete_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция сложения матриц
double** addMatrix(double** matrix, double** matrix2, int rows, int cols) {
    double** result_Add = new double* [rows];
    for (int i = 0; i < rows; i++) {
        result_Add[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result_Add[i][j] = matrix[i][j] + matrix2[i][j];
        }
    }
    return result_Add;
}

// Функция вычитания матриц
double** minusMatrix(double** matrix, double** matrix2, int rows, int cols) {
    double** result_minus = new double* [rows];
    for (int i = 0; i < rows; i++) {
        result_minus[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result_minus[i][j] = matrix[i][j] - matrix2[i][j];
        }
    }
    return result_minus;
}

// Функция умножения матриц
double** multiplyMatrix(double** matrix1, double** matrix2, int rows1, int cols1, int rows2, int cols2) {
    double** result_multiply = new double* [rows1];
    for (int i = 0; i < rows1; i++) {
        result_multiply[i] = new double[cols2];
    }

    // Заполняем результирующую матрицу нулями
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            result_multiply[i][j] = 0;
        }
    }

    // Выполняем умножение матриц
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result_multiply[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result_multiply;
}

// Функция транспонирования матрицы
double** matrixT(double** matrix, int rows1, int cols1) {
    double** result_T = new double* [cols1];
    for (int i = 0; i < cols1; i++) {
        result_T[i] = new double[rows1];
    }
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            result_T[j][i] = matrix[i][j];
        }
    }
    return result_T;
}

