#include <iostream>
#include "Stack.h"

using namespace std;
using namespace dsc;

int main()
{
    DynamicStack stack1;

    stack1.push(73);
    stack1.push(54);
    stack1.push(37);
    cout << stack1.peek() << endl;
    stack1.pop();
    stack1.push(88);
    
    while(!stack1.isEmpty())
    {
        stack1.pop();
    }
    cout << stack1.getSize() << endl;
    // cout << stack1.peek() << endl;
    return 0;
}