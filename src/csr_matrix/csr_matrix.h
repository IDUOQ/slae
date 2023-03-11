#ifndef SLAE_1_CSR_MATRIX_H
#define SLAE_1_CSR_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>

template <typename T>

class CSRMatrix {
private:
    std::vector<T> nonzeroElements;
    std::vector<unsigned int> cols;
    std::vector<unsigned int> elementsBeforeRow = { 0 };
public:
    explicit CSRMatrix(const std::string& path) {
        std::ifstream file;
        file.exceptions(std::ifstream::badbit);
        try {
            file.open(path);
            T tmp; char symbol; unsigned int index = 0;
            while (!file.eof()) {
                file >> tmp;
                if (tmp != 0) {
                    nonzeroElements.push_back(tmp);
                    cols.push_back(index);
                }
                index++;
                symbol = file.get();
                if (symbol == '\n'|| symbol == '\r') {
                    elementsBeforeRow.push_back(nonzeroElements.size());
                    index = 0;
                }
                tmp = 0;
            }
            file.close();
        }
        catch (const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
        }

    }

    const T operator()(std::size_t i, std::size_t j) const {
        for (int k = elementsBeforeRow[i]; k < elementsBeforeRow[i+1]; k++)
        {
            if (cols[k] == j) {
                return nonzeroElements[k];
            }
        }
        return 0;
    }
    const std::vector<T> operator*(const std::vector<T>& d) const{
        std::vector<T> result;
        result.resize(elementsBeforeRow.size() - 1);
        std::fill(result.begin(), result.end(), 0);
        for (size_t i = 0; i < elementsBeforeRow.size()-1; i++)
        {
            for (size_t j = elementsBeforeRow[i]; j < elementsBeforeRow[i+1]; j++)
            {
                result[i] += d[cols[j]] * nonzeroElements[j];
            }
        }
        return result;
    }
};

#endif //SLAE_1_CSR_MATRIX_H
