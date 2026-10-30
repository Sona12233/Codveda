
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* Stack operations */

void push(Node** top, int value) {
    Node* node = malloc(sizeof *node);

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    node->data = value;
    node->next = *top;
    *top = node;

    printf("%d pushed onto stack.\n", value);
}

void pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    Node* temp = *top;
    printf("Popped: %d\n", temp->data);

    *top = temp->next;
    free(temp);
}

void display_stack(const Node* top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack (top to bottom): ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

/* Queue operations */

void enqueue(Node** front, Node** rear, int value) {
    Node* node = malloc(sizeof *node);

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    node->data = value;
    node->next = NULL;

    if (*rear == NULL) {
        *front = node;
    } else {
        (*rear)->next = node;
    }

    *rear = node;
    printf("%d added to queue.\n", value);
}

void dequeue(Node **front, Node **rear) {
    if (*front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    Node *temp = *front;
    printf("Dequeued: %d\n", temp->data);

    *front = temp->next;

    if (*front == NULL) {
        *rear = NULL;
    }

    free(temp);
}

void display_queue(const Node *front) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue (front to rear): ");
    while (front != NULL) {
        printf("%d ", front->data);
        front = front->next;
    }
    printf("\n");
}

/* Release all remaining nodes */

void clear_list(Node **head) {
    while (*head != NULL) {
        Node *temp = *head;
        *head = temp->next;
        free(temp);
    }
}

int main(void) {
    Node *top = NULL;
    Node *front = NULL;
    Node *rear = NULL;
    int choice, value;

    do {
        printf("\n--- Data Structure Menu ---\n");
        printf("1. Push onto stack\n");
        printf("2. Pop from stack\n");
        printf("3. Display stack\n");
        printf("4. Enqueue into queue\n");
        printf("5. Dequeue from queue\n");
        printf("6. Display queue\n");
        printf("0. Exit\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
            case 4:
                printf("Enter integer: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input. Exiting.\n");
                    choice = 0;
                    break;
                }

                if (choice == 1)
                    push(&top, value);
                else
                    enqueue(&front, &rear, value);
                break;

            case 2:
                pop(&top);
                break;

            case 3:
                display_stack(top);
                break;

            case 5:
                dequeue(&front, &rear);
                break;

            case 6:
                display_queue(front);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    clear_list(&top);
    clear_list(&front);

    return 0;
}
