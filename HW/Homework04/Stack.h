#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

namespace dshw
{
    template <class T>
    class StaticStack
    {
        private:
            T* arr;
            int capacity;
            int count;

        public:
            StaticStack() : StaticStack(100) {}
            StaticStack(int size) : capacity(size), count(0)
            {
                if (size <= 0)
                {
                    throw invalid_argument("Size must be positive.");
                }
                arr = new T[size];
            }
            StaticStack(const StaticStack<T>& obj) : capacity(obj.capacity), count(obj.count)
            {
                arr = new T[capacity];
                for (int i = 0; i < count; i++)
                {
                    arr[i] = obj.arr[i];
                }
            }

            StaticStack<T>& operator=(const StaticStack<T>& rhs)
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    capacity = rhs.capacity;
                    count = rhs.count;
                    arr = new T[capacity];
                    for (int i = 0; i < count; i++)
                    {
                        arr[i] = rhs.arr[i];
                    }
                }
                return *this;
            }
            StaticStack(StaticStack<T>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), count(obj.count)
            {
                obj.arr = nullptr;
                obj.capacity = 0;
                obj.count = 0;
            }
            StaticStack<T>& operator=(StaticStack<T>&& rhs) noexcept
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
            ~StaticStack()
            {
                delete[] arr;
            }
            void push(const T& value)
            {
                if (count == capacity)
                {
                    throw overflow_error("Stack overflow. Cannot push to full stack.");
                }
                arr[count++] = value;
            }
            T pop()
            {
                if (isEmpty())
                {
                    throw runtime_error("Stack is empty. Cannot pop.");
                }
                return arr[--count];
            }
            T peek() const
            {
                if (isEmpty())
                {
                    throw runtime_error("Stack is empty. Cannot peek.");
                }
                return arr[count - 1];
            }
            bool isEmpty() const
            {
                return count == 0;
            }
            int size() const
            {
                return count;
            }
    };

    template <class T>
    class DynamicStack
    {
        private:
            NodeD<T>* top;
            int count;

        public:
            DynamicStack() : top(nullptr), count(0) {}
            DynamicStack(const DynamicStack<T>& obj) : top(nullptr), count(0)
            {
                if (obj.top == nullptr)
                {
                    return;
                }
                NodeD<T>* current = obj.top;
                NodeD<T>* prevNode = nullptr;
                while (current != nullptr)
                {
                    NodeD<T>* newNode = new NodeD<T>(current->data);
                    if (prevNode == nullptr)
                    {
                        top = newNode;
                    }
                    else
                    {
                        prevNode->next = newNode;
                        newNode->prev = prevNode;
                    }
                    prevNode = newNode;
                    current = current->next;
                    count++;
                }
            }
            
            DynamicStack<T>& operator=(const DynamicStack<T>& rhs)
            {
                if (this != &rhs)
                {
                    clear();
                    top = nullptr;
                    count = 0;
                    if (rhs.top == nullptr)
                    {
                        return *this;
                    }
                    NodeD<T>* current = rhs.top;
                    NodeD<T>* prevNode = nullptr;
                    while (current != nullptr)
                    {
                        NodeD<T>* newNode = new NodeD<T>(current->data);
                        if (prevNode == nullptr)
                        {
                            top = newNode;
                        }
                        else
                        {
                            prevNode->next = newNode;
                            newNode->prev = prevNode;
                        }
                        prevNode = newNode;
                        current = current->next;
                        count++;
                    }
                }
                return *this;
            }
            DynamicStack(DynamicStack<T>&& obj) noexcept : top(obj.top), count(obj.count)
            {
                obj.top = nullptr;
                obj.count = 0;
            }
            DynamicStack<T>& operator=(DynamicStack<T>&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    clear();
                    top = rhs.top;
                    count = rhs.count;
                    rhs.top = nullptr;
                    rhs.count = 0;
                }
                return *this;
            }

            ~DynamicStack()
            {
                clear();
            }

            void clear()
            {
                while (!isEmpty())
                {
                    pop();
                }
            }

            void push(const T& value)
            {
                NodeD<T>* newNode = new NodeD<T>(value);
                newNode->next = top;
                if (top != nullptr)
                {
                    top->prev = newNode;
                }
                top = newNode;
                count++;
            }
            T pop()
            {
                if (isEmpty())
                {
                    throw runtime_error("Stack is empty. Cannot pop.");
                }
                NodeD<T>* temp = top;
                T value = top->data;
                top = top->next;
                if (top != nullptr)
                {
                    top->prev = nullptr;
                }
                delete temp;
                count--;
                return value;
            }
            const T& peek() const
            {
                if (isEmpty())
                {
                    throw runtime_error("Stack is empty. Cannot peek.");
                }
                return top->data;
            }
            bool isEmpty() const
            {
                return top == nullptr;
            }
            int size() const
            {
                return count;
            }
    };
}

#endif