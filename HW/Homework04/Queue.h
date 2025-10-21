#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include "Node.h"


namespace dshw
{
    template <class T>
    class StaticQueue
    {
        private:
            T* arr;
            size_t capacity;
            int front;
            int rear;
            size_t count;

            void swap(StaticQueue& other) noexcept
            {
                std::swap(arr, other.arr);
                std::swap(capacity, other.capacity);
                std::swap(front, other.front);
                std::swap(rear, other.rear);
                std::swap(count, other.count);
            }

        public:
            StaticQueue() : StaticQueue(100) {}
            StaticQueue(int cap) : capacity(cap), front(0), rear(-1), count(0)
            {
                if (cap <= 0)
                {
                    throw std::invalid_argument("Size must be greater than 0");
                }
                arr = new T[capacity];
            }
            StaticQueue(const StaticQueue<T>& obj) : capacity(obj.capacity), front(obj.front), rear(obj.rear), count(obj.count)
            {
                arr = new T[capacity];
                for (int i = 0; i < capacity; ++i)
                {
                    arr[i] = obj.arr[i];
                }
            }
            StaticQueue& operator=(const StaticQueue<T>& rhs)
            {
                if (this != &rhs)
                {
                    StaticQueue temp(rhs);
                    swap(temp);
                }
                return *this;
            }

            StaticQueue(StaticQueue<T>&& obj) noexcept : arr(obj.arr), capacity(obj.capacity), front(obj.front), rear(obj.rear), count(obj.count)
            {
                obj.arr = nullptr;
                obj.capacity = 0;
                obj.front = 0;
                obj.rear = -1;
                obj.count = 0;
            }
            StaticQueue<T>& operator=(StaticQueue<T>&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    delete[] arr;
                    arr = rhs.arr;
                    capacity = rhs.capacity;
                    front = rhs.front;
                    rear = rhs.rear;
                    count = rhs.count;
                    rhs.arr = nullptr;
                    rhs.capacity = 0;
                    rhs.front = 0;
                    rhs.rear = -1;
                    rhs.count = 0;
                }
                return *this;
            }

            ~StaticQueue()
            {
                delete[] arr;
            }

            void enqueue(const T& value)
            {
                if (count == capacity)
                {
                    throw std::overflow_error("Queue is full");
                }
                rear = (rear + 1) % capacity;
                arr[rear] = value;
                count++;
            }

            T dequeue()
            {
                if (count == 0)
                {
                    throw std::underflow_error("Queue is empty");
                }
                T value = arr[front];
                front = (front + 1) % capacity;
                count--;
                return value;
            }

            const T& peek() const
            {
                if (count == 0)
                {
                    throw std::underflow_error("Queue is empty");
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

            size_t size() const
            {
                return count;
            }

            
    };

    template <class T>
    class DynamicQueue
    {
        private:
            using Node = NodeD<T>;
            Node* front;
            Node* rear;
            int count;

            void swap(DynamicQueue& other) noexcept
            {
                std::swap(front, other.front);
                std::swap(rear, other.rear);
                std::swap(count, other.count);
            }

        public:
            DynamicQueue() : front(nullptr), rear(nullptr), count(0) {}
            DynamicQueue(const DynamicQueue<T>& obj) : front(nullptr), rear(nullptr), count(0)
            {
                Node* current = obj.front;
                while (current != nullptr)
                {
                    enqueue(current->data);
                    current = current->next;
                }
            }
            DynamicQueue<T>& operator=(const DynamicQueue<T>& rhs)
            {
                if (this != &rhs)
                {
                    DynamicQueue temp(rhs);
                    swap(temp);
                }
                return *this;
            }
            DynamicQueue(DynamicQueue<T>&& obj) noexcept : front(obj.front), rear(obj.rear), count(obj.count)
            {
                obj.front = nullptr;
                obj.rear = nullptr;
                obj.count = 0;
            }
            DynamicQueue<T>& operator=(DynamicQueue<T>&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    clear();
                    front = rhs.front;
                    rear = rhs.rear;
                    count = rhs.count;
                    rhs.front = nullptr;
                    rhs.rear = nullptr;
                    rhs.count = 0;
                }
                return *this;
            }
            ~DynamicQueue()
            {
                clear();
            }
            void clear()
            {
                while (!isEmpty())
                {
                    dequeue();
                }
            }
            void enqueue(const T& value)
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
                count++;
            }
            T dequeue()
            {
                if (isEmpty())
                {
                    throw std::underflow_error("Queue is empty");
                }
                Node* temp = front;
                T value = front->data;
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
                count--;
                return value;
            }
            const T& peek() const
            {
                if (isEmpty())
                {
                    throw std::underflow_error("Queue is empty");
                }
                return front->data;
            }
            bool isEmpty() const
            {
                return count == 0;
            }
            size_t size() const
            {
                return count;
            }
    };
}

#endif