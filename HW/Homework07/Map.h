#ifndef MAP_H
#define MAP_H

#include "Hash.h"
#include "Pair.h"
#include "LinkedList.h"
#include "Object.h"
#include <stdexcept>

namespace dshw
{
    template <typename K, typename V>
    class MapOpen : public Object
    {
       private:
            Pair<K, V>** arr;
            size_t capacity;
            size_t count;
            Hash<K> hashFunc;
            static const size_t INITIAL_CAPACITY;
            static Pair<K, V>* DELETED;
            

            void clear()
            {
                if (arr != nullptr)
                {
                    for (size_t i = 0; i < capacity; ++i)
                    {
                        if (arr[i] != nullptr && arr[i] != DELETED)
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
            }

            void resize()
            {
                size_t newCapacity = capacity * 2;
                Pair<K, V>** newArr = new Pair<K, V>*[newCapacity]{nullptr};
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr && arr[i] != DELETED)
                    {
                        size_t index = hashFunc(arr[i]->getKey()) % newCapacity;
                        while (newArr[index] != nullptr)
                        {
                            index = (index + 1) % newCapacity;
                        }
                        newArr[index] = arr[i];
                    }
                }
                delete[] arr;
                arr = newArr;
                capacity = newCapacity;
            }

        public:
            MapOpen() : MapOpen(INITIAL_CAPACITY) {}
            MapOpen(size_t cap) : capacity(cap), count(0)
            {
                if (capacity == 0)
                {
                    throw invalid_argument("Capacity must be greater than 0");
                }
                arr = new Pair<K, V>*[capacity]{nullptr};
            }

            MapOpen(std::initializer_list<Pair<K, V>> initList) : MapOpen(std::max(INITIAL_CAPACITY, initList.size()))
            {
                for (const Pair<K, V>& p : initList)
                {
                    put(p.getKey(), p.getValue());
                }
            }

            MapOpen<K, V>& operator=(std::initializer_list<Pair<K, V>> initList)
            {
                clear();
                capacity = std::max(INITIAL_CAPACITY, initList.size());
                count = 0;
                arr = new Pair<K, V>*[capacity]{nullptr};
                for (const Pair<K, V>& p : initList)
                {
                    put(p.getKey(), p.getValue());
                }
                return *this;
            }

            MapOpen(const MapOpen<K, V>& obj) : capacity(obj.capacity), count(obj.count)
            {
                arr = new Pair<K, V>*[capacity]{nullptr};
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (obj.arr[i] == nullptr)
                    {
                        arr[i] = nullptr;
                    }
                    else if (obj.arr[i] == MapOpen<K, V>::DELETED)
                    {
                        arr[i] = MapOpen<K, V>::DELETED;
                    }
                    else
                    {
                        arr[i] = new Pair<K, V>(*(obj.arr[i]));
                    }
                }
            }
            MapOpen(MapOpen<K, V>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), count(obj.count)
            {
                obj.arr = nullptr;
                obj.capacity = 0;
                obj.count = 0;
            }
            MapOpen<K, V>& operator=(const MapOpen<K, V>& obj)
            {
                if (this != &obj)
                {
                    clear();
                    capacity = obj.capacity;
                    count = obj.count;
                    arr = new Pair<K, V>*[capacity]{nullptr};
                    for (size_t i = 0; i < capacity; ++i)
                    {
                        if (obj.arr[i] == nullptr)
                        {
                            arr[i] = nullptr;
                        }
                        else if (obj.arr[i] == MapOpen<K, V>::DELETED)
                        {
                            arr[i] = MapOpen<K, V>::DELETED;
                        }
                        else
                        {
                            arr[i] = new Pair<K, V>(*(obj.arr[i]));
                        }
                    }
                }
                return *this;
            }
            MapOpen<K, V>& operator=(MapOpen<K, V>&& obj) noexcept
            {
                if (this != &obj)
                {
                    clear();
                    capacity = obj.capacity;
                    count = obj.count;
                    arr = obj.arr;;
                    obj.arr = nullptr;
                    obj.capacity = 0;
                    obj.count = 0;
                }
                return *this;
            }
            ~MapOpen() override
            {
                clear();
            }

