#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include "Object.h"

namespace dsc
{
    template <class T>
    class Array : public Object
    {
        private:
            T* arr = nullptr;
            size_t capacity;
            size_t count;
            static const size_t INITIAL_CAPACITY;

            void resize()
            {
                size_t newCapacity = capacity * 2;
                T* newArr = new T[newCapacity];
                for (size_t i = 0; i < count; ++i)
                {
                    newArr[i] = arr[i];
                }
                delete[] arr;
                arr = newArr;
                capacity = newCapacity;
            }

            void clear()
            {
                if (arr != nullptr)
                {
                    delete[] arr;
                    arr = nullptr;
                }
                capacity = 0;
                count = 0;
            }

        public:
            Array() : Array(100) {}
            Array(size_t size) : capacity(size), count(0)
            {
                if (size <= 0)
                {
                    throw std::invalid_argument("Size must be greater than 0");
                }
                arr = new T[capacity];
            }
            Array(std::initializer_list<T> initList) : Array(initList.size())
            {
                for (const T& value : initList)
                {
                    insert(value);
                }
            }
            Array(const Array<T>& obj) : capacity(obj.capacity), count(obj.count)
            {
                arr = new T[capacity];
                for (size_t i = 0; i < count; ++i)
                {
                    arr[i] = obj.arr[i];
                }
            }
            Array(Array<T>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), count(obj.count)
            {
                obj.arr = nullptr;
                obj.capacity = 0;
                obj.count = 0;
            }
            Array<T>& operator=(const Array<T>& rhs)
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    capacity = rhs.capacity;
                    count = rhs.count;
                    arr = new T[capacity];
                    for (size_t i = 0; i < count; ++i)
                    {
                        arr[i] = rhs.arr[i];
                    }
                }
                return *this;
            }
            Array<T>& operator=(Array<T>&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    arr = rhs.arr;
                    capacity = rhs.capacity;
                    count = rhs.count;
                    rhs.arr = nullptr;
                    rhs.capacity = 0;
                    rhs.count = 0;
                }
                return *this;
            }
            ~Array() override
            {
               if (arr != nullptr)
               {
                   delete[] arr;
                   arr = nullptr;
               }
            }

            size_t size() const
            {
                return count;
            }

            void insert(const T& value)
            {
                if (count == capacity)
                {
                    resize();
                }
                arr[count++] = value;
            }

            void insertAt(size_t index, const T& value)
            {
                if (index > count)
                {
                    throw std::out_of_range("Index out of range");
                }
                if (count == capacity)
                {
                    resize();
                }
                for (size_t i = count; i > index; --i)
                {
                    arr[i] = arr[i - 1];
                }
                arr[index] = value;
                ++count;
            }

            void removeAt(size_t index)
            {
                if (index >= count)
                {
                    throw std::out_of_range("Index out of range");
                }
                for (size_t i = index; i < count - 1; ++i)
                {
                    arr[i] = arr[i + 1];
                }
                --count;
            }

            void remove(const T& value)
            {
                for (size_t i = 0; i < count; ++i)
                {
                    if (arr[i] == value)
                    {
                        removeAt(i);
                        return;
                    }
                }
            }

            T& pop()
            {
                if (count == 0)
                {
                    throw std::underflow_error("Array is empty");
                }
                return arr[--count];
            }

            T& operator[](int index)
            {
                if (index >= count || index < -static_cast<int>(count))
                {
                    throw std::out_of_range("Index out of range");
                }
                if (index < 0 && static_cast<size_t>(-index) <= count)
                {
                    index = count + index;
                }
                return arr[index];
            }

            const T& operator[](int index) const
            {
                if (index >= count || index < -static_cast<int>(count))
                {
                    throw std::out_of_range("Index out of range");
                }
                if (index < 0 && static_cast<size_t>(-index) <= count)
                {
                    index = count + index;
                }
                return arr[index];
            }

            T& at(int index)
            {
                if (index >= count || index < -static_cast<int>(count))
                {
                    throw std::out_of_range("Index out of range");
                }
                if (index < 0 && static_cast<size_t>(-index) <= count)
                {
                    index = count + index;
                }
                return arr[index];
            }

            const T& at(int index) const
            {
                if (index >= count || index < -static_cast<int>(count))
                {
                    throw std::out_of_range("Index out of range");
                }
                if (index < 0 && static_cast<size_t>(-index) <= count)
                {
                    index = count + index;
                }
                return arr[index];
            }

            bool contains(const T& value) const
            {
                for (size_t i = 0; i < count; ++i)
                {
                    if (arr[i] == value)
                    {
                        return true;
                    }
                }
                return false;
            }

            size_t index(const T& value) const
            {
                for (size_t i = 0; i < count; ++i)
                {
                    if (arr[i] == value)
                    {
                        return i;
                    }
                }
                return count; // Not found
            }

            string toString() const override
            {
                std::stringstream out;
                out << "[";
                for (size_t i = 0; i < count; ++i)
                {
                    out << arr[i];
                    if (i < count - 1)
                    {
                        out << ",";
                    }
                }
                out << "]";
                return out.str();
            }

            void reserve(size_t newCapacity)
            {
                if (newCapacity > capacity)
                {
                    T* newArr = new T[newCapacity];
                    for (size_t i = 0; i < count; ++i)
                    {
                        newArr[i] = arr[i];
                    }
                    delete[] arr;
                    arr = newArr;
                    capacity = newCapacity;
                }
            }

            T* begin()
            {
                return arr;
            }
            T* end()
            {
                return arr + count;
            }
            const T* begin() const
            {
                return arr;
            }
            const T* end() const
            {
                return arr + count;
            }

    };
    template <class T>
    const size_t Array<T>::INITIAL_CAPACITY = 100;
}




#endif