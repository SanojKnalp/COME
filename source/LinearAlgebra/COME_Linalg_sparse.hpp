#pragma once
#ifndef COME_LINALG_SPARSEMATRIX_HPP
#define COME_LINALG_SPARSEMATRIX_HPP

#include <armadillo>
#include <stdexcept>
#include "COME_Linalg_vector.h"

namespace LinearAlgebra {

    template <typename T>
    class SparseMatrix {
    public:
        arma::SpMat<T> mat;

        // Constructors
        SparseMatrix() = default;
        SparseMatrix(size_t rows, size_t cols) : mat(rows, cols) {}
        SparseMatrix(const arma::SpMat<T>& A) : mat(A) {}

        // Shape
        size_t rows() const { return mat.n_rows; }
        size_t cols() const { return mat.n_cols; }

        // Element access
        T operator()(size_t i, size_t j) const {
            if (i >= rows() || j >= cols())
                throw std::out_of_range("SparseMatrix index out of bounds");
            return mat(i, j);
        }


        // Set an element (inserts/updates value). Use assignment into SpMat.
        // Note: mat(i,j) = value will insert the value for sparse matrices.
        void set(size_t i, size_t j, const T& value) {
            if (i >= rows() || j >= cols())
                throw std::out_of_range("SparseMatrix index out of bounds");
            mat(i, j) = value;
        }

        // Frobenius norm
        T norm() const {
            return arma::norm(mat, "fro");
        }

        // Matrix-vector multiplication: y = A*x
        Vector<T> operator*(const Vector<T>& x) const {
            if (cols() != x.size())
                throw std::invalid_argument("Dimension mismatch: A*x");

            Vector<T> out(rows());
            out.col = mat * x.col;
            return out;
        }

        // Matrix-matrix multiplication: C = A*B
        SparseMatrix<T> operator*(const SparseMatrix<T>& B) const {
            if (cols() != B.rows())
                throw std::invalid_argument("Dimension mismatch: A*B");

            SparseMatrix<T> C(rows(), B.cols());
            C.mat = mat * B.mat;
            return C;
        }

        // Scalar multiplication
        SparseMatrix<T> operator*(T scalar) const {
            SparseMatrix<T> out(rows(), cols());
            out.mat = scalar * mat;
            return out;
        }

        SparseMatrix<T>& operator*=(T scalar) {
            mat *= scalar;
            return *this;
        }

        // Addition
        SparseMatrix<T> operator+(const SparseMatrix<T>& B) const {
            if (rows() != B.rows() || cols() != B.cols())
                throw std::invalid_argument("Dimension mismatch: A+B");

            SparseMatrix<T> out(rows(), cols());
            out.mat = mat + B.mat;
            return out;
        }

        // Subtraction
        SparseMatrix<T> operator-(const SparseMatrix<T>& B) const {
            if (rows() != B.rows() || cols() != B.cols())
                throw std::invalid_argument("Dimension mismatch: A-B");

            SparseMatrix<T> out(rows(), cols());
            out.mat = mat - B.mat;
            return out;
        }
    };

    // Scalar * matrix (nice convenience)
    template <typename T>
    SparseMatrix<T> operator*(T s, const SparseMatrix<T>& A) {
        return A * s;
    }

} // namespace LinearAlgebra

#endif // COME_LINALG_SPARSEMATRIX_HPP
