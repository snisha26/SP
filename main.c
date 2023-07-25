#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a single line
struct Line {
    char *data;
    struct Line *next;
};

// Function to create a new line node and copy the data
struct Line* create_line(const char *data) {
    struct Line new_line = (struct Line)malloc(sizeof(struct Line));
    if (new_line == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_line->data = strdup(data);
    new_line->next = NULL;
    return new_line;
}

// Function to add a new line node to the linked list
void add_line(struct Line **head, const char *data) {
    struct Line *new_line = create_line(data);

    if (*head == NULL) {
        *head = new_line;
    } else {
        struct Line *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_line;
    }
}

// Function to free the linked list and its data
void free_lines(struct Line *head) {
    struct Line *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

// Function to print the last n lines from the linked list
void print_last_n_lines(struct Line *head, int n) {
    if (head == NULL || n <= 0) {
        return;
    }

    struct Line *tail = head;
    struct Line *prev = NULL;
    int count = 0;

    // Move 'tail' to the nth node from the start
    while (tail != NULL && count < n) {
        tail = tail->next;
        count++;
    }

    // Move both 'tail' and 'prev' until 'tail' reaches the end
    while (tail != NULL) {
        tail = tail->next;
        prev = (prev == NULL) ? head : prev->next;
    }

    // Print the last n lines
    while (prev != NULL) {
        printf("%s", prev->data);
        prev = prev->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_lines>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);

    struct Line *lines = NULL;
    char buffer[1024];

    // Read lines from stdin and add them to the linked list
    while (fgets(buffer, sizeof(buffer), stdin)) {
        add_line(&lines, buffer);
    }

    // Print the last n lines
    print_last_n_lines(lines, n);

    // Free the allocated memory
    free_lines(lines);

    return EXIT_SUCCESS;
}