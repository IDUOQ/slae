#ifndef SLAE_1_TRIDIAG_MATRIX_H
#define SLAE_1_TRIDIAG_MATRIX_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


template<typename T>

class TridiagonalMatrix {
private:
    std::vector<T> elements;

public:
    explicit TridiagonalMatrix(const std::string& path) {
        std::ifstream file;
        file.exceptions(std::ifstream::badbit);
        try {
            file.open(path);
            T tmp;
            while (!file.eof()) {
                file >> tmp;
                if (tmp != 0) {
                    this->elements.push_back(tmp);
                }
                tmp = 0;
            }
            file.close();
        }
        catch (const std::exception & ex)
        {
            std::cerr << ex.what() << std::endl;
        }

    }
    T operator()(std::size_t i) const{
        return elements[i];
    }
    [[nodiscard]] int size() const{
        return elements.size();
    }
};


#endif //SLAE_1_TRIDIAG_MATRIX_H
