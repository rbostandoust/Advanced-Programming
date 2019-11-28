#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdio.h>

using namespace std;

vector<double> getInputs();
void derivative(vector<double>& function,vector<double>& derivative);//moshtagh
void printFunction(vector<double> function);//for trsting
double rootFinder(vector<double>& function,vector<double>& derivative,double num, int counter);
double valueInFunc(vector<double> function,double num);
double power(double base,int power);

int main()
{
    while(true){
        vector<double> functionNums=getInputs();
        vector<double> detrivativeNums(functionNums.size()-1);
        //printFunction(functionNums);
        derivative(functionNums,detrivativeNums);
        double result;
        result=rootFinder(functionNums,detrivativeNums,0,1000);
        result=floor(result*100)/100;
        cout<<fixed<<setprecision(2)<<result<<endl;
    }
}
vector<double> getInputs(){
    string line ;
    while(true){
        getline(cin,line);
        if(line.length()==0)
            continue;
        else
            break;
    }
    vector<double> functionNums;
    stringstream ss(line);
    double temp;
    while (ss >> temp)
        functionNums.push_back(temp);
    return functionNums;
}
void derivative(vector<double>& function,vector<double>& derivative){
    for (int i=0; i< function.size(); i++)
        derivative[i]=(function.size()-i-1)*function[i];
}
void printFunction(vector<double> function){// for testing
    for (int i=0; i< function.size(); i++){
        cout << function[i]<<"x^"<<function.size()-i-1;
        if(i!=(function.size()-1))
            cout<<'+';
        else
            cout<<"=0"<<endl;
    }
}
double rootFinder(vector<double>& function,vector<double>& derivative,double num, int counter){
    if(valueInFunc(function,num)>-0.000001 && valueInFunc(function,num)<0.000001)
        return num;
    if(counter==0)
        return num;
    double valInFunc,valInDerivative,newNum;
    valInFunc=valueInFunc(function,num);
    valInDerivative=valueInFunc(derivative,num);
    if(valInDerivative==0)// if moshtagh==0
        return num;
    newNum=num-valInFunc/valInDerivative;
    return rootFinder(function,derivative,newNum,--counter);
}
double valueInFunc(vector<double> function,double num){
    double result=0;
    for (int i=0; i< function.size(); i++)
        result+=power(num,function.size()-i-1)*function[i];
    return result;
}
double power(double base,int power){
    double result=1;
    for (int i = 0; i < power; i++)
        result*=base;
    return result;
}
