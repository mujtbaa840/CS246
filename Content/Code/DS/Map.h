#ifndef MAP_H
#define MAP_H

#include "Hash.h"
#include "Pair.h"
#include "LinkedList.h"
#include "Object.h"
#include <stdexcept>

namespace dsc
{
    template <typename K, typename V>
    class MapOpen : public Object
    {
       private:
            Pair<K, V>** arr;
            size_t capacity;
            size_t count;
            static const size_t INITIAL_CAPACITY;
            static const Pair<K, V>* DELETED;

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
                Pair<K, V>** newArr = new Pair<K, V>*[newCapacity]{nullptr};
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (arr[i] != nullptr)
                    {
                        size_t index = Hash<K>()(arr[i]->getKey()) % newCapacity;
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
            MapOpen(const MapOpen<K, V>& obj) : capacity(obj.capacity), count(obj.count)
            {
                arr = new Pair<K, V>*[capacity]{nullptr};
                for (size_t i = 0; i < capacity; ++i)
                {
                    if (obj.arr[i] != nullptr)
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
                        if (obj.arr[i] != nullptr)
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
                size_t index = Hash<K>()(key) % capacity;
                while (arr[index] != nullptr)
                {
                    if (arr[index]->getKey() == key)
                    {
                        arr[index]->setValue(value);
                        return;
                    }
                    index = (index + 1) % capacity;
                }
                arr[index] = new Pair<K, V>(key, value);
                ++count;
            }
            const V& get(const K& key) const
            {
                size_t index = Hash<K>()(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index]->getKey() == key)
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
                size_t index = Hash<K>()(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index]->getKey() == key)
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
                size_t index = Hash<K>()(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index]->getKey() == key)
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
                    if (arr[i] != nullptr)
                    {
                        if (!first)
                        {
                            out << ", ";
                        }
                        out << *arr[i];
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
                return get(key);
            }

            void remove(const K& key)
            {
                size_t index = Hash<K>()(key) % capacity;
                size_t startIndex = index;
                while (arr[index] != nullptr)
                {
                    if (arr[index]->getKey() == key)
                    {
                        delete arr[index];
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
                
    };
    template <typename K, typename V>
    const size_t MapOpen<K, V>::INITIAL_CAPACITY = 100;
    
    template <typename K, typename V>
    const Pair<K, V>* MapOpen<K, V>::DELETED = nullptr;

    template <typename K, typename V>
    class MapChain : public Object
    {
        private:
            LinkedList<Pair<K, V>>* arr;
            size_t capacity;
            size_t count;
            static const size_t INITIAL_CAPACITY;

            void clear()
            {
                delete[] arr;
                arr = nullptr;
                capacity = 0;
                count = 0;
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
                size_t index = Hash<K>()(key) % capacity;
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
                size_t index = Hash<K>()(key) % capacity;
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
                size_t index = Hash<K>()(key) % capacity;
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
                size_t index = Hash<K>()(key) % capacity;
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
                            out << ",";
                        }
                        out << *it;
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
                return get(key);
            }
            void remove(const K& key)
            {
                size_t index = Hash<K>()(key) % capacity;
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
    };
    template <typename K, typename V>
    const size_t MapChain<K, V>::INITIAL_CAPACITY = 100;
}


#endif