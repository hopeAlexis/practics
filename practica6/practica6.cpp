#include <iostream>
#include <vector>

using namespace std;	
vector <int> numbers = { 1, 2, 3, 4, 5 }; //иницилизация вектора через присваивание 

void printVec()
{
	for (int i = 0; i < numbers.size(); i++)
		cout << numbers[i] << " "; //к элементу вектора можно обратиться по номеру через квадратные скобки
	cout << endl;
}

int main()
{
	numbers.push_back(6); //добавляет в конец элемент
	numbers.erase(numbers.begin()); //удаляет элемент находящийся в векторе на указанном месте
	numbers.insert(numbers.begin(), 7); //вставляет элемент на место следующее по счету после указанного
		printVec();
	numbers.emplace_back(8); //похоже на push_back, но создает непосредственно объект в конце вектора
		printVec();
	numbers.resize(4); //оставляет первые n элементов вектора (но не меняет вместимость)
		printVec();
	cout << "capacity: " << numbers.capacity() << endl; //вместимость вектора
	numbers.shrink_to_fit(); //подгоняет вместимость под количество элементов
	cout << "capacity after shrinking: " << numbers.capacity() << endl; 
	numbers.reserve(10); //устанавливает вмещаемость вектора 
	cout << "capacity after reserve: " << numbers.capacity() << endl;
	numbers.clear(); //удаляет все элементы из вектора
		printVec();

}