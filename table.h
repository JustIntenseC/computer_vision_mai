#pragma once
#include <iostream>
#include <vector>

class Table {
private:
    std::vector<std::vector<std::string>> table;
    int row;
    int col;
public:
    Table(int rows, int cols, std::vector<std::vector<std::string>> Table) : row(rows), col(cols), table(Table) {}

    std::string get(int row, int col);

    int getRow();

    int getCol();

    void setTable(std::vector<std::vector<std::string>> newTable);
};
