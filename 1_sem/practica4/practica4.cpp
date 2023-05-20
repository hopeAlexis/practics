#include <iostream>

void package(unsigned int left, unsigned int middle, unsigned int right)
{	
	unsigned char package1, package2;
	package1 = (unsigned char)(right + (middle % 8) * 32);
	package2 = (unsigned char)(left * 4 + (middle - middle % 8) / 8);
	std::cout << +package1 << " " << +package2 << std::endl; 
}

void unpackage(unsigned int package1, unsigned int package2)
{
	unsigned int left, middle, right;
	right = package1 % 32;
	middle = (package2 % 4) * 8 + (package1 - package1 % 32) / 32;
	left = (package2 - package2 % 4) / 4;
	std::cout << left << " " << middle << " " << right;
}

int main()
{
	package(17, 7, 5);
	unsigned char a = (unsigned char)229;
	unsigned char b = (unsigned char)68;
	unpackage(a, b);
}