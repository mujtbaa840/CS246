#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <sstream>

namespace dshw
{
    template <class T>
    class LinkedList : public Object
    {
        private:
            Node<T>* head;
            size_t size; 

        public:
            LinkedList() : head(nullptr), size(0) {}
            LinkedList(const LinkedList<T>& obj) : head(nullptr), size(0)
            {
                Node<T>* current = obj.head;
                while (current != nullptr)
                {
                    this->insert(current->data);
                    current = current->next;
                }
            }
            LinkedList<T>& operator=(const LinkedList<T>& rhs)
            {
                if (this != &rhs)
                {
                    this->~LinkedList(); 
                    head = nullptr;
                    size = 0;
                    Node<T>* current = rhs.head;
                    while (current != nullptr)
                    {
                        this->insert(current->data);
                        current = current->next;
                    }
                }
                return *this;
            }
            ~LinkedList() override
            {
                Node<T>* current = head;
                while (current != nullptr)
                {
                    Node<T>* nextNode = current->next;
                    delete current;
                    current = nextNode;
                }
                head = nullptr;
            }
            void insert(T value)
            {
                Node<T>* newNode = new Node<T>(value);
                if (head == nullptr)
                {
                    head = newNode;
                }
                else
                {
                    Node<T>* current = head;
                    while (current->next != nullptr)
                    {
                        current = current->next;
                    }
                    current->next = newNode;
                }
                size++;
            }

            void insertFront(T value)
            {
                Node<T>* newNode = new Node<T>(value);
                newNode->next = head;
                head = newNode;
                size++;
            }

            bool remove(T value)
            {
                if (head == nullptr)
                {
                    return false;
                }

                if (head->data == value)
                {
                    Node<T>* temp = head;
                    head = head->next;
                    delete temp;
                    size--;
                    return true;
                }

                Node<T>* current = head;
                while (current->next != nullptr && current->next->data != value)
                {
                    current = current->next;
                }

                if (current->next == nullptr)
                {
                    return false;
                }

                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
                return true;
            }

            T pop()
            {
                if (head == nullptr)
                {
                    throw runtime_error("List is empty");
                }

                Node<T>* current = head;
                if (current->next == nullptr)
                {
                    T value = current->data;
                    delete current;
                    head = nullptr;
                    size--;
                    return value;
                }
                while (current->next->next != nullptr)
                {
                    current = current->next;
                }
                T value = current->next->data;
                delete current->next;
                current->next = nullptr;
                size--;
                return value;
            }

            T popFront()
            {
                if (head == nullptr)
                {
                    throw runtime_error("List is empty");
                }
                Node<T>* temp = head;
                T value = head->data;
                head = head->next;
                delete temp;
                size--;
                return value;
            }

            bool contains(T value) const
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

            size_t getSize() const
            {
                return size;
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

            void reverse()
            {
                Node<T>* prev = nullptr;
                Node<T>* current = head;
                Node<T>* next = nullptr;
                while (current != nullptr)
                {
                    next = current->next;
                    current->next = prev;
                    prev = current;
                    current = next;
                }
                head = prev;
            }   
    };
}



#endif