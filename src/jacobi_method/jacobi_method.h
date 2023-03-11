#ifndef SLAE_1_JACOBI_METHOD_H
#define SLAE_1_JACOBI_METHOD_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "dense_matrix.h"

template <typename T>

std::vector<T> JacobiMethod(const std::vector<T>& b, const denseMatrix<T>& A,
                            const T& tolerance, const std::vector<T> x_0) {
    const denseMatrix<T> L_U = A.getL() + A.getU();
    denseMatrix<T> D_1 = A - L_U;
    D_1 = D_1.getInversedDiag();
    std::vector<T> r;
    r.resize(x_0.size());
    for (size_t i = 0; i < r.size(); i++)
    {
        r[i] = b[i] - (A * x_0)[i];
    }
    sort(r.begin(), r.end(), [](int a, int b) { return abs(a) < abs(b); });
    std::vector<T> x;
    x.resize(x_0.size());
    for (size_t i = 0; i < r.size(); i++)
    {
        x[i] = (D_1*b)[i] - (D_1*(L_U * x_0))[i];
    }
    std::vector<T> tmp;
    tmp.resize(x_0.size());
    while (abs(r[r.size() - 1]) >= tolerance) {

        for (size_t i = 0; i < r.size(); i++)
        {
            tmp[i] = (D_1 * b)[i] - (D_1 * (L_U * x))[i];
        }
        for (size_t i = 0; i < r.size(); i++)
        {
            r[i] = b[i] - (A * x)[i];
        }
        sort(r.begin(), r.end(), [](int a, int b) { return abs(a) < abs(b); });
        x = tmp;
    }
    return x;
}

#endif //SLAE_1_JACOBI_METHOD_H
