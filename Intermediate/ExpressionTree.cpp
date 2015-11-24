//Help from https://gist.github.com/mycodeschool/7867739

#include <iostream>
#include <string>
#include <stack>
#include <windows.h>

using namespace std;

struct node {
	int info;
	node *left, *right;
};

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int whereX() {
	CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
	return consoleinfo.dwCursorPosition.X;
}

int whereY() {
	CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
	return consoleinfo.dwCursorPosition.Y;
}

bool isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
		return true;
	}
	return false;
}

bool isOperand(char ch) {
	if (ch >= '0' && ch <= '9') return true;
	if (ch >= 'a' && ch <= 'z') return true;
	return false;
}

int GetOperatorWeight(char op) {
	int weight = -1;
	switch (op)
	{
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
		weight = 2;
	}
	return weight;
}

int HasHigherPrecedence(char op1, char op2) {
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if (op1Weight == op2Weight)
	{
		return true;
	}
	return op1Weight > op2Weight ? true : false;
}

float applyOperator(float a, float b, int ch) {
	if (ch == '+') return a + b;
	else if (ch == '-') return a + b;
	else if (ch == '*') return a*b;
	else if (ch == '/') return a / b;

}

float postfixToFloat(string postfix) {
	stack<int> myStack;
	for (int i = 0; i < postfix.size(); i++) {
		if (isOperand(postfix[i])){
			//cout << "Push: " << postfix[i] << endl;
			myStack.push(postfix[i] - 48);
		}
		else {
			int a = myStack.top();
			myStack.pop();
			int b = myStack.top();
			myStack.pop();
			cout << "a: " << a << endl;
			cout << "b: " << b << endl;

			int c = applyOperator(a, b, postfix[i]);
			cout << "c: " << c << endl;

			myStack.push(c);
		}
	}
	cout << myStack.top();
	return 0;
}

string Exp2PostFix(string exp) {
	std::stack<int> myStack;
	string postfix = "";

	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == ' ') continue;

		if (isOperand(exp[i])) {
			postfix += exp[i];
		}
		else if (isOperator(exp[i])){
			while (!myStack.empty() && myStack.top() != '(' && HasHigherPrecedence(myStack.top(), exp[i]))
			{
				postfix += myStack.top();
				myStack.pop();
			}
			myStack.push(exp[i]);
		}
		else if (exp[i] == '(') {
			myStack.push(exp[i]);
		}
		else if (exp[i] == ')') {
			while (!myStack.empty() && myStack.top() != '(') {
				postfix += myStack.top();
				myStack.pop();
			}
			myStack.pop();
		}
	}

	while (!myStack.empty()) {
		postfix += myStack.top();
		myStack.pop();
	}

	return postfix;
}

node* genTree(string postfix) {
	stack<node*> myStack;
	node *tmp;
	for (int i = 0; i < postfix.size(); i++) {
		
		tmp = new node;
		tmp->info = postfix[i];

		if (isOperand(postfix[i])) {
			tmp->right = tmp->left = NULL;
		}
		if (isOperator(postfix[i])) {
			tmp->right = myStack.top();
			myStack.pop();
			tmp->left = myStack.top();
			myStack.pop();
		}
		myStack.push(tmp);
	}
	return myStack.top();
}

void print(node *n, int x = 40, int y = 0, int isRight = -1) {
	int tmpY = whereY();

	if (y == 0) y = tmpY;

	if (n == NULL)  {
		gotoXY(x, y);
		cout << "Empty";
		return;
	}

	if (isRight == 1) {
		gotoXY(x + 2, y - 1);
		cout << "/";
	}

	if (isRight == 0) {
		gotoXY(x - 2, y - 1);
		cout << "\\";
	}

	gotoXY(x, y);
	cout << char(n->info) << endl;
	Sleep(100);

	if (n->left != NULL) {
		print(n->left, x - 5, y + 2, 1);
	}

	if (n->right != NULL) {
		print(n->right, x + 5, y + 2, 0);
	}

	gotoXY(0, tmpY + 10 + 4);
}

int main() {
	string exp, postfix;
	node *tree;
	exp = "2+(2+3)+6*7/5";
	exp = "(a+b*c)+((d*e+f)*g)";
	postfix = Exp2PostFix(exp);
	tree = genTree(postfix);
	print(tree);
	return 0;
}