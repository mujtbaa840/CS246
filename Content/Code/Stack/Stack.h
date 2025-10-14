#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

namespace dsc
{
    class StaticStack
    {
        private:
            int* arr;
            int capacity;
            int top;

        public:
            StaticStack() : capacity(10), top(-1)
            {
                arr = new int[capacity];
            }
            StaticStack(int cap) : capacity(cap), top(-1)
            {
                if (cap <= 0)
                {
                    throw invalid_argument("Size must be greater than 0");
                }
                arr = new int[capacity];
            }
            StaticStack(const StaticStack& obj) : capacity(obj.capacity), top(obj.top)
            {
                arr = new int[capacity];
                for (int i = 0; i <= top; ++i)
                {
                    arr[i] = obj.arr[i];
                }
            }
            StaticStack& operator=(const StaticStack& rhs)
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    capacity = rhs.capacity;
                    top = rhs.top;
                    arr = new int[capacity];
                    for (int i = 0; i <= top; ++i)
                    {
                        arr[i] = rhs.arr[i];
                    }
                }
                return *this;
            }

            ~StaticStack()
            {
                delete[] arr;
            }

            void push(int value)
            {
                if (top == capacity - 1)
                {
                    throw overflow_error("Stack overflow");
                }
                arr[++top] = value;
            }

            int pop()
            {
                if (isEmpty())
                {
                    throw underflow_error("Stack is empty");
                }
                return arr[top--];
            }

            int peek() const
            {
                if (isEmpty())
                {
                    throw underflow_error("Stack is empty");
                }
                return arr[top];
            }

            bool isEmpty() const
            {
                return top == -1;
            }

            int getSize() const
            {
                return top + 1;
            }
    };

    class DynamicStack
    {
        private:
            using Node = dsc::NodeD<int>;
            Node* top;
            int size;

        public:
            DynamicStack() : top(nullptr), size(0) {}
            DynamicStack(int value) : top(new Node(value)), size(1) {}
            DynamicStack(const DynamicStack& obj) : top(nullptr), size(0)
            {
                Node* current = obj.top;
                Node* prevNode = nullptr;
                while (current != nullptr)
                {
                    Node* newNode = new Node(current->data);
                    if (top == nullptr)
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
                }
                size = obj.size;
            }
            DynamicStack& operator=(const DynamicStack& rhs)
            {
                if (this != &rhs)
                {
                    this->~DynamicStack();
                    top = nullptr;
                    size = 0;
                    Node* current = rhs.top;
                    Node* prevNode = nullptr;
                    while (current != nullptr)
                    {
                        Node* newNode = new Node(current->data);
                        if (top == nullptr)
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
                    }
                    size = rhs.size;
                }
                return *this;
            }

            ~DynamicStack()
            {
                while (!isEmpty())
                {
                    pop();
                }
            }
            bool isEmpty() const
            {
                return size == 0;
            }
            int getSize() const
            {
                return size;
            }
            void push(int value)
            {
                Node* newNode = new Node(value);
                newNode->next = top;
                if (top != nullptr)
                {
                    top->prev = newNode;
                }
                top = newNode;
                size++;
            }

            int pop()
            {
                if (isEmpty())
                {
                    throw underflow_error("Stack is empty");
                }
                Node* temp = top;
                int value = top->data;
                top = top->next;
                if (top != nullptr)
                {
                    top->prev = nullptr;
                }
                delete temp;
                size--;
                return value;
            }
            int peek() const
            {
                if (isEmpty())
                {
                    throw underflow_error("Stack is empty");
                }
                return top->data;
            }

            int getSize() const
            {
                return size;
            }
    };
}

#endif