#include <iostream>
#include <string>

    void swapIfSmaller(std::string* a, std::string* b) 
    {
        if ((*a).length() < (*b).length())
        {
            std::swap(*a, *b);
        }
        if ((*a).length() > (*b).length())
        {
            while ((*b).length() < (*a).length())
            {
                *b = "0" + *b;
            }
        }
    }

    std::string Sum(std::string a, std::string b)
    {
        swapIfSmaller(&a, &b);
        std::string sumS = "0" + a;               
        for (int i = 0; i < sumS.length(); i++)
        {
            sumS[i] = '0';
        }

        bool flag = 0;
        int extraDigit = 0;       

        for (int i = 1; i < a.length() + 1; i++)
        {
            int c1 = int(a[a.length() - i]) - 48;       
            int c2 = int(b[b.length() - i]) - 48;

            int d = 0;     

            if (c1 + c2 + extraDigit > 9)
            {
                flag = 1;
                d = (c1 + c2) - 10 + extraDigit;
                sumS[a.length() - i + 1] = char(d + 48);
                extraDigit = (c1 + c2) / 10;
            }

            if (flag == 0)
            {
                int c = c1 + c2;
                sumS[a.length() - i + 1] = char(c + 48) + extraDigit;
                extraDigit = 0;

            }

            flag = 0;
        }

        if (extraDigit != 0)
        {
            sumS[0] = char(int(sumS[0]) + extraDigit);
        }

        if (sumS[0] == '0')
        {
            sumS.erase(0, 1);
        }
        return sumS;
    }


    std::string Mult(std::string a, std::string b)
    {
        std::string multS = a + b;

        for (int i = 0; i < a.length() + b.length(); i++)
        {
            multS[i] = '0';
        }

        std::string result = multS;

        std::string emptyS = multS;

        for (int i = 0; i < a.length(); i++)
        {
            for (int j = 0; j < b.length(); j++)
            {
                int c1 = a[a.length() - i - 1] - 48;
                int c2 = b[b.length() - j - 1] - 48;

                int mult = c1 * c2;

                multS[multS.length() - j - i - 1] = char(mult % 10 + 48);
                multS[multS.length() - j - i - 2] = char(mult / 10 + 48);


                while (result.length() > multS.length())
                {
                    multS = '0' + multS;
                }

                result = Sum(result, multS);

                multS = emptyS;
            }

        }
        if (result[0] == '0')
        {
            result.erase(0, 1);
        }
        return result;
    }

    int main()
    {
        std::cout << "Enter numbers a and b:  ";
        std::string a, b;
        std::cin >> a >> b;
        std::cout << "Sum: " << Sum(a, b) << " and Multiplication: " << Mult(a, b);
    }