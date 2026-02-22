/*
  _____   ____   __  __  ______
 / ____| / __ \ |  \/  ||  ____|
| |     | |  | || \  / || |__
| |     | |  | || |\/| ||  __|
| |____ | |__| || |  | || |____
 \_____| \____/ |_|  |_||______|
*/
#include "LinearAlgebra/COME_Linalg_sparse.hpp"
#include "LinearAlgebra/COME_Linalg_vector.hpp"
#include "LinearSolvers/COME_LinearIterativeSolvers.hpp"
#include "LinearAlgebra/COME_Linalg_dense.hpp"
#include "Grid/COME_Mesh.hpp"
#include "FEM/Quadrature/COME_Quadrature_QGauss.hpp"
#include <iostream>
#include <istream>
#include <fstream>
#include <filesystem>

int main() {
    using namespace LinearAlgebra;

    // Create a 5x5 sparse matrix (all zeros for now)
    SparseMatrix<double> A(5, 5);

    // Create b = [1,1,1,1,1]^T
    Vector<double> b(5);
    for (size_t i = 0; i < 5; ++i) {
        b(i) = 1.0;
    }

    // Initial guess x = [0,0,0,0,0]^T
    Vector<double> x(5);   // initialized to zeros by Armadillo

    // Compute residual r = b - A*x
    Vector<double> r = b - (A * x);

    // Print residual
    std::cout << "Residual r = b - A*x:" << std::endl;
    for (size_t i = 0; i < r.size(); ++i) {
        std::cout << r(i) << std::endl;
    }

    // Frobenius norm of A
    std::cout << "Frobenius norm of A: " << A.norm() << std::endl;

    // Scalar multiplication test
    SparseMatrix<double> B = A * 2.0;
    std::cout << "B(0,0) after scaling: " << B(0, 0) << std::endl;
    B.set(1, 2, 1.0);

    SparseMatrix<double> C = B.diagonalMatrix();
    std::cout << "C(1,2):" << C(1, 2) << std::endl;
    std::cout << "B(1,2):" << B(1, 2) << std::endl;

    B(1, 2) = 0.0;

    std::cout << "B(1,2):" << B(1, 2) << std::endl;
    B(1, 2) = 1.0;
    B.eliminateRowAndColumn(1);
    std::cout << "B(1,2):" << B(1, 2) << std::endl;
    b.removeRow(1);
    std::cout << "b size" << b.size() << std::endl;
    x.removeRow(1);
    B(0, 0) = 2.0;
    B(1, 1) = 2.0;
    B(2, 2) = 2.0;
    B(3,3) = 2.0;
    B(0, 1) = -1.0;
    B(1, 0) = -1.0;
    B(1, 2) = -1.0;
    B(2, 1) = -1.0;
    B(2, 3) = -1.0;
    B(3, 2) = -1.0;
    std::cout << "rows and cols" << B.rows() << B.cols() << std::endl;
    std::cout << "works until here" << std::endl;
    std::cout << "b1" << b(1) << std::endl;
    std::cout << "B(1,1)" << B(1, 1) << std::endl;

    FullMatrix<double> F(2, 2);
    F(0, 0) = 2.0;
    F(1, 1) = 2.0;
    F(0, 1) = -1.0;
    F.inverse2x2();
    std::cout << "F(1,1)" << F(0, 1) << std::endl;


    LinearSolvers::LinearIterativeSolvers<double> solver1;

    LinearAlgebra::Vector<double>result = solver1.JacobiSolve(B, b, x);

    
    std::cout << "result vector" << result(0) << result(1) << result(2) << result(3) << std::endl;
    std::cout << "result vector" << x(0) << x(1) << x(2) << x(3) << std::endl;


    Mesh::Mesh<3> mesh;
    std::ifstream input_file("../../../Meshes/Abaqus3DHexaUniformBeam.inp");

    mesh.read_abaqus(input_file);

    Quadrature::QGauss<1> quad(2);
    std::cout << "gauss order" << quad.getQuadratureOrder() << std::endl;




    return 0;
}
