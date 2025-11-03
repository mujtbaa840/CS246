#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <cstdint>

namespace dsc
{
    template <typename T>
    class Hash
    {
        public:
            size_t operator()(const T& key) const
            {
                return reinterpret_cast<size_t>(&key);
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
}


#endif