#include "matrix.h"

Matrix::Matrix(){}

Matrix::Matrix (int r, int c){
	std::vector<double> temp(c,0);
	for (int i = 0; i < r; i++)
		row.push_back(temp);
}

Matrix::Matrix(std::vector<Row> _row){
	check_equal_rows_exeption(_row);
	for (int i = 0; i < _row.size(); ++i)
	{
		row.push_back(_row[i]);
	}
}

Matrix::Matrix(double value){
	std::vector<double> temp(1,value);
	row.push_back(temp);
}

Matrix& Matrix::operator= (const Matrix& matrix){
	row.clear();
	for (int i = 0; i < matrix.height(); i++)
			row.push_back(matrix[i]);
	return *this;
}

Matrix& Matrix::operator= (std::vector<Row> _row){
	check_equal_rows_exeption(_row);
	row.clear();
	for (int i = 0; i < _row.size(); i++)
		row.push_back(_row[i]);
}

Matrix& Matrix::operator= (const Row& _row){
	row.clear();
	row.push_back(_row);
}

Matrix& Matrix::operator= (double value){
	row.clear();
	std::vector<double> temp(1,value);
	row.push_back(temp);	
}

Matrix Matrix::operator+ (const Matrix& matrix) const{
	check_size_exeption(*this , matrix);
	std::vector<Row> temp_row;
	std::vector<double> temp;
	for (int i = 0; i < row.size(); i++)
	{
		temp.clear();
		for (int j = 0; j < row[i].element.size(); j++)
			temp.push_back(row[i].element[j] + matrix.row[i].element[j]);
		temp_row.push_back(temp);
	}
	return Matrix(temp_row);
}

Matrix& Matrix::operator+= (const Matrix& matrix){
	*this = *this + matrix;
	return *this;
}

Matrix Matrix::operator- (const Matrix& matrix) const{
	return *this + (-1) * matrix;
}

Matrix& Matrix::operator-= (const Matrix& matrix){
	*this = *this - matrix;
	return *this;
}

Matrix Matrix::operator* (const Matrix& matrix) const{
	check_size_exeption_p(*this , matrix);
	std::vector<Row> temp_row;
	std::vector<double> temp;
	double result;
	for (int result_row = 0; result_row < row.size(); result_row++)
	{
		temp.clear();
		for (int result_col = 0; result_col < matrix.row[0].element.size(); result_col++){
			result = 0;
			for (int i = 0; i < row[0].element.size(); i++)
				result += row[result_row].element[i] * matrix.row[i].element[result_col] ;
			temp.push_back(result);
		}	
		temp_row.push_back(temp);
	}
	return Matrix(temp_row);
}

Matrix& Matrix::operator*= (const Matrix& matrix){
	*this = *this * matrix;
	return *this;
}

Matrix operator* (double factor, const Matrix& matrix){
	std::vector<Row> temp;
	for (int i = 0; i < matrix.height(); i++)
		temp.push_back(factor * matrix.row[i]);
	return Matrix(temp);
}

Matrix Matrix::operator/ (const Matrix& matrix) const{
	Matrix inverse_matrix = matrix.inverse();
	return *this * inverse_matrix;
}

Matrix Matrix::operator^ (int power) const{
	Matrix temp = *this;
	if(power == 0)
		temp = make_I_matrix();
	if(power < 0){
		temp = inverse();
		power *= -1;
	}
	Matrix result(temp);
	for(int i = 1; i < power; i++)
		result *= temp;
	return result;
}

Matrix Matrix::operator-(){
	return -(1) * (*this);
}

Row& Matrix::operator[] (int row_number){
	if(row_number < 0 || row_number >= height())
		throw input_exeption();
	return row[row_number];
}

Row Matrix::operator[] (int row_number) const{
	if(row_number < 0 || row_number >= height())
		throw input_exeption();
	return row[row_number];
}

