#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "Object.h"
#include <sstream>

template <class T>
using Node = dshw::NodeD<T>;

namespace dshw
{
    template <class T>
    class LinkedList : public Object
    {
        private:
            Node<T>* head;
            Node<T>* tail;
            size_t count;

            void clear()
            {
                Node<T>* current = head;
                while (current != nullptr)
                {
                    Node<T>* nextNode = current->next;
                    delete current;
                    current = nextNode;
                }
                head = nullptr;
                tail = nullptr;
                count = 0;
            }

        public:
            LinkedList() : head(nullptr), tail(nullptr), count(0) {}
            LinkedList(const LinkedList<T>& obj) : head(nullptr), tail(nullptr), count(0)
            {
                Node<T>* current = obj.head;
                while (current != nullptr)
                {
                    this->insert(current->data);
                    current = current->next;
                }
            }
            LinkedList(LinkedList<T>&& obj) noexcept : head(obj.head), tail(obj.tail), count(obj.count)
            {
                obj.head = nullptr;
                obj.tail = nullptr;
                obj.count = 0;
            }

            LinkedList<T>& operator=(const LinkedList<T>& rhs)
            {
                if (this != &rhs)
                {
                    clear();
                    Node<T>* current = rhs.head;
                    while (current != nullptr)
                    {
                        insert(current->data);
                        current = current->next;
                    }
                }
                return *this;
            }
            LinkedList<T>& operator=(LinkedList<T>&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    clear();
                    head = rhs.head;
                    tail = rhs.tail;
                    count = rhs.count;
                    rhs.head = nullptr;
                    rhs.tail = nullptr;
                    rhs.count = 0;
                }
                return *this;
            }

            ~LinkedList() override
            {
                clear();
            }
            void insert(const T& value)
            {
                Node<T>* newNode = new Node<T>(value);
                if (tail == nullptr)
                {
                    head = tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                count++;
            }

            void insertFront(const T& value)
            {
                Node<T>* newNode = new Node<T>(value);
                if (head == nullptr)
                {
                    head = tail = newNode;
                }
                else
                {
                    newNode->next = head;
                    head->prev = newNode;
                    head = newNode;
                }
                count++;
            }

            void remove(const T& value)
            {
                Node<T>* current = head;
                while (current != nullptr)
                {
                    if (current->data == value)
                    {
                        if (current->prev != nullptr)
                        {
                            current->prev->next = current->next;
                        }
                        else
                        {
                            head = current->next;
                        }
                        if (current->next != nullptr)
                        {
                            current->next->prev = current->prev;
                        }
                        else
                        {
                            tail = current->prev;
                        }
                        delete current;
                        count--;
                        return;
                    }
                    current = current->next;
                }
            }

            T& pop()
            {
                if (tail == nullptr)
                {
                    throw runtime_error("List is empty");
                }
                Node<T>* temp = tail;
                T value = tail->data;
                tail = tail->prev;
                if (tail != nullptr)
                {
                    tail->next = nullptr;
                }
                else
                {
                    head = nullptr;
                }
                delete temp;
                count--;
                return value;
            }

            T& popFront()
            {
                if (head == nullptr)
                {
                    throw runtime_error("List is empty");
                }
                Node<T>* temp = head;
                T value = head->data;
                head = head->next;
                if (head != nullptr)
                {
                    head->prev = nullptr;
                }
                else
                {
                    tail = nullptr;
                }
                delete temp;
                count--;
                return value;
            }

            bool contains(const T& value) const
            {
                Node<T>* current = head;
                while (current != nullptr)
                {
                    if (current->data == value)
                    {
                        return true;
                    }
                    current = current->next;
                }
                return false;
            }

            size_t size() const
            {
                return count;
            }

            string toString() const override
            {
                stringstream out;
                out << "[";
                Node<T>* current = head;
                while (current != nullptr)
                {
                    out << current->data;
                    if (current->next != nullptr)
                    {
                        out << ",";
                    }
                    current = current->next;
                }
                out << "]";
                return out.str();    
            }

            class const_iterator
            {
                private:
                    Node<T>* current;
                public:
                    const_iterator(Node<T>* start) : current(start) {}
                    const T& operator*() const
                    {
                        return current->data;
                    }
                    const_iterator& operator++()
                    {
                        if (current != nullptr)
                        {
                            current = current->next;
                        }
                        return *this;
                    }
                    const_iterator operator++(int)
                    {
                        const_iterator temp = *this;
                        ++(*this);
                        return temp;
                    }
                    bool operator==(const const_iterator& other) const
                    {
                        return current == other.current;
                    }
                    bool operator!=(const const_iterator& other) const
                    {
                        return current != other.current;
                    }
            };

            const_iterator begin() const
            {
                return const_iterator(head);
            }
            const_iterator end() const
            {
                return const_iterator(nullptr);
            }
  
    };
}



#endif