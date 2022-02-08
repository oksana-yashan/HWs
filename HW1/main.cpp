#include "timer.h"
#include "matrix.h"

int main() {
    
    const int N = 1000;
    const int M = 800;

    Matrix matrix1(N, M);
    Matrix matrix2(N, M);

    // for multiplication
    Matrix matrix3(N, M);
    Matrix matrix4(M, N);

    // random matrix filling 
    matrix1.random_fill();
    matrix2.random_fill();
    matrix3.random_fill();
    matrix4.random_fill();

    // matrix sum by rows 
    {
        Timer t("row_sum_matrix");
        Matrix sum_row = matrix1.row_sum_matrix();
    }

    // matrix sum by columns 
    {
        Timer t("column_sum_matrix");
        Matrix sum_column = matrix1.column_sum_matrix();
    }

    // matrix summation 
    {
        Timer t("matrix summation");
        Matrix sum = matrix1 + matrix2;
    }

    // matrix subtraction
    {
        Timer t("matrix subtraction");
        Matrix sub = matrix1 - matrix2;
    }

    // matrix multiplication
    {
        Timer t("matrix multiplication");
        Matrix mul = matrix3 * matrix4;
    }

    // matrix transpose
    {
        Timer t("matrix transpose");
        Matrix transpose = matrix1.transpose();
    }


    
    return 0;
}