#include "My_STL.h"
#include <iostream>
#include <array>

int main()
{
    MyArray<std::string, 10> arr{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    MyArray<std::string, 10> arr2 = { "一", "二", "三", "四", "五", "六", "七", "八", "九", "十" };

    std::array<std::string, 10> originArr = { "一", "二", "三", "四", "五", "六", "七", "八", "九", "十" };

    MyArray<std::string, 10>::iterator it = arr2.rbegin();
    for (; it != arr2.rend(); it--)
    {
        std::cout << *it << " ";
    }

    return 0;
}