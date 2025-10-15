#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "Object.h"
#include <sstream>

namespace dshw
{
    template <class T>
    class ArrayList : public Object
    {
        private:
            T* arr;
            int capacity;
            int size;

            void resize()
            {
                capacity *= 2;
                T* newArr = new T[capacity];
                for (int i = 0; i < size; ++i)
                {
                    newArr[i] = arr[i];
                }
                delete[] arr;
                arr = newArr;
            }

        public:
            T* begin()
            {
                return arr;
            }
            T* end()
            {
                return arr + size;
            }
            const T* begin() const
            {
                return arr;
            }
            const T* end() const
            {
                return arr + size;
            }
            ArrayList() : capacity(10), size(0)
            {
                arr = new T[capacity];
            }

            ArrayList(int initialCapacity) : capacity(initialCapacity), size(0)
            {
                if (initialCapacity <= 0)
                {
                    throw std::invalid_argument("Initial capacity must be greater than 0");
                }
                arr = new T[capacity];
            }

            ArrayList(std::initializer_list<T> initList) : capacity(initList.size()), size(0)
            {
                arr = new T[capacity];
                for (const T& value : initList)
                {
                    arr[size++] = value;
                }
            }

            ArrayList(const ArrayList& obj) : capacity(obj.capacity), size(obj.size)
            {
                arr = new T[capacity];
                for (int i = 0; i < size; ++i)
                {
                    arr[i] = obj.arr[i];
                }
            }

            ArrayList& operator=(const ArrayList& rhs)
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    capacity = rhs.capacity;
                    size = rhs.size;
                    arr = new T[capacity];
                    for (int i = 0; i < size; ++i)
                    {
                        arr[i] = rhs.arr[i];
                    }
                }
                return *this;
            }

            ~ArrayList() override
            {
                delete[] arr;
            }

            void insert(T value)
            {
                if (size == capacity)
                {
                    resize();
                }
                arr[size] = value;
                size++;
            }

            void insertFront(T value)
            {
                if (size == capacity)
                {
                    resize();
                }
                for (int i = size; i > 0; --i)
                {
                    arr[i] = arr[i - 1];
                }
                arr[0] = value;
                size++;
            }

            T pop()
            {
                if (size == 0)
                {
                    throw runtime_error("List is empty");
                }
                size--;
                return arr[size];
            }

            T popFront()
            {
                if (size == 0)
                {
                    throw runtime_error("List is empty");
                }
                T value = arr[0];
                for (int i = 1; i < size; ++i)
                {
                    arr[i - 1] = arr[i];
                }
                size--;
                return value;
            }

            bool remove(T value)
            {
                for (int i = 0; i < size; ++i)
                {
                    if (arr[i] == value)
                    {
                        for (int j = i; j < size - 1; ++j)
                        {
                            arr[j] = arr[j + 1];
                        }
                        size--;
                        return true;
                    }
                }
                return false;
            }

            bool contains(T value) const
            {
                for (int i = 0; i < size; ++i)
                {
                    if (arr[i] == value)
                    {
                        return true;
                    }
                }
                return false;
            }

            int getSize() const
            {
                return size;
            }

            T& operator[](int index)
            {
                if (index >= size)
                {
                    throw out_of_range("Index out of range");
                }
                return arr[index];
            }
            const T& operator[](int index) const
            {
                if (index >= size)
                {
                    throw out_of_range("Index out of range");
                }
                return arr[index];
            }

            T& at(int index)
            {
                if (index >= size)
                {
                    throw out_of_range("Index out of range");
                }
                return arr[index];
            }

            const T& at(int index) const
            {
                if (index >= size)
                {
                    throw out_of_range("Index out of range");
                }
                return arr[index];
            }

            int find(T value) const
            {
                for (int i = 0; i < size; ++i)
                {
                    if (arr[i] == value)
                    {
                        return i;
                    }
                }
                return -1;
            }

            string toString() const override
            {
                stringstream out;
                out << "[";
                for (int i = 0; i < size; ++i)
                {
                    out << arr[i];
                    if (i < size - 1)
                    {
                        out << ",";
                    }
                }
                out << "]";
                return out.str();
            }

            void reverse()
            {
                int left = 0;
                int right = size - 1;
                while (left < right)
                {
                    T temp = arr[left];
                    arr[left] = arr[right];
                    arr[right] = temp;
                    left++;
                    right--;
                }
            }


    };

}


#endif