#pragma once

#include <stdexcept>

template<typename T, size_t N>
class MyArray {
private:
    T array[N];
public:
    // �ɱ����ģ�幹�캯��
    template<typename... Args>
    MyArray(Args... args) : array{ args... }
    {
        static_assert(sizeof...(args) <= N, "Too many parameters!");
    }
    using Reference = T&;
    using Pointer = T*;
    using ConReference = const T&;
    using ConPointer = const T*;

    size_t size() const { return N; }// ����array����
    ConReference at(size_t index) const
    {
        if (index >= N) throw std::out_of_range("Index out of range!");
        return array[index]; // ͨ��at�����±��Ӧ��ֵ
    }
    Reference operator[](size_t index)
    {
        if (index >= N) throw std::out_of_range("Index out of range!");
        return array[index];// �����±��Ӧֵ ����Ϊ��ֵ
    }
    ConReference operator[](size_t index) const
    {
        if (index >= N) throw std::out_of_range("Index out of range!");
        return array[index];// �����±��Ӧֵ ����Ϊ��ֵ
    }
    /* ��������� */
    ConPointer begin() const { return &(array[0]); }// ������ʼָ��
    ConPointer end() const { return &(array[N]); }// ����ĩβ���ָ��
    /* ��������� */
    ConPointer rbegin() const { return &(array[N - 1]); }// ����ĩβָ��
    ConPointer rend() const { return &(array[-1]); }// ������ʼǰ��ָ��

    ConReference front() const { return array[0]; }// ���ص�һ��Ԫ�ص�����
    ConReference back() const
    {
        if (N == 0) throw std::out_of_range("Array is empty");
        return array[N - 1];// �������һ��Ԫ�ص�����
    }
    void fill(ConReference value) { for (auto& val : array) val = value; }// ���

    void swap(MyArray& ano_Arr)
    {
        T temp;
        for (size_t i = 0; i < N; i++)
        {
            temp = array[i];
            array[i] = ano_Arr[i];
            ano_Arr[i] = temp;// ����
        }
    }
    // ������
    class iterator
    {
    private:
        Pointer ptr; // ���յ���MyArray��Ԫ�ص�ַ
    public:
        iterator(Pointer p = nullptr) : ptr(p) {}
        // ��д����� * -> ++ -- == !=
        Reference operator*() const { return *ptr; } // ����ptr�Ķ�Ӧ��ֵ
        Pointer operator->() const { return ptr; } // ����ptr
        /* �ж��Ƿ���� */
        bool operator==(const iterator& ano_Iterator) { return this->ptr == ano_Iterator.ptr; }
        bool operator!=(const iterator& ano_Iterator) { return this->ptr != ano_Iterator.ptr; }

        /* �����������Ϊʲô˵ǰ��++Ч�ʸ��� */
        iterator& operator++()
        {
            ++ptr;
            return *this;// ǰ׺++
        }
        // ע�����ﷵ�ص��ǿ�������������
        iterator operator++(int)
        {
            iterator temp = *this; // ����һ������
            ++(*this);
            return temp;// ��׺++
        }
        iterator& operator--()
        {
            --ptr;
            return *this;// ǰ׺--
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            --(*this);
            return temp;// ��׺--
        }
    };
    // ע����������
    iterator begin() { return iterator(array); }
    iterator end() { return iterator(array + N); }
    iterator rbegin() { return iterator(array + N - 1); }
    iterator rend() { return iterator(array - 1); }
};