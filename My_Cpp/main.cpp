#include "My_STL.h"
#include <iostream>
#include <array>

int main()
{
    MyArray<std::string, 10> arr{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    MyArray<std::string, 10> arr2 = { "һ", "��", "��", "��", "��", "��", "��", "��", "��", "ʮ" };

    std::array<std::string, 10> originArr = { "һ", "��", "��", "��", "��", "��", "��", "��", "��", "ʮ" };

    MyArray<std::string, 10>::iterator it = arr2.rbegin();
    for (; it != arr2.rend(); it--)
    {
        std::cout << *it << " ";
    }

    return 0;
}