#include <iostream>
#include <ostream>

class Matrix { 
public:
    Matrix(const int N, const int M);
    Matrix(const Matrix& m);
    Matrix& operator=(const Matrix& m);
    ~Matrix();

    void random_fill();
    Matrix row_sum_matrix() const;
    Matrix column_sum_matrix() const;
    Matrix transpose() const;
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);
    friend Matrix operator*(const Matrix&, const Matrix&);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
 
private:
    void alloc();
    void dealloc();
    void check_size_equality(int N1, int M1) const;
    void check_size_for_mult(int N1, int M1) const;

    float** matrix;
    int n_rows, n_col;
};
