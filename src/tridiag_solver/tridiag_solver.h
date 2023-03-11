#ifndef SLAE_1_TRIDIAG_SOLVER_H
#define SLAE_1_TRIDIAG_SOLVER_H
#include <vector>
#include "../tridiag_matrix/tridiag_matrix.h"

template<typename T>

std::vector<T> solveSLAE(const TridiagonalMatrix<T> matrix, const std::vector<T> d){
    std::vector<T> p, q, x;
    x.resize(d.size());
    p.resize(d.size()-1);
    q.resize(d.size()-1);
    p[0] = -matrix(1) / matrix(0);
    q[0] = d[0] / matrix(0);
    for (int i = 0; i < d.size() - 2; i++)
    {
        p[i+1] = (-matrix(4 + 3 * i) / (matrix(2 + 3 * i) * p[i] + matrix(3 + 3 * i)));
        q[i+1] = ((d[i + 1] - matrix(2 + 3 * i) * q[i]) / (matrix(2 + 3 * i) * p[i] + matrix(3 + 3 * i)));
    }
    x[d.size() - 1] = (d[d.size() - 1] - matrix(matrix.size() - 2) * q[q.size() - 1])
                      / (matrix(matrix.size() - 2) * p[p.size() - 1] + matrix(matrix.size() - 1));
    for (int i = x.size()-2; i >= 0; i--)
    {
        x[i] = x[i + 1] * p[i] + q[i];
    }
    return x;
}

#endif //SLAE_1_TRIDIAG_SOLVER_H
