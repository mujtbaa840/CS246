#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

using namespace std;

namespace dsc
{
    class Object
    {
        public:
            virtual string toString() const = 0;
            virtual ~Object(){}

            friend ostream& operator<<(ostream& out, const Object& obj)
            {
                out << obj.toString();
                return out;
            }
    };
}

#endif