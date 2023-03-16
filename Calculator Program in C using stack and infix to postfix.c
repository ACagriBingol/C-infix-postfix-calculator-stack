#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 100 // Maximum length of infix expression
#define STACK_SIZE 100 // Maximum size of stack

// Function to check if a character is an operator
int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return 1;
    }
    return 0;
}

// Function to get the precedence of an operator
int getPrecedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    else if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char infix[], char postfix[]) {
    char stack[STACK_SIZE]; // Initialize stack
    int top = -1; // Initialize top of stack
    int i, j; // Declare loop variables

    // Loop through each character in the infix expression
    for (i = 0, j = 0; infix[i] != '\0'; i++) {

        // If the current character is an operand, add it to the postfix expression
        if (isdigit(infix[i])) {
            postfix[j] = infix[i];
            j++;
        }

        // If the current character is an operator
        else if (isOperator(infix[i])) {

            // Pop operators with higher or equal precedence and add them to postfix
            while (top >= 0 && getPrecedence(stack[top]) >= getPrecedence(infix[i])) {
                postfix[j] = stack[top];
                j++;
                top--;
            }

            // Push the current operator onto the stack
            top++;
            stack[top] = infix[i];
        }

        // If the current character is a left parenthesis, push it onto the stack
        else if (infix[i] == '(') {
            top++;
            stack[top] = infix[i];
        }

        // If the current character is a right parenthesis, pop operators until we find the matching left parenthesis
        else if (infix[i] == ')') {
            while (stack[top] != '(') {
                postfix[j] = stack[top];
                j++;
                top--;
            }
            top--; // Pop the left parenthesis from the stack
        }
    }

    // Pop any remaining operators and add them to postfix
    while (top >= 0) {
        postfix[j] = stack[top];
        j++;
        top--;
    }

    postfix[j] = '\0'; // Terminate postfix string
}

// Function to evaluate a postfix expression
double evaluatePostfix(char postfix[]) {
    double stack[STACK_SIZE]; // Initialize stack
    int top = -1; // Initialize top of stack
    int i; // Declare loop variable

    // Loop through each character in the postfix expression
    for (i = 0; postfix[i] != '\0'; i++) {

        // If the current character is an operand, push it onto the stack
        if (isdigit(postfix[i])) {
            double operand = postfix[i] - '0'; // Convert character to integer
            top++;
            stack[top] = operand;
        }

        // If the current character is an operator, pop the two most recent operands and perform the operation
        else if (isOperator(postfix[i])) {
            double operand2 = stack[top];
            top--;
            double operand1 = stack[top];
            top--;
            double result;
            switch (postfix[i]) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            }

            // Push the result back onto the stack
            top++;
            stack[top] = result;
        }
    }

    // The final result is at the top of the stack
    return stack[top];
}
    // Main function
    int main() {
        char infix[MAX_LENGTH]; // Initialize infix expression
        char postfix[MAX_LENGTH]; // Initialize postfix expression
        printf("Enter infix expression: ");
        fgets(infix, MAX_LENGTH, stdin); // Read input expression

        // Convert infix expression to postfix expression
        infixToPostfix(infix, postfix);
        printf("Postfix expression: %s\n", postfix);

        // Evaluate postfix expression
        double result = evaluatePostfix(postfix);
        printf("Result: %.2f\n", result);

        return 0;

    }





/*
-
This code takes an infix expression as input, converts it to postfix using the shunting-yard algorithm, evaluates the postfix expression using a stack, and prints the result. 

The `isOperator` function checks if a character is an operator. It returns 1 if the character is one of '+', '-', '*', or '/', and 0 otherwise.

The `getPrecedence` function returns the precedence of an operator. It returns 1 for '+' and '-', 2 for '*' and '/', and 0 otherwise.

The `infixToPostfix` function takes an infix expression and converts it to postfix using the shunting-yard algorithm. It uses a stack to keep track of operators, and adds operands to the output string as they are encountered. When an operator is encountered, it pops operators from the stack and adds them to the output string until it finds an operator with lower precedence or a left parenthesis. It then pushes the current operator onto the stack. When a left parenthesis is encountered, it is pushed onto the stack. When a right parenthesis is encountered, operators are popped from the stack and added to the output string until the matching left parenthesis is found, which is then popped from the stack. Finally, any remaining operators are popped from the stack and added to the output string.

The `evaluatePostfix` function takes a postfix expression and evaluates it using a stack. It uses the stack to keep track of operands, and performs operations as operators are encountered. When an operand is encountered, it is pushed onto the stack. When an operator is encountered, the two most recent operands are popped from the stack, the operation is performed, and the result is pushed back onto the stack. Finally, the result is at the top of the stack.

The main function reads an infix expression from the user, converts it to postfix using `infixToPostfix`, evaluates the postfix expression using `evaluatePostfix`, and prints the result.

*/