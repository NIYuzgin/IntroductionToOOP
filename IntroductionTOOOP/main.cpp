
#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------------------\n"

class Point
{
	double x;
	double y;

public:
	double get_x() const {
		return x;
	}
	double get_y() const {
		return y;
	}
	void set_x(double x) {
		this->x = x;
	}
	void set_y(double y) {
		this->y = y;
	}

	// Constructors:

		/*
		Point() {
			x = y = 0;
			cout << "DefaultConstructor:\t" << this << endl;

		}

		Point(double x) {
			this->x = x;
			this->y = 0;
			cout << "SingleArgumentConstructor:\t" << this << endl;
			// конструктор с одним параметром
		}
		*/
	Point(double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}

	Point(const Point& other) {
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}

	~Point() {
		cout << "Destructor:\t\t" << this << endl;
	}

	// Operators:

	Point& operator = (const Point& other) {
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	
	
	// Methods:

	double distance(const Point& other) const {

		// this - эта точка (находим расстояние от этой точки)
		// other - та точка (до указанной точки)
		//other.x *= 100;
		//this->x *= 100;
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
		return distance;
	}
	void Print() const {
		cout << this << ": X = " << x << ",\tY = " << y << endl;
	}
};

double distance(const Point& A, const Point& B)  {

	//A.set_x(A.get_x() * 100);
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}

// #define STRUCT_POINT
//#define DISTANCE_CHECK
//#define CONSTRUCTORS_CHECK

void main() {
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	int a;	 //  объявление переменной 'a' типа 'int';
	Point A; // объявление переменной 'A' типа 'Point';
	// создание объекта 'A' структуры 'Point';
	// создание экземпляра 'A' структуры 'Point';
	// 'A' is instanse of struct 'Point'
	//Instantiate - создать объект
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);

	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B;
	B.set_x(7);
	B.set_y(8);

	cout << B.get_x() << "\t" << B.get_y() << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'A' до точки 'B': " << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'B' до точки 'A': " << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'A' и 'B': " << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'B' и 'A': " << distance(B, A) << endl;
	cout << delimiter << endl;
	cout << sizeof(Point) << endl;

#endif DISTANCE_CHECK

	/*
	for (int i = 0; i < 10; i++) {
		cout << i << "\t";
	}
	cout << endl;

	*/

#ifdef CONSTRUCTORS_CHECK


	Point A;
	A.Print();

	/*
	{
		Point B;
		cout << "Point B существует" << endl;
		B.distance(A);
	}
	cout << "Здесь Point B НЕ существует" << endl;
	*/

	Point B = 5; //Single-argument constructor - конструктор с одним параметром
	B.Print();

	Point C(7, 8); //Single-argument constructor - конструктор с одним параметром
	C.Print();

	Point D = C; //Copy constructor
	D.Print();

	Point E; //Default constructor
	E = D;	//Assignment constructor
	E.Print();





#endif CONSTRUCTORS_CHECK

	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	cout << delimiter << endl;
	A = B = C = Point(2, 3);
	//Point(2, 3) - здесь мы явно вызываем конструктор и создаем временный безымянный объект
	cout << delimiter << endl;
	A.Print();
	B.Print();
	C.Print();

}





