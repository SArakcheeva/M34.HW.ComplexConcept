/* Ќапишите концепт под названием ComplexConcept<T>, 
   который будет накладывать следующие ограничени€ на тип :

	- Ќаличие у типа T метода hash(), который возвращает тип, конвертируемый в long;
	- Ќаличие у типа T метода toString(), который возвращает std::string;
	- ќтсутствие у типа T виртуального деструктора.


ѕодсказки:
	1 - ƒл€ проверки наличи€ у типа метода перечислите ограничени€, использу€ ключевое слово requires
	2 - ƒл€ проверки конвертируемости возвращаемого типа воспользуетесь трейтом std::convertible_to
	3 - ƒл€ проверки возвращаемого типа воспользуетесь трейтом std::same_as
	4 - ƒл€ проверки отсутстви€ у типа виртуального деструктора воспользуетесь трейтом std::has_virtual_destructor
 */


#include <iostream>
#include <string>
#include <bits/stdc++.h>

 // ѕосле ключевого слова requires мы можем пречислить список требований, 
 // которые мы накладыаем на типы, которые мы передали
template <typename T> concept ComplexConcept = requires(T v) {

	// метод hash(), который возвращает тип, конвертируемый в long
	{ v.hash() } -> std::convertible_to<long>;

	// метод toString(), который возвращает std::string
	// (т.е. тип метода toString() должен быть в точности std::string)
	{ v.toString() } -> std::same_as<std::string>;

	// отсутствие у типа T виртуального деструктора
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