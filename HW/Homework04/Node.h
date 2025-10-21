#ifndef NODE_H
#define NODE_H

namespace dshw
{
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
}
#endif