
#include <iostream>

using namespace std;

{
	class String {
		int size; // размер сторки
		char* str;
	public:

		explicit String(int size = 80)
			this->size = size;
		this->str = new char[size];
		cout << "DefaultConstructor:\t" << this << endl;


		void print()const{
			cout << endl;


	};
	
	
	;
void main() {
	setlocale(LC_ALL, "");

	String str1;
	str1.print();
	

	String str2(5);
	str2.print();

	String str3 = "Hello";
	str3.print();
	cout << str3 << endl;
}
