#include <iostream>
#include <ostream>

class Matrix { 
public:
    Matrix(const int N, const int M);
    ~Matrix();

    void random_fill();
    Matrix row_sum_matrix() const;
    Matrix column_sum_matrix() const;
    Matrix transpose() const;
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);
    friend Matrix operator*(const Matrix&, const Matrix&);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    

    void check_size_equality(int N1, int M1) const;
    void check_size_for_mult(int N1, int M1) const;

private:
    float** matrix;
    int n_rows, n_col;
};
