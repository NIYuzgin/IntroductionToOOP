#include <iostream>

using namespace std;

class Fraction {

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

		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	// Constructors:

	Fraction(int integer = 0, int numerator = 0, int denominator = 0) {

		this->integer = integer;
		this->numerator = numerator;
		this -> set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
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
		this -> set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}

	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	void print()const {

		if (integer) cout << integer;
		if (numerator) {

			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
			else if (integer == 0)cout << "0";

		}





	}

};

#define CONSTRUCTORS_CHECK

void main() {
	setlocale(LC_ALL, "");



#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	A.print();
	
	Fraction B = 5;
	B.print();
	
	Fraction C(1,2);
	C.print();




#endif CONSTRUCTORS_CHECK



}