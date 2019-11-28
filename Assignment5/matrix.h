#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "row.h"
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>

class Row;

class Matrix
{
public:
	Matrix();
	Matrix(int r, int c);
	Matrix(std::vector<Row> _row);
	Matrix(double value);
	Matrix& operator= (const Matrix& matrix); 
	Matrix& operator= (std::vector<Row> _row);
	Matrix& operator= (const Row& _row);
	Matrix& operator= (double value);
	Matrix operator+ (const Matrix& matrix) const;
	Matrix& operator+= (const Matrix& matrix);
	Matrix operator- (const Matrix& matrix) const;
	Matrix& operator-= (const Matrix& matrix);
	Matrix operator* (const Matrix& matrix) const;
	Matrix& operator*= (const Matrix& matrix);
	friend Matrix operator* (double factor, const Matrix& matrix);
	Matrix operator/ (const Matrix& matrix) const;
	Matrix operator^ (int power) const;
	Matrix operator-();
	Row& operator[] (int row_number);
	Row operator[] (int row_number) const;
	bool operator== (const Matrix& matrix);
	bool operator== (const Row& _row);
	
	int height() const;
	int width() const;
	double determinant() ;
	void insert(const Row& _row, int row_number);
	Matrix make_smaller_matrix(int col_number);
	Matrix make_I_matrix() const;
	Matrix inverse() const;
	Matrix shift_matrix(int col);

	friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);
	friend std::istream& operator>> (std::istream& in, Matrix& matrix); 

	friend Row;
private:
	std::vector<Row> row;	
};

#endif