#ifndef SLAE_1_GAUSS_SEIDEL_METHOD_H
#define SLAE_1_GAUSS_SEIDEL_METHOD_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "dense_matrix.h"

template<typename T>

std::vector<T> Gauss_SeidelMethod(const std::vector<T>& b, const denseMatrix<T>& A,
                                  const T& tolerance, const std::vector<T>& x_0) {
    std::vector<T> r;
    r.resize(x_0.size());
    for (size_t i = 0; i < r.size(); i++)
    {
        r[i] = b[i] - (A * x_0)[i];
    }
    sort(r.begin(), r.end(), [](int a, int b) { return abs(a) < abs(b); });
    std::vector<T> x = x_0;
    std::vector<T> tmp;
    tmp.resize(x_0.size());
    while (abs(r[r.size() - 1]) >= tolerance) {
        for (size_t k = 0; k < x_0.size(); k++)
        {
            T sum = b[k];
            for (size_t j = 0; j < k; j++)
            {
                sum -= A(k, j) * tmp[j];
            }
            for (size_t j = k+1; j < x_0.size(); j++)
            {
                sum -= A(k, j) * x[j];
            }
            tmp[k] = sum / A(k, k);
        }
        x = tmp;
        for (size_t i = 0; i < r.size(); i++)
        {
            r[i] = b[i] - (A * x)[i];
        }
        sort(r.begin(), r.end(), [](int a, int b) { return abs(a) < abs(b); });
    }
    return x;
}

#endif //SLAE_1_GAUSS_SEIDEL_METHOD_H
