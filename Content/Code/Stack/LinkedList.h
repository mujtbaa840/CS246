#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"
#include "Object.h"

using namespace std;
using Node = dsc::NodeD<int>;

namespace dsc
{
    class LinkedList : public Object
    {
        private:
            Node* head;
            Node* tail;
            size_t size;

        public:
            LinkedList() : head(nullptr), tail(nullptr), size(0) {}
            LinkedList(const LinkedList& obj) : head(nullptr), tail(nullptr), size(0)
            {
                Node* current = obj.head;
                while (current != nullptr)
                {
                    this->insert(current->data);
                    current = current->next;
                }
            }
            LinkedList& operator=(const LinkedList& rhs)
            {
                if (this != &rhs)
                {
                    this->~LinkedList(); 
                    head = nullptr;
                    tail = nullptr;
                    size = 0;
                    Node* current = rhs.head;
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
                Node* current = head;
                while (current != nullptr)
                {
                    Node* nextNode = current->next;
                    delete current;
                    current = nextNode;
                }
                head = nullptr;
                tail = nullptr;
            }

            void insert(int value)
            {
                Node* newNode = new Node(value);
                if (head == nullptr)
                {
                    head = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                size++;
            }
            void insertFront(int value)
            {
                Node* newNode = new Node(value);
                newNode->next = head;
                if (head != nullptr)
                {
                    head->prev = newNode;
                }
                head = newNode;
                if (tail == nullptr)
                {
                    tail = newNode;
                }
                size++;
            }
            int pop()
            {
                if (tail == nullptr)
                {
                    throw out_of_range("List is empty");
                }
                Node* temp = tail;
                int value = tail->data;
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
                size--;
                return value;
            }

            int popFront()
            {
                if (head == nullptr)
                {
                    throw out_of_range("List is empty");
                }
                Node* temp = head;
                int value = head->data;
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
                size--;
                return value;
            }
            int remove(int value)
            {
                if (head == nullptr)
                {
                    throw out_of_range("List is empty");
                }
                Node* current = head;
                while (current != nullptr && current->data != value)
                {
                    current = current->next;
                }
                if (current == nullptr)
                {
                    throw invalid_argument("Value not found in the list");
                }
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
                size--;
                return value;
            }
            bool contains(int value) const
            {
                Node* current = head;
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
                Node* current = head;
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
                Node* prev = nullptr;
                Node* current = head;
                Node* next = nullptr;
                while (current != nullptr)
                {
                    next = current->next;
                    current->next = prev;
                    current->prev = next;
                    prev = current;
                    current = next;
                }
                tail = head;
                head = prev;
            }
    };        
}

#endif