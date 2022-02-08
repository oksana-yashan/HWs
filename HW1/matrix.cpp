#include "matrix.h"
#include <cstdlib>
#include <ctime>


Matrix::Matrix(const int N, const int M) : n_rows(N), n_col(M) {
    
    // dynamic matrix initialization
    alloc();
}

void Matrix::alloc() {
    matrix = new float* [n_rows];
    for (int i=0; i<n_rows; ++i) {
        // allocation
        matrix[i] = new float[n_col];
    }
}

void Matrix::dealloc() {
    for (int i = 0; i < n_rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Matrix::Matrix(const Matrix& m) : n_rows(m.n_rows), n_col(m.n_col) {
    
    alloc();

    // copying matrix values
    for (int i=0; i<n_rows; ++i) {
        for (int j = 0; j < n_col; ++j) {
            matrix[i][j] = m.matrix[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m) {
        return *this;
    }

    if (n_rows != m.n_rows || n_col != m.n_col) {
        dealloc();
        n_rows = m.n_rows; n_col = m.n_col; 
        alloc();
    }

    for (int i=0; i<n_rows; ++i) {
        for (int j = 0; j < n_col; ++j) {
            matrix[i][j] = m.matrix[i][j];
        }
    }
    return *this;
}

Matrix::~Matrix() {
    // deleting heap blocks
    for (int i=0; i<n_rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
}


void Matrix::random_fill() {

    const int FLOAT_MIN = 10;
    const int FLOAT_MAX = 100;
    
    std::srand(std::time(nullptr));
    for (int i = 0; i < n_rows; i++) {
        for (int j=0; j<n_col; ++j) {
            matrix[i][j] = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        }
    }
}


Matrix Matrix::row_sum_matrix( ) const {
    Matrix sum_by_row(n_rows, 1);

    for (int i=0; i<n_rows; ++i) {
        sum_by_row.matrix[i][0] = 0;
        for (int j=0; j<n_col; ++j) {
            sum_by_row.matrix[i][0] += matrix[i][j];
        } 
    }
    return sum_by_row;
}

Matrix Matrix::column_sum_matrix( ) const {
    Matrix sum_by_column(1, n_col);

    for (int i=0; i<n_col; ++i) {
        sum_by_column.matrix[0][i] = 0;
        for (int j=0; j<n_rows; ++j) {
            sum_by_column.matrix[0][i] += matrix[j][i];
        } 
    }
    return sum_by_column;
}



Matrix Matrix::transpose() const {
    Matrix transposed_matrix(n_col, n_rows);

    for (int i=0; i<n_rows; ++i) {
        for (int j=0; j<n_col; ++j) {
            transposed_matrix.matrix[j][i] = matrix[i][j];
        } 
    }
    return transposed_matrix;
}

void Matrix::check_size_for_mult(int N1, int M1) const {
    if (M1 != n_rows) {
        throw std::logic_error("Sizes are not suitable for multiplication!");
    }
}

void Matrix::check_size_equality(int N1, int M1) const {
    if (n_rows != N1 && n_col != M1) {
        throw std::logic_error("Sizes are not equal!");
    }
}


Matrix operator+(const Matrix& m1, const Matrix& m2) {
    const int N = m1.n_rows;
    const int M = m1.n_col;
    // check for size equality
    m2.check_size_equality(N, M);
    // summation
    Matrix sum_matrix(N, M);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            sum_matrix.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j] ;
        } 
    }
    return sum_matrix;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    const int N = m1.n_rows;
    const int M = m1.n_col;
    // check for size equality
    m2.check_size_equality(N, M);
    // subtraction
    Matrix subtr_matrix(N, M);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            subtr_matrix.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j] ;
        } 
    }
    return subtr_matrix;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    const int N1 = m1.n_rows;
    const int M1 = m1.n_col;
    const int M2 = m2.n_col;
    // check for multiplication sizes
    m2.check_size_for_mult(N1, M1);

    Matrix mul_matrix(N1, M2);
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < M2; j++) {
            mul_matrix.matrix[i][j] = 0;
 
            for (int k = 0; k < M1; k++) {
                mul_matrix.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
            }
        }
    }
    return mul_matrix;
}




std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.n_rows; ++i) {
        os << m.matrix[i][0];
        for (int j = 1; j < m.n_col; ++j) {
            os << " " << m.matrix[i][j];
        }
        os << std::endl;
    }
    return os;
}