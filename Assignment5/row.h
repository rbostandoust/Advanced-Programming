#ifndef __ROW_H__
#define __ROW_H__

#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include "matrix.h"

#define DEFAULT_VALUE 0

class Matrix;
class size_exeption{};
class input_exeption{};

class Row
{
public:
	Row(int n);
	Row(std::vector<double> _element);

	Row& operator= (const Row& row);
	Row& operator= (const std::vector <double>& _element);
	Row operator+ (const Row& row) const;
	Row& operator+= (const Row& row);
	Row operator- (const Row& row) const;
	Row& operator-= (const Row& row);
	Row operator* (const Matrix& matrix);
	Row& operator*= (const Matrix& matrix);
	friend Row operator* (double factor, const Row& row);
	double& operator[] (int element_num);
	double operator[] (int element_num) const;
	bool operator== (const Row& row) const;
	bool operator!= (const Row& row) const;
	bool operator== (const Matrix& matrix) const;
	int size() const;

	friend std::istream& operator>> (std::istream& in, Row& row);
	friend std::ostream& operator<< (std::ostream& out, const Row& row);

	friend Matrix;
private:
	std::vector<double> element;
};

void check_size_exeption(const Row& r1, const Row& r2);
void check_size_exeption(const Row& r, const Matrix& m);
void check_size_exeption(const Matrix& m1, const Matrix& m2);
void check_size_exeption_p(const Matrix& m1, const Matrix& m2);
void check_square_exeption(const Matrix& m);
void check_equal_rows_exeption(const std::vector<Row>& r);

#endif