bool Matrix::operator== (const Matrix& matrix){
	if(height() != matrix.height() || width() != matrix.width())
		return false;
	for(int i = 0; i < height(); i++)
		if(row[i] != matrix.row[i])
			return false;
	return true;
}

bool Matrix::operator== (const Row& _row){
	if(_row == (*this))
		return true;
	return false;
}

int Matrix::height() const{
	return row.size();
}

int Matrix::width() const{
	return row[0].size();
}

double Matrix::determinant(){
	check_square_exeption(*this);
	if(height() == 2)
		return (row[0].element[0] * row[1].element[1]) - (row[1].element[0] * row[0].element[1]);
	double determinant_amount = 0;
	for(int i = 0; i < height(); i++){
		Matrix smaller_matrix = make_smaller_matrix(i);
		determinant_amount += row[0].element[i] * pow(-1 , i) * smaller_matrix.determinant();  
	}
	return determinant_amount;
}	

void Matrix::insert(const Row& _row, int row_number){
	if(row_number < 0 || row_number > height())
		throw input_exeption();
	std::vector<Row> temp_row;
	for(int i = 0; i < height(); i++){
		if(i == row_number)
			temp_row.push_back(_row);
		temp_row.push_back(row[i]);
	}
	if(row_number == height())
		temp_row.push_back(_row);
	row.clear();
	for (int i = 0; i < temp_row.size(); i++)
			row.push_back(temp_row[i]);
}

Matrix Matrix::make_smaller_matrix(int col_number){
	std::vector<Row> temp_matrix;
	std::vector<double> temp_row;
	for (int result_row = 1; result_row < height(); result_row++)
	{
		temp_row.clear();
		for (int result_col = 0; result_col < width(); result_col++){
			if(result_col != col_number)
				temp_row.push_back(row[result_row].element[result_col]);
		}	
		temp_matrix.push_back(temp_row);
	}
	Matrix temp(temp_matrix);
	return temp;
}

Matrix Matrix::make_I_matrix() const{
	check_square_exeption(*this);
	std::vector<Row> temp_matrix;
	std::vector<double> temp_row;
	for (int row = 0; row < height(); row++)
	{
		temp_row.clear();
		for (int col = 0; col < width(); col++){
			temp_row.push_back(col == row ? 1 : 0); 	
		}	
		temp_matrix.push_back(temp_row);
	}
	return Matrix(temp_matrix);
}

Matrix Matrix::inverse() const{
	Matrix base = *this;
	if(base.determinant() == 0)
		throw input_exeption();
	Matrix inverse_matrix = make_I_matrix();
	for(int matrix_row = 0; matrix_row < base.height(); matrix_row++){
		while(base.row[matrix_row][matrix_row] == 0)
			base.shift_matrix(matrix_row);
		double make_1 = 1.0 / base.row[matrix_row][matrix_row]; 
		base.row[matrix_row] = make_1 * base.row[matrix_row];
		inverse_matrix.row[matrix_row] = make_1 * inverse_matrix.row[matrix_row];
		for(int explore_row = 0; explore_row < base.height(); explore_row++){
			if(explore_row == matrix_row)
				continue;
			double factor = base.row[explore_row][matrix_row];
			base.row[explore_row] -= factor * base.row[matrix_row];
			inverse_matrix.row[explore_row] -= factor * inverse_matrix.row[matrix_row];
		}
	}
	return inverse_matrix;
}

Matrix Matrix::shift_matrix(int col){
	std::vector<Row> temp_matrix;
	for (int i = 1; i < height(); ++i)
		temp_matrix.push_back(row[i]);
	temp_matrix.push_back(row[0]);
	*this = Matrix(temp_matrix);
}


std::ostream& operator<< (std::ostream& out, const Matrix& matrix){
	out << "[\n";
	for (int i = 0; i < matrix.height(); i++)
	{
		out << matrix.row[i] << "\n";
	}
	out << "]";
	return out;
}

std::istream& operator>> (std::istream& in, Matrix& matrix){

}