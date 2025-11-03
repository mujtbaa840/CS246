#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Hash.h"
#include "LinkedList.h"
#include "Object.h"

namespace dsc
{
    template <class T>
    class SetOpen : public Object
    {
        private:
            T** arr;
            size_t capacity;
            size_t count;
            Hash<T> hashFunc;
            static const size_t INITIAL_CAPACITY = 100;

            void clear()
            {
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr)
                    {
                        delete arr[i];
                        arr[i] = nullptr;
                    }
                }
                delete[] arr;
                arr = nullptr;
                capacity = 0;
                count = 0;
            }

            void resize()
            {
                size_t newCapacity = capacity * 2;
                T** newArr = new T*[newCapacity]{nullptr};

                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr)
                    {
                        size_t index = hashFunc(*arr[i]) % newCapacity;
                        while (newArr[index] != nullptr)
                        {
                            index = (index + 1) % newCapacity;
                        }
                        newArr[index] = arr[i];
                        arr[i] = nullptr;
                    }
                }
                delete[] arr;
                arr = newArr;
                capacity = newCapacity;
            }

        public:
            SetOpen() : SetOpen(INITIAL_CAPACITY) {}
            SetOpen(size_t cap) : capacity(cap), count(0)
            {
                if (capacity == 0)
                {
                    throw std::invalid_argument("Capacity must be greater than 0");
                }
                arr = new T*[capacity]{nullptr};
            }
            
            SetOpen(std::initializer_list<T> initList) : SetOpen(initList.size())
            {
                for (const T& value : initList)
                {
                    insert(value);
                }
            }
            SetOpen(const SetOpen<T>& obj) : capacity(obj.capacity), count(obj.count)
            {
                arr = new T*[capacity]{nullptr};
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (obj.arr[i] != nullptr)
                    {
                        arr[i] = new T(*obj.arr[i]);
                    }
                }
            }
            SetOpen(SetOpen<T>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), count(obj.count)
            {
                obj.arr = nullptr;
                obj.capacity = 0;
                obj.count = 0;
            }
            SetOpen<T>& operator=(const SetOpen<T>& obj)
            {
                if (this != &obj)
                {
                    clear();
                    capacity = obj.capacity;
                    count = obj.count;
                    arr = new T*[capacity]{nullptr};
                    for (size_t i = 0; i < capacity; ++i)
                    {
                        if (obj.arr[i] != nullptr)
                        {
                            arr[i] = new T(*obj.arr[i]);
                        }
                    }
                }
                return *this;
            }
            SetOpen<T>& operator=(SetOpen<T>&& obj) noexcept
            {
                if (this != &obj)
                {
                    clear();
                    capacity = obj.capacity;
                    count = obj.count;
                    arr = obj.arr;
                    obj.arr = nullptr;
                    obj.capacity = 0;
                    obj.count = 0;
                }
                return *this;
            }
            ~SetOpen() override
            {
                clear();
            }
            
            void insert(const T& value)
            {
                if (count == capacity)
                {
                    resize();
                }
                size_t index = hashFunc(value) % capacity;
                while (arr[index] != nullptr)
                {
                    if (*arr[index] == value)
                    {
                        return;
                    }
                    index = (index + 1) % capacity;
                }
                arr[index] = new T(value);
                ++count;
            }

            void remove(const T& value)
            {
                size_t index = hashFunc(value) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (*arr[index] == value)
                    {
                        delete arr[index];
                        arr[index] = nullptr;
                        --count;
                        return;
                    }
                    index = (index + 1) % capacity;
                    if (index == startIndex)
                    {
                        return;
                    }
                }
            }
            bool contains(const T& value) const
            {
                size_t index = hashFunc(value) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (*arr[index] == value)
                    {
                        return true;
                    }
                    index = (index + 1) % capacity;
                    if (index == startIndex)
                    {
                        break;
                    }
                }
                return false;
            }
            size_t size() const
            {
                return count;
            }
            std::string toString() const override
            {
                std::stringstream out;
                out << "{";
                bool first = true;
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr)
                    {
                        if (!first)
                        {
                            out << ",";
                        }
                        out << *arr[i];
                        first = false;
                    }
                }
                out << "}";
                return out.str();    
            }

            class const_iterator
            {
                private:
                    T* const* arr;
                    size_t capacity;
                    size_t index;

                    void skipToNext()
                    {
                        while (index < capacity && arr[index] == nullptr)
                        {
                            ++index;
                        }
                    }

                public:
                    const_iterator(T* const* array, size_t cap, size_t idx) : arr(array), capacity(cap), index(idx)
                    {
                        skipToNext();
                    }
                    const T& operator*() const
                    {
                        return *arr[index];
                    }
                    const_iterator& operator++()
                    {
                        ++index;
                        skipToNext();
                        return *this;
                    }
                    const_iterator operator++(int)
                    {
                        const_iterator temp = *this;
                        ++(*this);
                        return temp;
                    }
                    bool operator==(const const_iterator& other) const
                    {
                        return index == other.index;
                    }
                    bool operator!=(const const_iterator& other) const
                    {
                        return index != other.index;
                    }
            };
            
            const_iterator begin() const
            {
                return const_iterator(arr, capacity, 0);
            }
            const_iterator end() const
            {
                return const_iterator(arr, capacity, capacity);
            }
    };
    const size_t INITIAL_CAPACITY = 100;

    template <class T>
    class SetChain : public Object
    {
            private:
                LinkedList<T>* arr;
                size_t capacity;
                size_t count;
                size_t arrSize;
                Hash<T> hashFunc;
                static const size_t INITIAL_CAPACITY;

                void resize()
                {
                    size_t newCapacity = capacity * 2;
                    LinkedList<T>* newArr = new LinkedList<T>[newCapacity];

                    for (size_t i = 0; i < capacity; ++i)
                    {
                        for (const T& value : arr[i])
                        {
                            size_t index = hashFunc(value) % newCapacity;
                            newArr[index].insert(value);
                        }
                    }
                    delete[] arr;
                    arr = newArr;
                    capacity = newCapacity;
                }
            public:
                SetChain() : SetChain(INITIAL_CAPACITY) {}
                SetChain(size_t cap) : capacity(cap), count(0), arrSize(0)
                {
                    if (capacity == 0)
                    {
                        throw std::invalid_argument("Capacity must be greater than 0");
                    }
                    arr = new LinkedList<T>[capacity];
                }
                SetChain(std::initializer_list<T> initList) : SetChain(initList.size())
                {
                    for (const T& value : initList)
                    {
                        insert(value);
                    }
                }
                SetChain(const SetChain<T>& obj) : capacity(obj.capacity), count(obj.count), arrSize(obj.arrSize)
                {
                    arr = new LinkedList<T>[capacity];
                    for (size_t i = 0; i < capacity; ++i)
                    {
                        arr[i] = obj.arr[i];
                    }
                }
                SetChain(SetChain<T>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), count(obj.count), arrSize(obj.arrSize)
                {
                    obj.arr = nullptr;
                    obj.capacity = 0;
                    obj.count = 0;
                    obj.arrSize = 0;
                }
                SetChain<T>& operator=(const SetChain<T>& obj)
                {
                    if (this != &obj)
                    {
                        delete[] arr;
                        capacity = obj.capacity;
                        count = obj.count;
                        arrSize = obj.arrSize;
                        arr = new LinkedList<T>[capacity];
                        for (size_t i = 0; i < capacity; ++i)
                        {
                            arr[i] = obj.arr[i];
                        }
                    }
                    return *this;
                }
                SetChain<T>& operator=(SetChain<T>&& obj) noexcept
                {
                    if (this != &obj)
                    {
                        delete[] arr;
                        capacity = obj.capacity;
                        count = obj.count;
                        arrSize = obj.arrSize;
                        arr = obj.arr;;
                        obj.arr = nullptr;
                        obj.capacity = 0;
                        obj.count = 0;
                        obj.arrSize = 0;
                    }
                    return *this;
                }
                ~SetChain() override
                {
                    delete[] arr;
                }
                void insert(const T& value)
                {
                    if (arrSize == capacity)
                    {
                        resize();
                    }
                    size_t index = hashFunc(value) % capacity;
                    if (arr[index].contains(value))
                    {
                        return;
                    }
                    if (!arr[index].size())
                    {
                        arrSize++;
                    }
                    arr[index].insert(value);
                    count++;
                }
                void remove(const T& value)
                {
                    size_t index = hashFunc(value) % capacity;
                    if (arr[index].contains(value))
                    {
                        arr[index].remove(value);
                        count--;
                        if (arr[index].size() == 0)
                        {
                            arrSize--;
                        }
                    }
                }
                bool contains(const T& value) const
                {
                    size_t index = hashFunc(value) % capacity;
                    return arr[index].contains(value);
                }
                size_t size() const
                {
                    return count;
                }
                std::string toString() const override
                {
                    std::stringstream out;
                    out << "{";
                    bool first = true;
                    for (size_t i = 0; i < capacity; ++i)
                    {
                        for (const T& value : arr[i])
                        {
                            if (!first)
                            {
                                out << ",";
                            }
                            out << value;
                            first = false;
                        }
                    }
                    out << "}";
                    return out.str();    
                }

                class const_iterator
                {
                    private:
                        const SetChain<T>* set;
                        size_t bucketIndex;
                        typename LinkedList<T>::const_iterator listIterator;

                        void advanceToNextValid()
                        {
                            while (bucketIndex < set->capacity && set->arr[bucketIndex].size() == 0)
                            {
                                ++bucketIndex;
                            }
                            if (bucketIndex < set->capacity)
                            {
                                listIterator = set->arr[bucketIndex].begin();
                            }
                        }

                    public:
                        const_iterator(const SetChain<T>* s, size_t bIndex) : set(s), bucketIndex(bIndex)
                        {
                            advanceToNextValid();
                        }
                        const T& operator*() const
                        {
                            return *listIterator;
                        }
                        const_iterator& operator++()
                        {
                            ++listIterator;
                            if (listIterator == set->arr[bucketIndex].end())
                            {
                                ++bucketIndex;
                                advanceToNextValid();
                            }
                            return *this;
                        }
                        const_iterator operator++(int)
                        {
                            const_iterator temp = *this;
                            ++(*this);
                            return temp;
                        }
                        bool operator==(const const_iterator& other) const
                        {
                            return bucketIndex == other.bucketIndex && listIterator == other.listIterator;
                        }
                        bool operator!=(const const_iterator& other) const
                        {
                            return !(*this == other);
                        }       
                    };
                const_iterator begin() const
                {
                    return const_iterator(this, 0);
                }
                const_iterator end() const
                {
                    return const_iterator(this, capacity);
                }
    };
    template <class T>
    const size_t SetChain<T>::INITIAL_CAPACITY = 100;
}

#endif