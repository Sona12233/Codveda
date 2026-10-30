#include <stdio.h>

int main(void) {
    printf("Enter first number: ");
    int first;
    scanf("%d", &first);

    printf("Enter second number: ");
    int second;
    scanf("%d", &second);

    printf("Enter what kind of operation you want to perform ( +, -, *, / ): ");
    char operation;
    scanf(" %c", &operation);

    switch(operation) {
        case '+':
            printf("%d + %d = %d\n", first, second, first + second);
            break;

        case '-':
            printf("%d - %d = %d\n", first, second, first - second);
            break;

        case '*':
            printf("%d * %d = %d\n", first, second, first * second);
            break;

        case '/':
            if (!second) {
                printf("Can not divide by zero.");
                break;
            }
            printf("%d / %d = %d\n", first, second, first / second);
            break;

        default:
            printf("Enter valid operator ( +, -, *, / )");
    }

    return 0;
}