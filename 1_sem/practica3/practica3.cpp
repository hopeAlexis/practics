#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::vector<int>> readFile()
{
	std::ifstream in("input.txt", std::ios::in);
	std::string s;
	std::vector <std::vector<int>> alphabet(26, std::vector<int>(2));
	for (int i = 0; i < 26; i++)
		alphabet[i][1] = i + 65;
	if (!in.is_open())
		std::cout << "cool";
	while (!in.eof())
	{
		in >> s;
		for (int i = 0; i < s.length(); i++)
		{
			if (unsigned char(s[i]) >= 65 && unsigned char(s[i]) <= 90)
			{
				alphabet[int(unsigned char(s[i] - 'A'))][0] += 1;
			}
			else if (unsigned char(s[i]) >= 97 && unsigned char(s[i]) <= 122)
			{
				alphabet[int(unsigned char(s[i] - 'a'))][0] += 1;
			}
		}
	}
	in.close();
	return alphabet;
}

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

std::vector<std::vector<int>> sortAlphabet(std::vector<std::vector<int>> alphabet)
{
	for (int i = 0; i < alphabet.size() - 1; i++)
	{
		for(int j = i; j < alphabet.size(); j++)
		{
			if (alphabet[i][0] < alphabet[i + 1][0])
			{
				swap(alphabet[i][0], alphabet[j][0]);
				swap(alphabet[i][1], alphabet[j][1]);
			}
		}
	}
	std::cout << alphabet[0][0];
	return alphabet;
}

int* maxLetters(std::vector<std::vector<int>> alphabet)
{
	static int maxLetters[8];
	for (int i = 0; i < alphabet.size(); i++)
	{
		maxLetters[i] = alphabet[i][1];
	}
	return maxLetters;
}

std::vector <int> is5outOf8(std::string s, int letters[8])
{
	std::vector <int> count = {0};
	for (int i = 0; i < s.length(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (s[i] == char(letters[j]) || s[i] == char(letters[j] + 32))
			{
				count[i] == letters[j];
				break;
			}
		}
	}
	return count;
}

void changeText(int letters[8])
{
	std::ifstream in("input.txt", std::ios::in);
	std::ofstream out("output.txt", std::ios::out);
	std::string s;
	std::vector <int> count;
	while (!in.eof())
	{
		in >> s;
		count = is5outOf8(s, letters);
		if (count.size() >= 5)
		{
			for (int i = 0; i < s.length(); i++)
			{
				if (unsigned char(s[i]) >= 'a' && unsigned char(s[i]) <= 'z')
					out << s[i] - 26;
				else
					out << s[i];
			}
			out << " (";
			for (int i = 0; i < count.size(); i++)
				out << s[i]; 
			out << ") ";
		}
		else
			out << s;
	}
}

int main()
{
	changeText(maxLetters(sortAlphabet(readFile())));
}