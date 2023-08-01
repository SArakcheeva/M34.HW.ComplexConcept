/* �������� ������� ��� ��������� ComplexConcept<T>, 
   ������� ����� ����������� ��������� ����������� �� ��� :

	- ������� � ���� T ������ hash(), ������� ���������� ���, �������������� � long;
	- ������� � ���� T ������ toString(), ������� ���������� std::string;
	- ���������� � ���� T ������������ �����������.


���������:
	1 - ��� �������� ������� � ���� ������ ����������� �����������, ��������� �������� ����� requires
	2 - ��� �������� ���������������� ������������� ���� �������������� ������� std::convertible_to
	3 - ��� �������� ������������� ���� �������������� ������� std::same_as
	4 - ��� �������� ���������� � ���� ������������ ����������� �������������� ������� std::has_virtual_destructor
 */


#include <iostream>
#include <string>
#include <bits/stdc++.h>

 // ����� ��������� ����� requires �� ����� ���������� ������ ����������, 
 // ������� �� ���������� �� ����, ������� �� ��������
template <typename T> concept ComplexConcept = requires(T v) {

	// ����� hash(), ������� ���������� ���, �������������� � long
	{ v.hash() } -> std::convertible_to<long>;

	// ����� toString(), ������� ���������� std::string
	// (�.�. ��� ������ toString() ������ ���� � �������� std::string)
	{ v.toString() } -> std::same_as<std::string>;

	// ���������� � ���� T ������������ �����������
	std::has_virtual_destructor<T>::value == false;
};


struct Number {
	int _num{ 0 };

	long hash() {
		return static_cast<long>(_num);
	}

	std::string toString() const {
		return std::to_string(_num);
	}
};


struct Number2 {
	virtual ~Number2() {}
};


void PrintType(ComplexConcept auto& t) {
	std::cout << t.toString() << '\n';
}


int main() {
	Number x{ 5 };
	PrintType(x);
	std::cout << std::boolalpha << std::has_virtual_destructor<Number>::value << std::endl;
	std::cout << std::boolalpha << std::has_virtual_destructor<Number2>::value << std::endl;
}