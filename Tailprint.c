#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a single line in the linked list
typedef struct Node {
    char *line;
    struct Node *next;
} Node;

// Function to create a new node with the given line
Node* createNode(const char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->line = strdup(line);
        newNode->next = NULL;
    }
    return newNode;
}

// Function to add a new node to the end of the linked list
void appendNode(Node** head, Node* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to free the memory used by the linked list
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }
}

// Function to print the last n lines from the linked list
void printTail(Node* head, int n) {
    int totalLines = 0;
    Node* current = head;

    // Count the total number of lines in the linked list
    while (current != NULL) {
        totalLines++;
        current = current->next;
    }

    // Adjust n to the total number of lines if n is larger
    n = (n > totalLines) ? totalLines : n;

    // Calculate the starting position to print from
    int startPos = totalLines - n;

    // Move current to the starting position
    current = head;
    for (int i = 0; i < startPos; i++) {
        current = current->next;
    }

    // Print the last n lines
    while (current != NULL) {
        printf("%s", current->line);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Invalid value for n: %d\n", n);
        return 1;
    }

    Node* head = NULL;
    char buffer[256];

    // Read lines from input and store them in the linked list
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        Node* newNode = createNode(buffer);
        if (newNode == NULL) {
            printf("Memory allocation error!\n");
            freeList(head);
            return 1;
        }
        appendNode(&head, newNode);
    }

    // Print the last n lines
    printTail(head, n);

    // Free the memory used by the linked list
    freeList(head);

    return 0;
}
