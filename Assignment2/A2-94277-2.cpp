#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point{
	double x;
	double y;
};

void getPoints(vector<Point>& points);
void sortPointsByX(vector<Point>& points);
void swap(Point& first,Point& second);
void printPoints(vector<Point>& points);
vector<Point> convexHull(int n,vector<Point>& points);
double exteriorProduct(Point a,Point b, Point c);//zarbe khareji
void changePoints(vector<Point>& points);
void calculatePerimeter(vector<Point>& points);
void reversePoints(vector<Point>& points);
double sumOfLenghts(vector<Point>& points);
double lenght(Point a,Point b);
bool isSame(vector<Point>& a,vector<Point>& b);//checks if 2 vectors are same or not

int main(){
	vector<Point> points;
	getPoints(points);
	sortPointsByX(points);
	calculatePerimeter(points);
}

void getPoints(vector<Point>& points){
	int numOfPoints;
	Point temp;
	cin>>numOfPoints;
	for(int i=0;i<numOfPoints;i++){
		cin>> temp.x >> temp.y;
		points.push_back(temp);
	}
}
void sortPointsByX(vector<Point>& points){//bublle sort on x of points
	Point temp;
	for(int i=0;i<points.size();i++)
		for(int j=0;j<points.size()-i-1;j++)
			if(points[j].x > points[j+1].x)
				swap(points[j] , points[j+1]);
}
void swap(Point& first,Point& second){
	Point temp;
	temp.x=first.x;
	temp.y=first.y;
	first.x=second.x;
	first.y=second.y;
	second.x=temp.x;
	second.y=temp.y;
}
void printPoints(vector<Point>& points){// this func is for testing
	for(int i=0;i<points.size();i++)
		cout <<"x: " << points[i].x<<" ,y: " << points[i].y << endl;
}
vector<Point> convexHull(int n,vector<Point>& points){
	if(n==2){
		vector<Point> begin;
		begin.push_back(points[0]);
		begin.push_back(points[1]);
		return begin;
	}
	vector<Point> v=convexHull(n-1,points);
	v.push_back(points[n-1]);
	//cout<<"lvl "<<n<<" before:"<<endl;
	//printPoints(v);
	while(v.size()>2 && exteriorProduct(v[v.size()-3], v[v.size()-2], v[v.size()-1])>0)
		changePoints(v);
	//cout<<"lvl "<<n<<" after:"<<endl;
	//printPoints(v);
	return v;
}
double exteriorProduct(Point a,Point b, Point c){
	double x1=b.x-a.x;
	double y1=b.y-a.y;
	double x2=c.x-b.x;
	double y2=c.y-b.y;
	return (x1*y2 - x2*y1);
}
void changePoints(vector<Point>& points){// this funcs delete one remain to last point
	Point temp;
	temp.x=points[points.size()-1].x;
	temp.y=points[points.size()-1].y;
	points.pop_back();
	points.pop_back();
	points.push_back(temp);
}
void calculatePerimeter(vector<Point>& points){
	vector<Point> upperLines=convexHull(points.size(),points);
	cout<<"Upper:"<<endl;
	printPoints(upperLines);
	reversePoints(points);
	vector<Point> lowerLines=convexHull(points.size(),points);
	cout<<"lower:"<<endl;
	printPoints(lowerLines);
	double perimeter=0;
	perimeter=sumOfLenghts(upperLines);
	perimeter+=sumOfLenghts(lowerLines);
	if(isSame(upperLines,lowerLines))// if we had a line, divide the perimeter by 2
		perimeter/=2;
	perimeter=floor(perimeter*100)/100;
	cout<<fixed<<setprecision(2)<<perimeter<<endl;
}
void reversePoints(vector<Point>& points){
	for (int i = 0; i < points.size()/2; ++i)
	{
		swap(points[i],points[points.size()-1-i]);
	}
}
double sumOfLenghts(vector<Point>& points){
	double result=0;
	for (int i = 0; i < points.size()-1; ++i)
		result+=lenght(points[i],points[i+1]);
	return result;
}
double lenght(Point a,Point b){
	return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}
bool isSame(vector<Point>& a,vector<Point>& b){
	if(a.size()!=b.size())
		return false;
	for(int i=0;i<a.size();i++){
		if(a[i].x!=b[b.size()-1-i].x||a[i].y!=b[b.size()-1-i].y)
			return false;
	}
	return true;
}