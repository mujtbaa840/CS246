#ifndef NODE_H
#define NODE_H

namespace dsc
{
    template <class T>
    class NodeS
    {
        public:
            T data;
            NodeS<T>* next;
            NodeS(const T& value) // : data(value), next(nullptr) {}
            {
                data = value;
                next = nullptr;
            }
    };

    template <class T>
    class NodeD
    {
        public:
            T data;
            NodeD<T>* next;
            NodeD<T>* prev;
            NodeD(const T& value) // : data(value), next(nullptr), prev(nullptr) {}
            {
                data = value;
                next = nullptr;
                prev = nullptr;
            }
    };

    template <class T>
    class NodeT
    {
        public:
            T data;
            NodeT<T>* left;
            NodeT<T>* right;
            NodeT(const T& value) // : data(value), left(nullptr), right(nullptr) {}
            {
                data = value;
                left = nullptr;
                right = nullptr;
            }
    };
}
#endif