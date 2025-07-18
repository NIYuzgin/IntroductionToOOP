﻿#include <iostream>

using namespace std;

class Fraction; // объявление класса
Fraction operator* (Fraction left, Fraction right); // объявление оператора
Fraction operator/ (const Fraction& left, const Fraction& right);


class Fraction // описание класса
{
	int integer; //целая часть
	int numerator; //числитель
	int denominator; //знаменатель

public:
	int get_integer()const {
		return integer;
	}
	int get_numerator()const {
		return numerator;
	}
	int get_denominator()const {
		return denominator;
	}

	void set_integer(int integer) {
		this->integer = integer;
	}
	void set_numerator(int numerator) {
		this->numerator = numerator;
	}
	void set_denominator(int denominator) {
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}

	// Constructors:

	Fraction() {
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}

	explicit Fraction(int integer) {
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:\t" << this << endl;
	}

	Fraction(double decimal) // decimal - десятичная дробь
	{
		decimal += 1e-10;
		integer = decimal;		//получаем целую часть дроби
		decimal -= integer;		//убираем целую часть из десятичной дроби
		denominator = 1e+9;		//получаем максимально возможный знаменатель 1000000000;
		numerator = decimal * denominator; // вытаскиваем дробную часть в числитель
		reduce();
		cout << "SingleArgumentConstructor:\t" << this << endl;
	}

