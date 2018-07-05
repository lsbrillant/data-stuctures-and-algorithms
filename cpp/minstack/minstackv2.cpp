#include <iostream>
#include <stack>

using namespace std;

class MinStack : public stack<int>
{
	public:
		MinStack() : stack<int>() { 
}
		void pop() {
			int top = stack<int>::top();
			stack<int>::pop();
			if( top < 0 ) {
				this->min = this->min - top;
			}	
		}
		void push( const int& val ) {
			if(stack<int>::empty()) {
				stack<int>::push(0); 
				min = val;
			} else {
				stack<int>::push( val - this->min );
				if( val < min ) this->min = val;
			}
		}
		int top(){
			int top = stack<int>::top();
			return (top < 0 )? min : (top + this->min);
		}
		int getMin() {
			return this->min;
		}
	private:
		int min;

};

int main() {
	MinStack * myStack = new MinStack();
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
