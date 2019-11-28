#include <iostream>
#include <vector>
#include <string>
#include "matrix.h"
#include "row.h"
using namespace std;

int main() {
	cout<<"\nconstructor and assignment(=) of Row\n";
	//constructor and assignment(=) of Row
	Row r1(5);
	r1[0]=r1[4]=2;
	vector<double> d_row(5,2);
	Row r2(d_row);
	cout<<"r1:\t\t"<<r1<<endl;
	cout<<"r2:\t\t"<<r2<<endl;
	r2 = r1;
	r2 = d_row;
	Row r3(0);
	cin >> r3;
	cout<< "r3:\t\t"<<r3<<endl;

	cout<<"\n+ & - & * of Row\n";

	//+ & - & * of Row
	r3 += r1 + r2;
	cout<< "r3+r2+r1:\t"<<r3<<endl;
	cout<< "r2+r1:\t\t"<<r2 + r1<<endl;
	r3 -= r1 + r2;
	cout<< "r3-r2-r1:\t"<<r3<<endl;
	cout<< "r2-r1:\t\t"<<r2 - r1<<endl;
	cout<< "r3 * 5:\t\t"<<(r3 = 5 * r3)<<endl;
	Row r4(0);
	cin>>r4;

	if(r3 == r4)
		cout<<"r3 = r4\n";
	else
		cout<<"r3 != r4\n";
	cout<< "r1.size:"<<r1.size()<<endl;

	cout<<"\nmatrix constructor\n";

	//matrix constructor
	Matrix m1;
	Matrix m2(5,2);
	cout<<"m1:\n"<<m1<<endl;
	cout<<"m2:\n"<<m2<<endl;

	std::vector<Row> rows;
	rows.push_back(r1);
	rows.push_back(r2);
	rows.push_back(r3);
	rows.push_back(r4);
	Matrix m3(rows);
	cout<<"m3:\n"<<m3<<endl;
	
	cout<<"* - + and assignment(=) and insert of matrix\n";

	//* - + and assignment(=) and insert of matrix
	r3 = 1.0/5 * r3;
	rows.push_back(r3);
	m3.insert(r3,m3.height());
	cout<<"new m3:\n"<<m3<<endl;

	cout<< "r3*m2:\t"<< r3 * m2<<endl;
	r3 *= m3;
	cout<< "r3:\t"<< r3<<endl;
	cin >> r1;
	cout << r1 <<endl;
	m1 = m2;
	cout<<"m1:\n"<<m1<<endl;
	m1 = rows;
	cout<<"m1:\n"<<m1<<endl;
	m1 = 5.2;
	cout<<"m1:\n"<<m1<<endl;
	cout<<"2*m3:\n"<<2.0*m3<<endl;
	cout<<"m3+m3:\n"<<m3+m3<<endl;
	cout<<"-(m3):\n"<<-(m3)<<endl;
	cout<<"2*m3-m3:\n"<<2*m3-m3<<endl;

	m1 = 2*m3;
	m1 -= m3;
	cout<<"m1:\n"<<m1<<endl;
	m1 += m3;
	cout<<"m1:\n"<<m1<<endl;
	if(m1-m3 == m3)
		cout <<"m1 = m3\n";
	else
		cout <<"m1 != m3\n";
	cout<<"m1*m3:\n"<<m1*m3<<endl;

	for (int i = 0; i < m3.height(); ++i)
		cout<<"row:"<<i<<"\t"<<m3[i]<<endl;

	cout<<"\ndeterminant\n";

	//determinant
	Matrix m4(4,4);
	m4[0][0] = 3; m4[0][1] = 2; m4[0][2] = -1; m4[0][3] = 4;
	m4[1][0] = 2; m4[1][1] = 1; m4[1][2] = 5; m4[1][3] = 7;
	m4[2][0] = 0; m4[2][1] = 5; m4[2][2] = 2; m4[2][3] = -6;
	m4[3][0] = -1; m4[3][1] = 2; m4[3][2] = 1; m4[3][3] = 0;
	cout <<"m4:" <<m4<<endl;
	cout<<"determinant(m4):"<<m4.determinant()<<endl; // determinant = -418

	cout<<"\ninverse"<<endl;

	//inverse
	Matrix m5 = m4.inverse();
	cout <<"inverse(m4):" <<m5<<endl;
	cout <<"inverse(m4) * m4:"<< (m5*m4)<<endl;
	cout<<"m4/m4:\n"<<m4/m4<<endl;

	cout<<"\ninverse"<<endl;

	//power
	cout<<"m4^(0):\n"<< (m4^0)<<endl;
	cout<<"m4^(2):\n"<< (m4^2)<<endl;
	cout<<"m4^(-2):\n"<< (m4^(-2)) <<endl;
}
