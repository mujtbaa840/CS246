#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

namespace dsl
{
    template <typename T>
    void Swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    void printVector(const std::vector<T>& vec)
    {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i];
            if (i < vec.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    template <typename T>
    void printLinkedList(NodeD<T>* head)
    {
        NodeD<T>* current = head;
        while (current != nullptr)
        {
            if (current != head)
            {
                std::cout << " -> ";
            }
            std::cout << current->data;
            current = current->next;
        }
        std::cout << std::endl;
    }

    template <typename T>
    NodeD<T>* loadList(const std::vector<T>& arr)
    {
        if (arr.empty())
        {
            return nullptr;
        }
        NodeD<T>* head = new Node<T>(arr[0]);
        NodeD<T>* current = head;
        for (size_t i = 1; i < arr.size(); i++)
        {
            current->next = new Node<T>(arr[i]);
            current->next->prev = current;
            current = current->next;
        }
        return head;
    }

    template <typename T>
    void clear(NodeD<T>* head)
    {
        while (head != nullptr)
        {
            NodeD<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
}



#endif