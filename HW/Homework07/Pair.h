#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <string>
#include <sstream>
#include "Object.h"

namespace dshw
{
    template <typename K, typename V>
    class Pair : public Object
    {
        private:
            K key;
            V value;
        public:
            Pair() : key(), value() {}
            Pair(const K& k, const V& v) : key(k), value(v) {}
            Pair(const Pair<K, V>& obj) : key(obj.key), value(obj.value) {}
            Pair(Pair<K, V>&& obj) noexcept : key(std::move(obj.key)), value(std::move(obj.value)) {}
            Pair<K, V>& operator=(const Pair<K, V>& obj)
            {
                if (this != &obj)
                {
                    key = obj.key;
                    value = obj.value;
                }
                return *this;
            }
            Pair<K, V>& operator=(Pair<K, V>&& obj) noexcept
            {
                if (this != &obj)
                {
                    key = std::move(obj.key);
                    value = std::move(obj.value);
                }
                return *this;
            }
            ~Pair() override {}

            const K& getKey() const
            {
                return key;
            }

            const V& getValue() const
            {
                return value;
            }

            V& getValue()
            {
                return value;
            }

            void setValue(const V& v)
            {
                value = v;
            }

            std::string toString() const override
            {
                std::stringstream out;
                out << "(" << key << ", " << value << ")";
                return out.str();
            }

            bool operator==(const Pair<K, V>& other) const
            {
                return key == other.key && value == other.value;
            }

            bool operator!=(const Pair<K, V>& other) const
            {
                return !(*this == other);
            }
    };
}



#endif