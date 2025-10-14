#ifndef NODE_H
#define NODE_H

#include "Object.h"

namespace DS
{
    template <class T>
    class Node : public Object
    {
        public:
            T data;
            Node<T>* next;
            Node(T value) // : data(value), next(nullptr) {}
            {
                data = value;
                next = nullptr;
            }
    };
}

#endif 