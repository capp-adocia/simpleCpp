#pragma once

#include <stdexcept>

template<typename T, size_t N>
class MyArray {
private:
    T array[N];
public:
    // 可变参数模板构造函数
    template<typename... Args>
    MyArray(Args... args) : array{ args... }
    {
        static_assert(sizeof...(args) <= N, "Too many parameters!");
    }
    using Reference = T&;
    using Pointer = T*;
    using ConReference = const T&;
    using ConPointer = const T*;

    size_t size() const { return N; }// 返回array长度
    ConReference at(size_t index) const
    {
        if (index >= N) throw std::out_of_range("Index out of range!");
        return array[index]; // 通过at访问下标对应的值
    }
    Reference operator[](size_t index)
    {
        if (index >= N) throw std::out_of_range("Index out of range!");
        return array[index];// 返回下标对应值 参数为左值
    }
    ConReference operator[](size_t index) const
    {
        if (index >= N) throw std::out_of_range("Index out of range!");
        return array[index];// 返回下标对应值 参数为右值
    }
    /* 正向迭代器 */
    ConPointer begin() const { return &(array[0]); }// 返回起始指针
    ConPointer end() const { return &(array[N]); }// 返回末尾后的指针
    /* 反向迭代器 */
    ConPointer rbegin() const { return &(array[N - 1]); }// 返回末尾指针
    ConPointer rend() const { return &(array[-1]); }// 返回起始前的指针

    ConReference front() const { return array[0]; }// 返回第一个元素的引用
    ConReference back() const
    {
        if (N == 0) throw std::out_of_range("Array is empty");
        return array[N - 1];// 返回最后一个元素的引用
    }
    void fill(ConReference value) { for (auto& val : array) val = value; }// 填充

    void swap(MyArray& ano_Arr)
    {
        T temp;
        for (size_t i = 0; i < N; i++)
        {
            temp = array[i];
            array[i] = ano_Arr[i];
            ano_Arr[i] = temp;// 交换
        }
    }
    // 迭代器
    class iterator
    {
    private:
        Pointer ptr; // 接收的是MyArray的元素地址
    public:
        iterator(Pointer p = nullptr) : ptr(p) {}
        // 重写运算符 * -> ++ -- == !=
        Reference operator*() const { return *ptr; } // 返回ptr的对应的值
        Pointer operator->() const { return ptr; } // 返回ptr
        /* 判断是否相等 */
        bool operator==(const iterator& ano_Iterator) { return this->ptr == ano_Iterator.ptr; }
        bool operator!=(const iterator& ano_Iterator) { return this->ptr != ano_Iterator.ptr; }

        /* 这里就体现了为什么说前置++效率更高 */
        iterator& operator++()
        {
            ++ptr;
            return *this;// 前缀++
        }
        // 注意这里返回的是拷贝，不是引用
        iterator operator++(int)
        {
            iterator temp = *this; // 多了一个拷贝
            ++(*this);
            return temp;// 后缀++
        }
        iterator& operator--()
        {
            --ptr;
            return *this;// 前缀--
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            --(*this);
            return temp;// 后缀--
        }
    };
    // 注意类外重载
    iterator begin() { return iterator(array); }
    iterator end() { return iterator(array + N); }
    iterator rbegin() { return iterator(array + N - 1); }
    iterator rend() { return iterator(array - 1); }
};