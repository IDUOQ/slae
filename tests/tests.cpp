#include <gtest/gtest.h>
#include <vector>
#include "tridiag_solver.h"
#include "tridiag_matrix.h"
#include "dense_matrix.h"
#include "csr_matrix.h"
#include "jacobi_method.h"
#include "simple_iteration_method.h"
#include "gauss_seidel_method.h"


TEST(TridiagonalMatrixTest, ReadingMatrix) {

    const std::vector<int> elements = {9, 1, 2, 6, 1, 2, 9, 1, 1, 8};
    const TridiagonalMatrix<int> matrix("matrix1.txt");
    for (unsigned int i = 0; i < elements.size(); ++i) {
        EXPECT_EQ(elements[i], matrix(i));
    }
}


TEST(TridiagonalMatrixTest, MatrixSize) {
    const int realSize = 7;
    const TridiagonalMatrix<double> matrix("matrix2.txt");
    EXPECT_EQ(realSize, matrix.size());
}

TEST(TridiagonalSolverTest, SimpleSLAE) {
    const std::vector<double> d = {10, 9, 12, 9};
    const std::vector<double> answer = {1, 1, 1, 1};
    const TridiagonalMatrix<double> matrix("matrix1.txt");
    EXPECT_EQ(answer, solveSLAE(matrix, d));
}


TEST(CSRMatrixTest, ChoosingElements) {
    const std::vector<double> elements = {0, 1, 2};
    const CSRMatrix<double> matrix("matrix3.txt");

    for(int i = 0; i < elements.size(); i++){
        EXPECT_EQ(elements[i], matrix(i,i));
    }
}

TEST(CSRMatrixTest, MultiplyOnVector) {
    const std::vector<double> elements = {0, 1, 2};
    const std::vector<double> expected = {0, 1, 4};
    const CSRMatrix<double> matrix("matrix3.txt");

    for(int i = 0; i < expected.size(); i++){
        EXPECT_EQ(expected[i], (matrix*elements)[i]);
    }
}

TEST(CSRMatrixTest, Scalar) {
    const int number = 9;
    const CSRMatrix<double> matrix("matrix4.txt");
    EXPECT_EQ(number, matrix(0,0));
}

TEST(DenseMatrix, ChoosingElements) {
    denseMatrix<double> matrix("matrix3.txt");
    matrix(0,0) = 9;
    matrix(0,0) = matrix(0,0) * matrix(0,0);
    EXPECT_EQ(81, matrix(0,0));
}

TEST(DenseMatrix, MultiplyOnVector) {
    const std::vector<double> elements = {0, 1, 2};
    const std::vector<double> expected = {0, 1, 4};
    const denseMatrix<double> matrix("matrix3.txt");

    for(int i = 0; i < expected.size(); i++){
        EXPECT_EQ(expected[i], (matrix*elements)[i]);
    }
}

TEST(DenseMatrix, Arithmetic) {
    denseMatrix<double> matrix("matrix3.txt");
    EXPECT_EQ(2 * matrix, matrix * 2 + matrix - matrix);
}
