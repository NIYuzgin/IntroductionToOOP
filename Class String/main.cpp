﻿#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n---------------------------------------------\n"

class String {
	int size; // размер строки в Байтах (с учетом NULL-Terminator)
	char* str; // адрес строки в динамической памяти
	
public:
	
	int get_size() const {
		return size;
	}
	
	const char* get_str() const {
		return str;
	}
	
	char* get_str() {
		return str;
	}

	//	Constructors:
		
	explicit String(int size = 80) //Конструктор по умолчанию создает строку размером 80 Байт
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	 
	String(const char* str) {
		this->size = strlen(str) + 1;	// strlen() возвращает размер строки в символах,
										//+1 нужен, чтобы выделилась память под NULL-Terminator
		this->str = new char[size] {};
		for (int i = 0; i < size; i++) this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	
	String(const String& other) {
		this->size = other.size;
		//this->str = other.str;    //Shallow copy
		//Deep copy:
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	
	String(String&& other) {
		// MoveConstructor -Shallow copy
		this->size = other.size;
		this->str = other.str;
		// обнуляем принимаемый объект, для того, чтобы предотвратить удаление его ресурсов деструктором
		other.size = 0;
		other.str = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}

	~String() {
		delete[] str;
		str = nullptr;
		size = 0;
		cout << "Destructor:\t\t" << this << endl;
	}

	//	Operators:

	String& operator= (const String& other){
		
		//0) Проверяем, не является ли тот объект этим объектом
		if (this == &other)return *this;
		//1) удаляем старую динамическую память
		delete[] this->str;
		//this->str = other.str; // Shallow copy - Поверхностное копирование
		this->size = other.size; // Deep copy - Побитовое копирование
		//2) выделяем новую динамическую память
		this->str = new char[size] {}; 
		for (int i = 0; i < size; i++) this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	
	String& operator= (String&& other) {
		
		//0) Проверяем, не является ли 'this' и 'other' одним и тем же объектом
		if (this == &other)return *this;
		//1) удаление старой памяти
		delete[] str;
		//2)	Shallow copy
		this->size = other.size;
		this->str = other.str;
		//3) обнуляем принимаемый объект:
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:\t\t" << this << endl;
		return *this;
	}

	char operator[](int i)const {
		return str[i]; // [] - Index operator, Subscript operator
	}
	
	char& operator[](int i) {
		return str[i];
	}

	//	Methods:

	void print()const {
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}

};

String operator+(const String& left, const String& right) {
	String result (left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		result[i] = left[i];
		//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj) {
	return os << obj.get_str();
}

/*
void Clear(char* str) {
	delete[] str;
}
*/	


 //#define CONSTRUCTORS_CHECK
//#define COPY_SEMANTIC_CHECK

void main() {
	setlocale(LC_ALL, "");
		
#ifdef CONSTRUCTORS_CHECK

	String str1;
	str1.print();

	String str2(5);
	str2.print();

	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;

	String str4 = "World";
	cout << str4 << endl;

	cout << delimiter << endl;
	String str5;
	str5 = str3 + str4;
	cout << delimiter << endl;
	cout << str5 << endl;

#endif CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK
	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;

	String str2;
	str2 = str1;

	cout << str2 << endl;

#endif COPY_SEMANTIC_CHECK

	String str1;
	str1.print();
	
	String str3(5);
	str3.print();



	String str2 = "Hello";
	str2.print();
	
	String str4(); // В этой строке не вызывается DefaultConstructor, и НЕ создается объект
					// здесь объявляется функция 'str4', которая ничего не принимает,
					// и возвращает значение типа "String'
					// 
	// то есть 

	String str5{};
	str5.print();
	
	String str6{6};
	str6.print();
	
	String str7{"World"};
	str7.print();
	
	String str8 =str7;
	str8.print();
	
	String str9(str8);
	str9.print();
	
	String str10(str9);
	str10.print();

	// Фигурные скобки для вызова конструкторов следует использовать с большой осторожностью


}			
			
		

