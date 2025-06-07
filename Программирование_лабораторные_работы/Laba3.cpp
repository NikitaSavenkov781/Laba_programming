#include <iostream>
#include <stack>
#include <locale.h>

using namespace std;

void printStack(stack<int> s) 
{
    stack<int> temp;

    while (!s.empty()) 
	{
        temp.push(s.top());
        s.pop();
    }
    while (!temp.empty())
	 {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

int main()
{
	setlocale(LC_ALL,"russian");
    stack<int> originalStack;

    // Заполняем стек
    originalStack.push(1);
    originalStack.push(2);
    originalStack.push(3);
    originalStack.push(4);
    originalStack.push(5);

    cout << "Исходный стек: ";
    printStack(originalStack);

    stack<int> doubledStack;


    stack<int> tempStack = originalStack; 
    while (!tempStack.empty()) {
        int val = tempStack.top();
        tempStack.pop();
        doubledStack.push(val * 2);
    }

    cout << "Преобразованный стек (элементы увеличены вдвое): ";
    printStack(doubledStack);

    return 0;
}

