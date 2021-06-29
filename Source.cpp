// C program to convert infix expression to postfix 
#include <stdio.h> 
#include <conio.h>
#include <string.h> 
#include <stdlib.h> 

struct Stack		// Stack type 
{
	int top;
	unsigned capacity;
	int* array;
};

struct Stack* createStack(int cap)	// Stack Operations 
{
	struct Stack *st = (struct Stack*) malloc(sizeof(struct Stack));

	st->top = -1;
	st->capacity = cap;
	st->array = (int*)malloc(cap * sizeof(int));
	return st;
}
int isEmpty(struct Stack *st)
{
	return st->top == -1;
}
int isFull(struct Stack *st)
{
	return (st->top == st->capacity - 1);
}
char peek(struct Stack *st)
{
	return st->array[st->top];
}
char pop(struct Stack *st)
{
	if (isEmpty(st))
		return '$';
	int temp = st->array[st->top];
	st->top--;
	return temp;
}
void push(struct Stack *st, char op)
{
	st->top++;
	st->array[st->top] = op;
}

int isOperand(char ch)	// A utility function to check if the given character is operand 
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// A utility function to return precedence of a given operator 
// Higher returned value means higher precedence 
int Precedence(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}

// The main function that converts given infix expression to postfix expression. 
int infixToPostfix(char *exp)
{
	int i, k;
	char postfix[30] = {};
	struct Stack *s = createStack(strlen(exp));  // Create a stack of capacity equal to expression size 

	for (i = 0, k = 0; exp[i]; i++)
	{
		if (isOperand(exp[i]))    // If the scanned character is an operand, add it to output. 
		{
			postfix[k] = exp[i];
			k++;
		}
		else if (exp[i] == '(')    // If the scanned character is an ‘(‘, push it to the stack. 
			push(s, exp[i]);

// If the scanned character is an ‘)’, pop and output from the stack until an ‘(‘ is encountered. 
		else if (exp[i] == ')')
		{
			while (peek(s) != '(')
			{
				postfix[k] = pop(s);
				k++;
			}
				pop(s);
		}
		else // an operator is encountered 
		{
			//char peekstack = peek(s);
			//if (Precedence(exp[i]) <= Precedence(peekstack))
				while (Precedence(exp[i]) <= Precedence(peek(s)) && !isEmpty(s))
				{
					postfix[k] = pop(s);
					k++;
				}
				push(s, exp[i]);
		}
	}

	while (!isEmpty(s))    // pop all the operators from the stack 
	{
		postfix[k] = pop(s);
		k++;
	}
	postfix[k] = '\0';
	printf("%s", postfix);
}

// Driver program to test above functions 
int main()
{
	char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
	infixToPostfix(exp);
	printf("\n\n");
	char exp2[] = "a+b*c-d/e";
	infixToPostfix(exp2);
	printf("\n\n");
	char exp3[] = "(a+b)*(c-d)/e";
	infixToPostfix(exp3);
	printf("\n\n");
	char exp4[] = "a+((b+c)+(d+e)*f)/g";	//EX 5.3 Baluja
	infixToPostfix(exp4);
	printf("\n\n");
	char exp5[] = "a-b/(c*d^e)";
	infixToPostfix(exp5);
	printf("\n\n");
	char exp6[] = "a-b/c*d^e";
	infixToPostfix(exp6);
	printf("\n\n");
	char exp7[] = "a*b+c/d";				//EX 5.5 Baluja
	infixToPostfix(exp7);
	printf("\n\n");
	char exp8[] = "(a+b)*c/d";				//EX 5.9 Baluja
	infixToPostfix(exp8);
	printf("\n\n");
	char exp9[] = "(a+b)*c/d+e^f/g";				//EX 5.10 Baluja
	infixToPostfix(exp9);
	_getch();
}