#include <stdio.h>
#include <string.h>

#define MAXNUMS 20

// Defining the stack
typedef struct
{
    int size;
    float nums[MAXNUMS];
} stack;

int is_operator(char *c);

int push(stack *to_push, float number);

float pop(stack *to_pop);

float apply_operation(float term_one, float term_two, char operation);

int main(int argc, chaFinir *argv[])
{
    // Validate number of arguments
    if (argc == 1)
    {
        printf("Usage: ./calculator {prefix expression}\n");
        return -1; // The exit code used for invalid arguments
    }
    else if (argc < 4)
    {
        // Must be at least 3 elements to a valid prefix expression (an operator and 2 operands)
        printf("Prefix expression is too short to possibly be valid.\n");
        return -1;
    }

    // Initialize the stack and its size
    stack operand_stack;
    operand_stack.size = 0;

    // Iterate through the prefix expression's elements from right to left
    for (int i = argc - 1; i >= 1; i--)
    {
        char *element = argv[i];

        if (!is_operator(element))
        {
            // Is the stack about to overflow?
            if (operand_stack.size == MAXNUMS)
            {
                printf("Sorry, but your prefix expression is too large for this calculator to handle! Consider adjusting MAXNUMS.\n");
                return -2; // The exit code used for an invalid expression
            }

            // It is a number: parse it as a float
            float numerical_value;
            sscanf(element, "%f", &numerical_value);

            // Push the parsed number into the stack
            push(&operand_stack, numerical_value);
        }
        else
        {
            // An opportunity to ensure the prefix operation is valid: there should be at least 2 operands in operand_stack
            if (operand_stack.size < 2)
            {
                printf("Invalid prefix expression!\n");
                return -2;
            }

            // Pop the two latest terms (the operands of this operation)
            float term_one = pop(&operand_stack), term_two = pop(&operand_stack);

            // Apply the operation to the operands
            float result = apply_operation(term_one, term_two, element[0]);

            // Push the result back into the stack
            push(&operand_stack, result);
        }
    }

    // The final element in operand_stack is the result. Output it
    printf("%f\n", pop(&operand_stack));
}

// Returns 1 if the provided string is a mathematical operator
int is_operator(char *c)
{
    // It should only be one character
    if (strlen(c) == 1)
    {
        return c[0] == '+' || c[0] == '-' || c[0] == 'x' || c[0] == '*' || c[0] == '/';
    }

    return 0;
}

// Pushes the given number onto the given stack, returns 1 if successful
int push(stack *to_push, float number)
{
    if (to_push->size < MAXNUMS)
    {
        // Push number and increment size
        to_push->nums[to_push->size] = number;
        to_push->size++;
        return 1;
    }

    // Did not push
    return 0;
}

// Pops the top element from the stack
float pop(stack *to_pop)
{
    if (to_pop->size == 0)
    {
        return 0;
    }

    // Stack is not empty, return the top element and reduce the size
    return to_pop->nums[--to_pop->size];
}

float apply_operation(float term_one, float term_two, char operation)
{
    switch (operation)
    {
        case '+':
            return term_one + term_two;
        case '-':
            return term_one - term_two;
        case '*':
        case 'x':
            return term_one * term_two;
        default:
            return term_one / term_two;
    }
}