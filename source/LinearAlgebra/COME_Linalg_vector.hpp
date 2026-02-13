#pragma once
#ifndef COME_LINALG_VECTOR_HPP
#define COME_LINALG_VECTOR_HPP

#include <armadillo>
#include <stdexcept>

namespace LinearAlgebra {

    template <typename T>
    class Vector {
    public:
        arma::Col<T> col;

        // Constructors
        Vector() = default;
        explicit Vector(size_t n) : col(n) {}
        Vector(const arma::Col<T>& data) : col(data) {}

        // Size
        size_t size() const { return col.n_rows; }

        // Element access
        T& operator()(size_t i) {
            if (!col.in_range(i)) {
                throw std::out_of_range("Vector index out of bounds");
            }
            return col(i);
        }

        T& operator()(size_t i) const {
            if (!col.in_range(i)) {
                throw std::out_of_range("Vector index out of bounds");
            }
            return col(i);
        }
        // Element access (get/set) for consistency with SparseMatrix
        T get(size_t i) const {
            if (!col.in_range(i)) {
                throw std::out_of_range("Vector index out of bounds");
            }
            return col(i);
        }

        void set(size_t i, T value) {
            if (!col.in_range(i)) {
                throw std::out_of_range("Vector index out of bounds");
            }
            col(i) = value;
        }

        // Norm
        T norm(int p) const {
            return arma::norm(col, p);
        }

        // Dot product
        T dot(const Vector<T>& other) const {
            return arma::dot(col, other.col);
        }

        // Arithmetic: return new vectors
        Vector<T> operator+(const Vector<T>& other) const {
            Vector<T> out(size());
            out.col = col + other.col;
            return out;
        }

        Vector<T> operator-(const Vector<T>& other) const {
            Vector<T> out(size());
            out.col = col - other.col;
            return out;
        }

        Vector<T> operator*(T scalar) const {
            Vector<T> out(size());
            out.col = col * scalar;
            return out;
        }

        // Compound operators (modify in-place)
        Vector<T>& operator+=(const Vector<T>& other) {
            col += other.col;
            return *this;
        }

        Vector<T>& operator-=(const Vector<T>& other) {
            col -= other.col;
            return *this;
        }

        Vector<T>& operator*=(T scalar) {
            col *= scalar;
            return *this;
        }
        Vector<T> removeRow(unsigned int index)
        {
            this->col.shed_row(index);
            return *this;

        }
    };

    // Scalar * vector (optional convenience)
    template <typename T>
    Vector<T> operator*(T scalar, const Vector<T>& v) {
        return v * scalar;
    }

} // namespace LinearAlgebra

#endif // COME_LINALG_VECTOR_HPP
