#ifndef SLAE_1_DENSE_MATRIX_H
#define SLAE_1_DENSE_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

template <typename T>

class denseMatrix {
private:
    std::vector<T> elements;
    unsigned int cols;
    unsigned int rows;
public:
    explicit denseMatrix(const std::string& path) {
        std::ifstream file;
        file.exceptions(std::ifstream::badbit);
        try {
            file.open(path);
            T tmp; char symbol; unsigned int rows = 0;
            while (!file.eof()) {
                file >> tmp;
                symbol = file.get();
                if (symbol == '\n' || symbol == '\r') {
                    rows++;
                    elements.push_back(tmp);
                }
                else if (symbol == ' ') {
                    elements.push_back(tmp);
                }
            }
            this->rows = rows;
            cols = elements.size() / rows;
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
        }

    }

    [[nodiscard]] unsigned int getRows() const{
        return rows;
    }

    [[nodiscard]] unsigned int getCols() const {
        return cols;
    }

    [[nodiscard]] unsigned int getSize() const {
        return cols*rows;
    }

    T operator()(const std::size_t& i, const std::size_t& j) const{
        return elements[i*cols + j];
    }

    T& operator()(const std::size_t& i, const std::size_t& j){
        return elements[i * cols + j];
    }

    std::vector<T> operator*(const std::vector<T>& d) const {
        std::vector<T> result;
        result.resize(rows);
        std::fill(result.begin(), result.end(), 0);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                result[i] += d[j] * elements[cols*i+j];
            }
        }
        return result;
    }

    denseMatrix<T>& operator+=(const denseMatrix<T>& d){
        for (size_t i = 0; i < elements.size(); i++)
        {
            elements[i] += d.elements[i];
        }
        return *this;
    }

    denseMatrix<T> operator+(const denseMatrix<T>& d) const{
        denseMatrix<T> tmp = *this;
        return tmp += d;
    }

    denseMatrix<T>& operator-=(const denseMatrix<T>& d) {
        for (size_t i = 0; i < elements.size(); i++)
        {
            elements[i] -= d.elements[i];
        }
        return *this;
    }

    denseMatrix<T> operator-(const denseMatrix<T>& d) const{
        denseMatrix<T> tmp = *this;
        return tmp -= d;
    }

    denseMatrix<T> operator*(const T& number) const{
        denseMatrix<T> object = *this;
        for (size_t i = 0; i < object.elements.size(); i++)
        {
            object.elements[i] *= number;
        }
        return object;
    }

    bool operator==(const denseMatrix<T>& d) const{
        return elements == d.elements;
    }

    denseMatrix<T> getL() const{
        denseMatrix<T> L = *this;
        for (size_t i = 0; i < L.getRows(); i++)
        {
            for (size_t j = i; j < L.getCols(); j++)
            {
                L.elements[i*cols+j] = 0;
            }
        }
        return L;
    }

    denseMatrix<T> getU() const{
        denseMatrix<T> D = *this;
        for (size_t i = 0; i < D.getRows(); i++)
        {
            D.elements[i*cols+i] = 0;
        }
        return (D - getL());
    }

    denseMatrix<T> getD() const{
        return (*this - getL(*this) - getU(*this));
    }

    denseMatrix<T> getInversedDiag() const{

        denseMatrix<T> tmp = *this;
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = i; j < i+1; j++)
            {
                tmp.elements[i*cols + j] = 1 / tmp.elements[i * cols + j];
            }
        }
        return tmp;
    }
};


template <typename T>

std::ostream& operator<< (std::ostream& out, const denseMatrix<T>& obj){

    for (size_t i = 0; i < obj.getRows(); i++)
    {
        for (size_t j = 0; j < obj.getCols(); j++)
        {
            out << obj(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}

template <typename T, typename N>

denseMatrix<T> operator*(const N& number, const denseMatrix<T>& obj){
    return obj*number;
}

#endif //SLAE_1_DENSE_MATRIX_H
