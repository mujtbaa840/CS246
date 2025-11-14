#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <cstdint>
#include "Pair.h"

namespace dshw
{
    template <typename T>
    class Hash
    {
    public:
        size_t operator()(const T& key) const
        {
            const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
            size_t hash = 0;
            for (size_t i = 0; i < sizeof(T); ++i)
            {
                hash = hash * 131 + data[i]; // 131 is a common prime multiplier
            }
            return hash;
        }
    };

    template <>
    class Hash<int>
    {
        public:
            size_t operator()(const int& key) const
            {
                return static_cast<size_t>(key);
            }
    };

    template <>
    class Hash<char>
    {
        public:
            size_t operator()(const char& key) const
            {
                return static_cast<size_t>(key);
            }
    };

    template <>
    class Hash<std::string>
    {
        public:
            size_t operator()(const std::string& key) const
            {
                size_t hash = 0;
                for (char c : key)
                {
                    hash = hash * 31 + static_cast<size_t>(c);
                }
                return hash;
            }
    };

    template <typename T>
    class Hash<T*>
    {
        public:
            size_t operator()(T* const& key) const
            {
                return reinterpret_cast<size_t>(key);
            }
    };

    template <>
    class Hash<char*>
    {
        public:
            size_t operator()(const char* key) const
            {
                size_t hash = 0;
                for (const char* ptr = key; *ptr != '\0'; ++ptr)
                {
                    hash = hash * 31 + static_cast<size_t>(*ptr);
                }
                return hash;
            }
    };

    template <>
    class Hash<bool>
    {
        public:
            size_t operator()(const bool& key) const
            {
                return key ? 1u : 0u;
            }
    };

    template <typename K, typename V>
    class Hash<Pair<K,V>>
    {
    public:
        size_t operator()(const Pair<K,V>& p) const
        {
            Hash<K> hashK;
            Hash<V> hashV;

            size_t h1 = hashK(p.getKey());
            size_t h2 = hashV(p.getValue());
            
            return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
        }
    };
}


#endif