	Fraction(int numerator, int denominator) {
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(int integer, int numerator, int denominator) {
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(const Fraction& other) {
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t\t" << this << endl;
	}

	~Fraction() {
		cout << "Destructor:\t\t" << this << endl;
	}

	// Operators:

	Fraction& operator= (const Fraction& other) {
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*= (const Fraction& other) {
		return *this = *this * other;
	}
	Fraction& operator/= (const Fraction& other) {
		return *this = *this / other;
	}
	Fraction& operator+= (const Fraction& other) {
		return *this = *this + other;
	}
	Fraction& operator-= (const Fraction& other) {
		return *this = *this - other;
	}

	// Incremento/Decremento:

	Fraction& operator++ () // префиксный инкремент
	{
		integer++;
		return *this;
	}
	Fraction operator++ (int) // постфиксный инкремент
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	Fraction& operator-- () // префиксный инкремент
	{
		integer--;
		return *this;
	}
	Fraction operator-- (int) // постфиксный инкремент
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	// Type-cast operators:

	explicit operator int()const {
		// to_improper(); // evalueate as a constant
		return integer + numerator / denominator;
	}
	
	operator double()const {
		return integer + (double)numerator / denominator;

	}

	// Methods:

	Fraction& to_improper() //перевод в неправильную дробь
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper() //перевод в правильную дробь
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction inverted() const {
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator); // функция swap() меняет местами две переменные
		return inverted;
	}
	Fraction& reduce() {
		int more, less, rest;
		if (numerator > denominator) more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do {
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}


	void print()const {
		if (integer) cout << integer;
		if (numerator) {
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};


Fraction operator+ (Fraction left, Fraction right) {
	left.to_improper();
	right.to_improper();
	return Fraction
	(left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator- (Fraction left, Fraction right) {
	left.to_improper();
	right.to_improper();
	return Fraction
	(left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator* (Fraction left, Fraction right) {
	left.to_improper();
	right.to_improper();

	return Fraction
	(left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();


}
Fraction operator/ (const Fraction& left, const Fraction& right) {
	return left * right.inverted();
}


// Comparison operators:

bool operator == (Fraction left, Fraction right) {
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator();
}

bool operator != (const Fraction& left, const Fraction& right) {
	return !(left == right);
}

bool operator > (Fraction left, Fraction right) {
	left.to_improper();
	right.to_improper();

	return left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}

bool operator < (Fraction left, Fraction right) {
	left.to_improper();
	right.to_improper();

	return left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}

bool operator >= (const Fraction& left, const Fraction& right) {
	return !(left < right);
	//return left > right || left == right;
}

bool operator <= (const Fraction& left, const Fraction& right) {
	return !(left > right);
	//return left < right || left == right;
}


std::ostream& operator << (std::ostream& os, const Fraction& obj) // Stream extraction operator
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator()) {
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0) os << 0;
	return os;
}

std::istream& operator >> (std::istream& is, Fraction& obj) {
	
	/*
	----------------------------------------
	5;
	1/2;
	2(3/4);
	2 3/4;
	2,3/4;
	------------------------------------------
	*/
	
	const int SIZE = 256;  // размер буфера ввода
	char buffer[SIZE] = {}; // буфер ввода
	//is >> buffer;
	is.getline(buffer, SIZE);
	const char delimiters[] = "(/, )";
	int n = 0; // количество введенных чисел
	int numbers[3] = {}; // числа, введенные с клавиатуры
	for (char* pch = strtok(buffer, delimiters); pch && n < 3; pch = strtok(NULL, delimiters))
		numbers[n++] = atoi(pch);	//atoi() - ASCI-string to Integer
	//for (int i = 0; i < n; i++) cout << numbers[i] << "\t"; cout << endl;
	switch (n) {
	case 0: obj = Fraction(); break;
	case 1: obj = Fraction(numbers[0]); break;
	case 2: obj = Fraction(numbers[0], numbers[1]); break;
	case 3: obj = Fraction(numbers[0], numbers[1], numbers[2]); break;
	}
	return is;
}


//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define INCREMENTO_DECREMENTO_CHECK
//#define COMPARISON_OPERATORS
//#define STREAMS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER
//#define HAVE_A_NICE_DAY


void main() {
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A; // Default constructor
	A.print();

	Fraction B = 5; //Single - Argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

#endif CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();

	Fraction C = A * B;
	C.print();

	C = A / B;
	C.print();

	A *= B;
	A.print();

	A /= B;
	A.print();

	C = A + B;
	C.print();
	
	C = B - A;
	C.print();

	A += B;
	A.print();
	
	A -= B;
	A.print();

#endif ARITHMETICAL_OPERATORS_CHECK

#ifdef INCREMENTO_DECREMENTO_CHECK
	double a = 2;
	double b = 0;
	//b += ++ a ++;
	cout << a << endl;
	cout << b << endl;

	Fraction A(2, 3, 4);
	Fraction B;
	B = ++A++;
	A.print();
	B.print();
#endif INCREMENTO_DECREMENTO_CHECK

#ifdef COMPARISON_OPERATORS

	cout << (2 == 3) << endl;
	cout << (Fraction(1, 3) <= Fraction(5, 11)) << endl;

#endif COMPARISON_OPERATORS

	/*
	for (Fraction i(9, 1, 2); i > 0 ; --i) {
		i.print();
	}
	*/

#ifdef STREAMS_CHECK

	Fraction A(2, 3, 4);
	cout << "Введите простую дробь: ";
	cin >> A;
	cout << A << endl;
	
#endif STREAMS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS

	int a = 2;	// No conversion
	double b = 3;	// Conversion from less to more
	int c = b;	// Conversion from more to less whithout data loss
	int d = 5.5;	// Conversion from more to less with data loss

#endif TYPE_CONVERSIONS_BASICS

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS

	Fraction A = (Fraction)5;		//Single-Argument constructor (from less to more)
	cout << A << endl;

	Fraction B;
	B = (Fraction)8;		//Single-Argument constructor -> CopyAssignment (from less to more)
	//Single-Argument constructor создает из '8' временный безымянный объект,
	//а оператор присваивания просто записывает его в существующий объект 'B'

#endif CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef CONVERSIONS_FROM_CLASS_TO_OTHER

	Fraction A(2, 3, 4);
	A.to_improper().print();
	int a = (int)A;
	cout << a << endl;

	double b = A;
	cout << b << endl;

#endif CONVERSIONS_FROM_CLASS_TO_OTHER

#ifdef HAVE_A_NICE_DAY
	
	Fraction A = 3.333; 3.14159265359; //conversion from 'double' to 'Fraction'
	cout << A << endl;

#endif HAVE_A_NICE_DAY

}


