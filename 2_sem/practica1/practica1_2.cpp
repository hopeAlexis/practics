#include <iostream>
#include <string>

class Cipher
{
private:
	int c_fibonacci[30] = { 1,2 };
	std::string c_words[30];
	std::string c_encodedWords[30];
	int c_key[30];

	int c_wordAmount = 0;

	void fiboFinder()		//fills in fibonacci sequence
	{
		for (size_t i = 2; i <= c_wordAmount; i++)
		{
			c_fibonacci[i] = c_fibonacci[i - 1] + c_fibonacci[i - 2];
		}
	}

	void wordCount(const std::string& message)		//counts words in a message (until there's a " ")
	{
		int helper = 0;
		for (size_t i = 0; i < message.length(); i++)
		{
			if (message[i] != ' ')		//so that we don't count a " " + " " as a word 
			{
				helper++;
			}
			else
			{
				if (helper != 0)
				{
					helper = 0;
					c_wordAmount++;
				}
			}
		}
	}


public:
	Cipher(std::string str)
	{
		wordCount(str);
		fiboFinder();

		int count = -1;

		for (size_t i = 0; i < c_wordAmount; i++) //input into c_words array
		{
			count++;		//to account for a " " that breaks the while cycle
			while (str[count] != ' ')
			{
				if (count >= str.length())
					break;
				c_words[i] += str[count];
				count++;
			}
		}

	}

	void keyInput()
	{
		std::cout << "Enter the key for encoding/decoding: ";
		for (size_t i = 0; i < c_wordAmount; i++)
		{
			std::cin >> c_key[i];
		}
		isKeyCorrect();
	}	

	void isKeyCorrect()
	{
		int count = 0;

		for (int i = 0; i < c_wordAmount; i++)
		{
			for (int j = 0; j < c_wordAmount; j++)
			{
				if (c_key[i] == c_fibonacci[j])
				{
					count++;		//checking the correlation between key and the fibonacci sequence
				}
			}

		}

		if (count != c_wordAmount)
		{
			throw "This key is incorrect.";
		}
	}
	
	void keyOutput()
	{
		std::cout << "The key: ";
		for (size_t i = 0; i < c_wordAmount; i++)
		{
			std::cout << c_key[i] << " ";
		}
		std::cout << "\n\n";
	}

	void encode()
	{
		for (size_t i = 0; i < c_wordAmount; i++)
		{
			for (size_t j = 0; j < c_wordAmount; j++)
			{
				if (c_key[i] == c_fibonacci[j])
					c_encodedWords[i] = c_words[j];
			}
		}

		for (size_t i = 0; i < c_wordAmount; i++)
		{
			c_words[i] = c_encodedWords[i];
		}
	}

	void decode()
	{
		for (size_t i = 0; i < c_wordAmount; i++)
		{
			for (size_t j = 0; j < c_wordAmount; j++)
			{
				if (c_key[i] == c_fibonacci[j])
					c_encodedWords[j] = c_words[i];
			}
		}

		for (size_t i = 0; i < c_wordAmount; i++)
		{
			c_words[i] = c_encodedWords[i];
		}

	}

	void messageOutput()
	{
		std::cout << "The message: ";
		for (size_t i = 0; i < c_wordAmount; i++)
		{
			std::cout << c_words[i] << " ";
		}
		std::cout << "\n\n";
	}

};




int main()
{
	try
	{
		std::string str;
		std::getline(std::cin, str);
		Cipher cipher(str + " ");
		cipher.keyInput();
		cipher.encode();
		cipher.messageOutput();
		cipher.keyOutput();
		cipher.decode();
		cipher.messageOutput();
	}
	catch (std::string message) {
		std::cout << message;
	}
}