            void put(const K& key, const V& value)
            {
                if (count == capacity)
                {
                    resize();
                }
                size_t firstDeleted = capacity;
                size_t index = hashFunc(key) % capacity;
                while (arr[index] != nullptr)
                {
                    if (arr[index] != DELETED && arr[index]->getKey() == key)
                    {
                        arr[index]->setValue(value);
                        return;
                    }
                    if (arr[index] == DELETED && firstDeleted == capacity)
                    {
                        firstDeleted = index;
                    }
                    index = (index + 1) % capacity;
                }
                if (firstDeleted != capacity)
                {
                    index = firstDeleted;
                }
                arr[index] = new Pair<K, V>(key, value);
                ++count;
            }
            const V& get(const K& key) const
            {
                size_t index = hashFunc(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index] != DELETED && arr[index]->getKey() == key)
                    {
                        return arr[index]->getValue();
                    }
                    index = (index + 1) % capacity;
                    if (index == startIndex)
                    {
                        break;
                    }
                }
                throw out_of_range("Key not found in MapOpen");
            }

            V& get(const K& key)
            {
                size_t index = hashFunc(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index] != DELETED && arr[index]->getKey() == key)
                    {
                        return arr[index]->getValue();
                    }
                    index = (index + 1) % capacity;
                    if (index == startIndex)
                    {
                        break;
                    }
                }
                throw out_of_range("Key not found in MapOpen");
            }

            bool contains(const K& key) const
            {   
                size_t index = hashFunc(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index] != DELETED && arr[index]->getKey() == key)
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
            bool isEmpty() const
            {
                return count == 0;
            }
            std::string toString() const override
            {
                std::stringstream out;
                out << "{";
                bool first = true;
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr && arr[i] != DELETED)
                    {
                        if (!first)
                        {
                            out << ", ";
                        }
                        out << arr[i]->getKey() << ": " << arr[i]->getValue();
                        first = false;
                    }
                }
                out << "}";
                return out.str();    
            }

            const V& operator[](const K& key) const
            {
                return get(key);
            }

            V& operator[](const K& key)
            {
                if (!contains(key))
                {
                    put(key, V());
                }
                return get(key);
            }

            void remove(const K& key)
            {
                size_t index = hashFunc(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index] != DELETED && arr[index]->getKey() == key)
                    {
                        arr[index] = DELETED;
                        --count;
                        return;
                    }
                    index = (index + 1) % capacity;
                    if (index == startIndex)
                    {
                        break;
                    }
                }
                throw out_of_range("Key not found in Map");
            }

            bool operator==(const MapOpen<K, V>& other) const
            {
                if (count != other.count)
                {
                    return false;
                }
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr && arr[i] != DELETED)
                    {
                        if (!other.contains(arr[i]->getKey()) || other.get(arr[i]->getKey()) != arr[i]->getValue())
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
            bool operator!=(const MapOpen<K, V>& other) const
            {
                return !(*this == other);
            }

            class iterator
            {
                private:
                    Pair<K, V>** arr;
                    size_t capacity;
                    size_t index;
                    void skipToNext()
                    {
                        while (index < capacity && (arr[index] == nullptr || arr[index] == DELETED))
                        {
                            ++index;
                        }
                    }
                public:
                    iterator(Pair<K, V>** array, size_t cap, size_t idx) : arr(array), capacity(cap), index(idx)
                    {
                        skipToNext();
                    }
                    Pair<K, V>& operator*() const
                    {
                        return *arr[index];
                    }
                    iterator& operator++()
                    {
                        ++index;
                        skipToNext();
                        return *this;
                    }
                    iterator operator++(int)
                    {
                        iterator temp = *this;
                        ++(*this);
                        return temp;
                    }
                    bool operator==(const iterator& other) const
                    {
                        return index == other.index;
                    }
                    bool operator!=(const iterator& other) const
                    {
                        return index != other.index;
                    }
            };
            iterator begin()
            {
                return iterator(arr, capacity, 0);
            }
            iterator end()
            {
                return iterator(arr, capacity, capacity);
            }

            class const_iterator
            {
                private:
                    Pair<K, V>** arr;
                    size_t capacity;
                    size_t index;
                    void skipToNext()
                    {
                        while (index < capacity && (arr[index] == nullptr || arr[index] == DELETED))
                        {
                            ++index;
                        }
                    }
                public:
                    const_iterator(Pair<K, V>** array, size_t cap, size_t idx) : arr(array), capacity(cap), index(idx)
                    {
                        skipToNext();
                    }
                    const Pair<K, V>& operator*() const
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
    template <typename K, typename V>
    const size_t MapOpen<K, V>::INITIAL_CAPACITY = 100;
    
    template <typename K, typename V>
    Pair<K, V>* MapOpen<K, V>::DELETED = new Pair<K, V>(K(), V());

    template <typename K, typename V>
    class MapChain : public Object
    {
        private:
            LinkedList<Pair<K, V>>* arr;
            size_t capacity;
            size_t count;
            Hash<K> hashFunc;
            static const size_t INITIAL_CAPACITY;

            void clear()
            {
                delete[] arr;
                arr = nullptr;
                capacity = 0;
                count = 0;
            }

            void resize()
            {
                size_t newCapacity = capacity * 2;
                LinkedList<Pair<K, V>>* newArr = new LinkedList<Pair<K, V>>[newCapacity];

                for (size_t i = 0; i < capacity; ++i)
                {
                    for (const Pair<K, V>& pair : arr[i])
                    {
                        size_t index = hashFunc(pair.getKey()) % newCapacity;
                        newArr[index].insert(pair);
                    }
                }
                delete[] arr;
                arr = newArr;
                capacity = newCapacity;
            }

        public:
            MapChain() : MapChain(INITIAL_CAPACITY) {}
            MapChain(size_t cap) : capacity(cap), count(0)
            {
                if (capacity == 0)
                {
                    throw invalid_argument("Capacity must be greater than 0");
                }
                arr = new LinkedList<Pair<K, V>>[capacity];
            }

            MapChain(std::initializer_list<Pair<K, V>> initList) : MapChain(std::max(INITIAL_CAPACITY, initList.size()))
            {
                for (const Pair<K, V>& p : initList)
                {
                    put(p.getKey(), p.getValue());
                }
            }

            MapChain<K, V>& operator=(std::initializer_list<Pair<K, V>> initList)
            {
                clear();
                capacity = std::max(INITIAL_CAPACITY, initList.size());
                count = 0;
                arr = new LinkedList<Pair<K, V>>[capacity];
                for (const Pair<K, V>& p : initList)
                {
                    put(p.getKey(), p.getValue());
                }
                return *this;
            }

            MapChain(const MapChain<K, V>& obj) : capacity(obj.capacity), count(obj.count)
            {
                arr = new LinkedList<Pair<K, V>>[capacity];
                for (size_t i = 0; i < capacity; ++i)
                {
                    arr[i] = obj.arr[i];
                }
            }
            MapChain(MapChain<K, V>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), count(obj.count)
            {
                obj.arr = nullptr;
                obj.capacity = 0;
                obj.count = 0;
            }
            MapChain<K, V>& operator=(const MapChain<K, V>& obj)
            {
                if (this != &obj)
                {
                    clear();
                    capacity = obj.capacity;
                    count = obj.count;
                    arr = new LinkedList<Pair<K, V>>[capacity];
                    for (size_t i = 0; i < capacity; ++i)
                    {
                        arr[i] = obj.arr[i];
                    }
                }
                return *this;
            }
            MapChain<K, V>& operator=(MapChain<K, V>&& obj) noexcept
            {
                if (this != &obj)
                {
                    clear();
                    capacity = obj.capacity;
                    count = obj.count;
                    arr = obj.arr;;
                    obj.arr = nullptr;
                    obj.capacity = 0;
                    obj.count = 0;
                }
                return *this;
            }
            ~MapChain() override
            {
                clear();
            }
            void put(const K& key, const V& value)
            {
                if (count == capacity)
                {
                    resize();
                }
                size_t index = hashFunc(key) % capacity;
                for (auto& pair : arr[index])
                {
                    if (pair.getKey() == key)
                    {
                        pair.setValue(value);
                        return;
                    }
                }
                arr[index].insert(Pair<K, V>(key, value));
                ++count;
            }
            const V& get(const K& key) const
            {
                size_t index = hashFunc(key) % capacity;
                for (auto& pair : arr[index])
                {
                    if (pair.getKey() == key)
                    {
                        return pair.getValue();
                    }
                }
                throw out_of_range("Key not found in MapChain");
            }
            V& get(const K& key)
            {
                size_t index = hashFunc(key) % capacity;
                for (auto& pair : arr[index])
                {
                    if (pair.getKey() == key)
                    {
                        return pair.getValue();
                    }
                }
                throw out_of_range("Key not found in MapChain");
            }
            bool contains(const K& key) const
            {
                size_t index = hashFunc(key) % capacity;
                for (const auto& pair : arr[index])
                {
                    if (pair.getKey() == key)
                    {
                        return true;
                    }
                }
                return false;
            }
            size_t size() const
            {
                return count;
            }
            bool isEmpty() const
            {
                return count == 0;
            }
            std::string toString() const override
            {
                std::stringstream out;
                out << "{";
                bool first = true;
                for (size_t i = 0; i < capacity; ++i)
                {
                    for (auto it = arr[i].begin(); it != arr[i].end(); ++it)
                    {
                        if (!first)
                        {
                            out << ", ";
                        }
                        out << (*it).getKey() << ": " << (*it).getValue();
                        first = false;
                    }
                }
                out << "}";    
                return out.str();
            }
            const V& operator[](const K& key) const
            {
                return get(key);
            }
            V& operator[](const K& key)
            {
                if (!contains(key))
                {
                    put(key, V());
                }
                return get(key);
            }
            void remove(const K& key)
            {
                size_t index = hashFunc(key) % capacity;
                for (auto& pair : arr[index])
                {
                    if (pair.getKey() == key)
                    {
                        arr[index].remove(pair);
                        --count;
                        return;
                    }
                }
                throw out_of_range("Key not found in MapChain");
            }

            bool operator==(const MapChain<K, V>& other) const
            {
                if (count != other.count)
                {
                    return false;
                }
                for (size_t i = 0; i < capacity; ++i)
                {
                    for (const auto& pair : arr[i])
                    {
                        if (!other.contains(pair.getKey()) || other.get(pair.getKey()) != pair.getValue())
                        {
                            return false;
                        }
                    }
                }
                return true;
            }

            bool operator!=(const MapChain<K, V>& other) const
            {
                return !(*this == other);
            }

            class iterator
            {
                private:
                    LinkedList<Pair<K, V>>* arr;
                    size_t capacity;
                    size_t listIndex;
                    typename LinkedList<Pair<K, V>>::iterator listIt;
                    void advanceToNextValid()
                    {
                        while (listIndex < capacity && listIt == arr[listIndex].end())
                        {
                            ++listIndex;
                            if (listIndex < capacity)
                            {
                                listIt = arr[listIndex].begin();
                            }
                        }
                    }
                public:
                    iterator(LinkedList<Pair<K, V>>* array, size_t cap, size_t lIndex) : arr(array), capacity(cap), listIndex(lIndex)
                    {
                        if (listIndex < capacity)
                        {
                            listIt = arr[listIndex].begin();
                        }
                        advanceToNextValid();
                    }
                    Pair<K, V>& operator*()
                    {
                        return *listIt;
                    }
                    iterator& operator++()
                    {
                        ++listIt;
                        advanceToNextValid();
                        return *this;
                    }
                    iterator operator++(int)
                    {
                        iterator temp = *this;
                        ++(*this);
                        return temp;
                    }
                    bool operator==(const iterator& other) const
                    {
                        return listIndex == other.listIndex && listIt == other.listIt;
                    }
                    bool operator!=(const iterator& other) const
                    {
                        return !(*this == other);
                    }
            };
            iterator begin()
            {
                return iterator(arr, capacity, 0);
            }
            iterator end()
            {
                return iterator(arr, capacity, capacity);
            }

            class const_iterator
            {
                private:
                    const LinkedList<Pair<K, V>>* arr;
                    size_t capacity;
                    size_t listIndex;
                    typename LinkedList<Pair<K, V>>::const_iterator listIt;
                    void advanceToNextValid()
                    {
                        while (listIndex < capacity && listIt == arr[listIndex].end())
                        {
                            ++listIndex;
                            if (listIndex < capacity)
                            {
                                listIt = arr[listIndex].begin();
                            }
                        }
                    }
                public:
                    const_iterator(const LinkedList<Pair<K, V>>* array, size_t cap, size_t lIndex) : arr(array), capacity(cap), listIndex(lIndex)
                    {
                        if (listIndex < capacity)
                        {
                            listIt = arr[listIndex].begin();
                        }
                        advanceToNextValid();
                    }
                    const Pair<K, V>& operator*() const
                    {
                        return *listIt;
                    }
                    const_iterator& operator++()
                    {
                        ++listIt;
                        advanceToNextValid();
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
                        return listIndex == other.listIndex && listIt == other.listIt;
                    }
                    bool operator!=(const const_iterator& other) const
                    {
                        return !(*this == other);
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
    template <typename K, typename V>
    const size_t MapChain<K, V>::INITIAL_CAPACITY = 100;
}


#endif