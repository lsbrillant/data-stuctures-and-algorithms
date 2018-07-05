#include <iostream>
#include <stack>

using namespace std;

template <typename Object>
class MinStack : public stack<Object>
{
	public:
		MinStack() : stack<Object>() { 
			minStack = new stack<Object>();
		}

		void pop() {
			stack<Object>::pop();
			this->minStack->pop();
		}
		void push( const Object& val ) {
			stack<Object>::push(val);
			if(!this->minStack->empty()) {
				Object mintop = this->minStack->top();
				this->minStack->push((val < mintop) ? val : mintop);
			} else {
				this->minStack->push(val);
			}
		}
		Object getMin() {
			return this->minStack->top();
		}

	private:
		stack<Object> * minStack;
};

int main() {
	MinStack<int> * myStack = new MinStack<int>();
	cout << "push(5)" << endl;
	myStack->push(5);
	cout << "push(7)" << endl;
	myStack->push(7);
	cout << "push(6)" << endl;
	myStack->push(6);
	
	cout << "getMin()" << endl;
	cout << myStack->getMin() << endl;
	
	cout << "push(2)" << endl;
	myStack->push(2);
	
	cout << "getMin()" << endl;
	cout << myStack->getMin() << endl;
	
	cout << "pop()" << endl;
	myStack->pop();

	
	cout << "getMin()" << endl;
	cout << myStack->getMin() << endl;

	return EXIT_SUCCESS;
}
