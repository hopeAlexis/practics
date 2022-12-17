#include <iostream>

class Array
{
private:
    int a_size = 1;
    int* a_array = new int[a_size];

public:
    Array(int element)
    {
        a_size = 1;
        a_array[0] = element;
    }

    void push_back(int element)
    {
        int* temp = new int[a_size + 1];
        for (int i = 0; i < a_size; i++)
        {
            temp[i] = a_array[i];
        }
        temp[a_size] = element;
        delete[]a_array;
        a_array = temp;
        a_size++;
    }

    int size()
    {
        return a_size;
    }

    int element(int index)
    {
        return a_array[index];
    }

    void change_element(int index, int element)
    {
        a_array[index] = element;
    }

    void delete_element(int index)
    {
        for (int i = index; i < a_size - 1; i++)
        {
            a_array[i] = a_array[i + 1];
        }
        a_size --;
    }

    void insert(int index, int element)
    {
        int* temp = new int[a_size + 2];

        for (int i = 0; i < index; i++)
        {
            temp[i] = a_array[i];
        }

        temp[index] = element;

        for (int i = index + 1; i < a_size + 1; i++)
        {
            temp[i] = a_array[i - 1];
        }

        a_size++;
        delete[]a_array;
        a_array = temp;

    }

    void print()
    {
        for (int i = 0; i < a_size; i++)
        {
            std::cout << a_array[i] << " ";
        }
    }

};

int main()
{
    int n, amount;
    std::cout << "Enter the [0] element of array: "; std::cin >> n;
    Array mas(n);

    std::cout << "Enter the amount of elements for a push_back: "; std::cin >> amount;
    for (int i = 0; i < amount; i++)
    {
        std::cout << "[" << mas.size() << "] element: "; std::cin >> n;
        mas.push_back(n);
    }
    mas.print();
    std::cout << "Size of array: " << mas.size() << std::endl;

    std::cout << "Let's change [1] element in array. ";
    mas.change_element(1, mas.element(1) + 1);
    std::cout << "Element [1]: " << mas.element(1) << std::endl;

    std::cout << "Let's insert number 100 between [1] and [3]. ";
    mas.insert(2, 100);
    mas.print();
}