#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>

using namespace std;

namespace DS
{
    class Object
    {
        public:
            virtual string toString() const = 0;
            virtual ~Object(){}

            friend ostream& operator<<(ostream& os, const Object& obj)
            {
                os << obj.toString();
                return os;
            }
    };
}



#endif