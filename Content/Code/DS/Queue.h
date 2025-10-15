#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "Node.h"

using namespace std;
namespace dsc
{
    class StaticQueue
    {
        private:
            int* arr;
            int capacity;
            int front;
            int rear;
            int count;

        public:
            StaticQueue() : capacity(10), front(0), rear(-1), count(0)
            {
                arr = new int[capacity];
            }
            StaticQueue(int cap) : capacity(cap), front(0), rear(-1), count(0)
            {
                if (cap <= 0)
                {
                    throw invalid_argument("Size must be greater than 0");
                }
                arr = new int[capacity];
            }
            StaticQueue(const StaticQueue& obj) : capacity(obj.capacity), front(obj.front), rear(obj.rear), count(obj.count)
            {
                arr = new int[capacity];
                for (int i = 0; i < capacity; ++i)
                {
                    arr[i] = obj.arr[i];
                }
            }
            StaticQueue& operator=(const StaticQueue& rhs)
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    capacity = rhs.capacity;
                    front = rhs.front;
                    rear = rhs.rear;
                    count = rhs.count;
                    arr = new int[capacity];
                    for (int i = 0; i < capacity; ++i)
                    {
                        arr[i] = rhs.arr[i];
                    }
                }
                return *this;
            }

            ~StaticQueue()
            {
                delete[] arr;
            }

            void enqueue(int value)
            {
                if (count == capacity)
                {
                    throw overflow_error("Queue is full");
                }
                rear = (rear + 1) % capacity;
                arr[rear] = value;
                count++;
            }

            int dequeue()
            {
                if (count == 0)
                {
                    throw underflow_error("Queue is empty");
                }
                int value = arr[front];
                front = (front + 1) % capacity;
                count--;
                return value;
            }

            int peek() const
            {
                if (count == 0)
                {
                    throw underflow_error("Queue is empty");
                }
                return arr[front];
            }

            bool isEmpty() const
            {
                return count == 0;
            }

            bool isFull() const
            {
                return count == capacity;
            }

            int size() const
            {
                return count;
            }

            
    };
    class DynamicQueue
    {
        private:
            using Node = dsc::NodeD<int>;
            Node* front;
            Node* rear;
            int size;
        public:
            DynamicQueue() : front(nullptr), rear(nullptr), size(0) {}
            DynamicQueue(int value) : front(new Node(value)), rear(front), size(1) {}
            DynamicQueue(const DynamicQueue& obj) : front(nullptr), rear(nullptr), size(0)
            {
                Node* current = obj.front;
                while (current != nullptr)
                {
                    this->enqueue(current->data);
                    current = current->next;
                }
            }
            DynamicQueue& operator=(const DynamicQueue& rhs)
            {
                if (this != &rhs)
                {
                    this->~DynamicQueue();
                    front = nullptr;
                    rear = nullptr;
                    size = 0;
                    Node* current = rhs.front;
                    while (current != nullptr)
                    {
                        this->enqueue(current->data);
                        current = current->next;
                    }
                }
                return *this;
            }
            ~DynamicQueue()
            {
                while (!isEmpty())
                {
                    dequeue();
                }
            }
            void enqueue(int value)
            {
                Node* newNode = new Node(value);
                if (rear == nullptr)
                {
                    front = rear = newNode;
                }
                else
                {
                    rear->next = newNode;
                    newNode->prev = rear;
                    rear = newNode;
                }
                size++;
            }
            int dequeue()
            {
                if (isEmpty())
                {
                    throw underflow_error("Queue is empty");
                }
                Node* temp = front;
                int value = front->data;
                front = front->next;
                if (front != nullptr)
                {
                    front->prev = nullptr;
                }
                else
                {
                    rear = nullptr;
                }
                delete temp;
                size--;
                return value;
            }
            int peek() const
            {
                if (isEmpty())
                {
                    throw underflow_error("Queue is empty");
                }
                return front->data;
            }
            bool isEmpty() const
            {
                return size == 0;
            }
            int getSize() const
            {
                return size;
            }
    };
}

#endif