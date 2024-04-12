#include <table.h>

std::string Table::get(int row, int col) {
	return table[row][col];
}

int Table::getRow() {
	return row;
}

int Table::getCol() {
	return col;
}

void Table::setTable(std::vector<std::vector<std::string>> newTable) {
	table = newTable;
}
