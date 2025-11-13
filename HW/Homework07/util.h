#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

namespace dshw
{
    bool isSpace(char c)
    {
        return c == ' ' || c == '\n' || c == '\t';
    }

    std::string getRomanNumeral(unsigned int length=5)
    {
        static bool seeded = false;
        if (!seeded)
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            seeded = true;
        }
        std::string romans = "IVXLCDM";
        if (length == 0 || length > 7)
        {
            length = 5;
        }
        std::string result;
        for (unsigned int i = 0; i < length; ++i)
        {
            result += romans[rand() % romans.size()];
        }
        return result;
    }
    void printVector(const std::vector<int>& vec)
    {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i];
            if (i < vec.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
    double decimalPlaces(double num, int places)
    {
        int factor = 1;
        for (int i = 0; i < places; ++i)
        {
            factor *= 10;
        }
        num *= factor;
        num = static_cast<int>(num);
        num /= factor;
        return num;
    }
}

void drawGrid(unsigned int m, unsigned int n)
{
    std::vector<std::vector<int>> grid(m, std::vector<int>(n, 1));

    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
        }
    }

    int maxNum = 0;

    for (const auto& row : grid)
    {
        for (const auto& num : row)
        {
            if (num > maxNum)
            {
                maxNum = num;
            }
        }
    }

    int cellWidth = std::to_string(maxNum).size() + 2;

    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            std::cout << "+" << std::string(cellWidth, '-');
        }

        std::cout << "+" << std::endl;
    
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            std::cout << "|" << std::setw(cellWidth - 1) << grid[i][j] << " ";
        }

        std::cout << "|" << std::endl;
    }

    for (size_t j = 0; j < grid[0].size(); ++j)
    {
        std::cout << "+" << std::string(cellWidth, '-');
    }

    std::cout << "+" << std::endl;
}
#endif