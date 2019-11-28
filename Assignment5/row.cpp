#include "row.h"

Row::Row(int n){
	if(n < 0)
		throw input_exeption();
	for(int i = 0; i < n; i++)
		element.push_back(DEFAULT_VALUE);
}

Row::Row(std::vector <double> _element){
	for(int i = 0; i < _element.size(); i++)
		element.push_back(_element[i]);
}

Row& Row::operator= (const Row& row){
	check_size_exeption(*this , row);
	for(int i = 0; i < element.size(); i++)
		element[i]=row.element[i];
	return *this;
}

Row& Row::operator= (const std::vector <double>& _element){
	check_size_exeption(*this , Row(_element));
	element = _element;
	return *this;
}

Row Row::operator+ (const Row& row) const{
	check_size_exeption(*this , row);
	std::vector <double> temp;
	for(int i = 0; i < element.size(); i++)
		temp.push_back(element[i] + row.element[i]);
	return Row(temp);
}

Row& Row::operator+= (const Row& row){
	*this = *this + row;
	return *this;
}

Row Row::operator- (const Row& row) const{
	return *this + (-1)*row;
}

Row& Row::operator-= (const Row& row){
	*this = *this - row;
	return *this;
}

Row Row::operator* (const Matrix& matrix){
	check_size_exeption(*this , matrix);
	std::vector<double> temp;
	double result;
	for(int j = 0; j < matrix.row[0].element.size(); j++){
		result = 0;
		for (int i = 0; i < element.size(); i++)
			result += element[i] * matrix.row[i].element[j];
		temp.push_back(result);
	}
	return Row(temp);
}

Row& Row::operator*= (const Matrix& matrix){
	check_size_exeption(*this , matrix.row[0]);
	*this = *this * matrix;
	return *this;
}

Row operator* (double factor, const Row& row){
	std::vector<double> temp;
	for (int i = 0; i < row.element.size(); i++)
		temp.push_back(factor * row.element[i]);
	return Row(temp);
}

double& Row::operator[] (int element_num){
	if(element_num < 0 || element_num >= size())
		throw input_exeption();
	return element[element_num];
}

double Row::operator[] (int element_num) const{
	if(element_num < 0 || element_num >= size())
		throw input_exeption();
	return element[element_num];
}

bool Row::operator== (const Row& row) const{
	check_size_exeption(*this , row);
	for(int i = 0; i < size(); i++)
		if(element[i] != row.element[i])
			return false;
	return true;
}

bool Row::operator!= (const Row& row) const{
	if(*this == row)
		return false;
	return true;
}

bool Row::operator== (const Matrix& matrix) const{
	check_size_exeption(*this , matrix.row[0]);
	for(int j = 0; j < matrix.row.size(); j++)
		for(int i = 0; i < element.size(); i++)
			if(element[i] != matrix.row[j].element[i])
				return false;
	return true;	
}

int Row::size() const{
	return element.size();
}

std::istream& operator>> (std::istream& in, Row& row){
	std::string line;
	getline(in, line);
	std::istringstream iss(line);
	std::vector<double> _element;
	double temp;
	while(iss >> temp)
		_element.push_back(temp);
	row.element =  _element;
	return in;
}

std::ostream& operator<< (std::ostream& out, const Row& row){
	for (int i = 0; i < row.size(); i++){
		out << floor((row.element[i] * pow(10.0, 3.0) + 0.5)) / pow(10.0, 3.0); //chap ba taghrib e 3 raghame ashar
		if(i != row.size() - 1)
			out << "\t";
	}
	return out;
}

void check_size_exeption(const Row& r1, const Row& r2){
	if(r1.size() != r2.size())
		throw size_exeption();
}

void check_size_exeption(const Row& r, const Matrix& m){
	if(r.size() != m.height())
		throw size_exeption();
}

void check_size_exeption(const Matrix& m1, const Matrix& m2){
	if(m1.width() != m2.width() || m1.height() != m2.height())
		throw size_exeption();
}

void check_size_exeption_p(const Matrix& m1, const Matrix& m2){
	if(m1.width() != m2.height())
		throw size_exeption();
}

void check_square_exeption(const Matrix& m){
	if(m.height() != m.width())
		throw input_exeption();
}

void check_equal_rows_exeption(const std::vector<Row>& r){
	int col_num = r[0].size();
	for (int i = 1; i < r.size(); ++i)
		if(col_num != r[i].size())
			throw input_exeption();
}