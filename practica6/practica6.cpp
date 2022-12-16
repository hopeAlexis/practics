#include <iostream>
#include <vector>

using namespace std;	
vector <int> numbers = { 1, 2, 3, 4, 5 }; //������������ ������� ����� ������������ 

void printVec()
{
	for (int i = 0; i < numbers.size(); i++)
		cout << numbers[i] << " "; //� �������� ������� ����� ���������� �� ������ ����� ���������� ������
	cout << endl;
}

int main()
{
	numbers.push_back(6); //��������� � ����� �������
	numbers.erase(numbers.begin()); //������� ������� ����������� � ������� �� ��������� �����
	numbers.insert(numbers.begin(), 7); //��������� ������� �� ����� ��������� �� ����� ����� ����������
		printVec();
	numbers.emplace_back(8); //������ �� push_back, �� ������� ��������������� ������ � ����� �������
		printVec();
	numbers.resize(4); //��������� ������ n ��������� ������� (�� �� ������ �����������)
		printVec();
	cout << "capacity: " << numbers.capacity() << endl; //����������� �������
	numbers.shrink_to_fit(); //��������� ����������� ��� ���������� ���������
	cout << "capacity after shrinking: " << numbers.capacity() << endl; 
	numbers.reserve(10); //������������� ����������� ������� 
	cout << "capacity after reserve: " << numbers.capacity() << endl;
	numbers.clear(); //������� ��� �������� �� �������
		printVec();

}