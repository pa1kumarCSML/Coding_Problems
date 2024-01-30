#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a patient
typedef struct {
    char name[50];
    int priority;
    char admitTime[10];
} Patient;

// Structure to represent a node in the priority queue
typedef struct {
    Patient patient;
} Node;

// Priority Queue structure
typedef struct {
    Node* array;
    int capacity;
    int size;
} PriorityQueue;

int LEFT(int i)
{
    return 2 * i;
}
int RIGHT(int i)
{
    return 2 * i + 1;
}
int PARENT(int i)
{
    return i / 2;
}

// Function to initialize the priority queue
PriorityQueue* initializePriorityQueue(int capacity) {
    PriorityQueue* priorityQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    priorityQ->array = (Node*)malloc(capacity * sizeof(Node));
    priorityQ->capacity = capacity;
    priorityQ->size = 0;
    return priorityQ;
}


// Function to swap two nodes in the priority queue
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree with the root at given index (1-based indexing)
void maxHeapify(PriorityQueue* priorityQ, int index) {
    int largest = index; 
    int left = LEFT(index);
    int right = RIGHT(index);

    if (!(left > priorityQ->size) &&
        (priorityQ->array[left].patient.priority > priorityQ->array[largest].patient.priority ||
         (priorityQ->array[left].patient.priority == priorityQ->array[largest].patient.priority &&
          strcmp(priorityQ->array[left].patient.admitTime, priorityQ->array[largest].patient.admitTime) < 0))) {
        largest = left;
    }

    if (!(right > priorityQ->size) &&
        (priorityQ->array[right].patient.priority > priorityQ->array[largest].patient.priority ||
         (priorityQ->array[right].patient.priority == priorityQ->array[largest].patient.priority &&
          strcmp(priorityQ->array[right].patient.admitTime, priorityQ->array[largest].patient.admitTime) < 0))) {
        largest = right;
    }

    if (largest != index) {
        swap(&priorityQ->array[index], &priorityQ->array[largest]);
        maxHeapify(priorityQ, largest);
    }
}


void buildMaxHeap(PriorityQueue* priorityQ) {
    int n = priorityQ->size;
    for (int i = n / 2; i >0; i--) {
        maxHeapify(priorityQ, i);
    }
}

// Function to perform heap sort
void heapSort(PriorityQueue* priorityQ) {
    for (int i = priorityQ->size; i > 0; i--) {
        swap(&priorityQ->array[1], &priorityQ->array[i]);
        priorityQ->size--;
        maxHeapify(priorityQ, 1);
    }
}

// Function to insert a new patient into the priority queue
void admitPatient(PriorityQueue* priorityQ, char name[], int priority, char admitTime[]) {

    Node newNode;
    strcpy(newNode.patient.name, name);
    newNode.patient.priority = priority;
    strcpy(newNode.patient.admitTime, admitTime);

    // Insert the new patient at the end
    priorityQ->size++;
    priorityQ->array[priorityQ->size] = newNode;
    

    // Build max heap
    buildMaxHeap(priorityQ);
}

// Function to treat the next patient with high severity
void treatNextPatient(PriorityQueue* priorityQ) {
    if (priorityQ->size == 0) {
        printf("No patients in the queue.\n");
        return;
    }

    // Treat the patient with the highest priority
    printf("%s %d %s\n", priorityQ->array[1].patient.name, priorityQ->array[1].patient.priority,
           priorityQ->array[1].patient.admitTime);

    // Replace the root with the last patient and heapify
    priorityQ->array[1] = priorityQ->array[priorityQ->size];
    priorityQ->size--;

    maxHeapify(priorityQ, 1);
}

// Function to check the details of the next patient without removing them from the priority queue
void checkNextPatient(PriorityQueue* priorityQ) {
    if (priorityQ->size == 0) {
        printf("No patients in the queue.\n");
        return;
    }

    // Print details of the patient with the highest priority
    printf("%s %d %s\n", priorityQ->array[1].patient.name, priorityQ->array[1].patient.priority,
           priorityQ->array[1].patient.admitTime);
}

// Function to discharge a specific patient from the priority queue
void dischargePatient(PriorityQueue* priorityQ, char name[], char admitTime[]) {
    int i;
    for (i = 1; i <= priorityQ->size; i++) {
        if (strcmp(priorityQ->array[i].patient.name, name) == 0 &&
            strcmp(priorityQ->array[i].patient.admitTime, admitTime) == 0) {
            break;
        }
    }

    if (i > priorityQ->size) {
        printf("Patient not found in the queue.\n");
        return;
    }

    // Replace the patient with the last patient and heapify
    priorityQ->array[i] = priorityQ->array[priorityQ->size];
    priorityQ->size--;

    maxHeapify(priorityQ, i);
}

// Function to update the condition severity of a specific patient
void updateConditionSeverity(PriorityQueue* priorityQ, char name[], char admitTime[], int newPriority) {
    int i;
    for (i = 1; i <= priorityQ->size; i++) {
        if (strcmp(priorityQ->array[i].patient.name, name) == 0 &&
            strcmp(priorityQ->array[i].patient.admitTime, admitTime) == 0) {
            break;
        }
    }

    if (i > priorityQ->size) {
        printf("Patient not found in the queue.\n");
        return;
    }

    // Update the priority and heapify
    priorityQ->array[i].patient.priority = newPriority;

    buildMaxHeap(priorityQ);
}

// Function to print details of all patients
void printAllPatients(PriorityQueue* priorityQ) {
    int size=priorityQ->size;
    heapSort(priorityQ);

    for (int i = size; i>0; i--) {
        printf("%s %d %s\n", priorityQ->array[i].patient.name, priorityQ->array[i].patient.priority,
               priorityQ->array[i].patient.admitTime);
    }
    priorityQ->size=size;
    buildMaxHeap(priorityQ);
}

int main() {
    char option;
    PriorityQueue* priorityQ = initializePriorityQueue(100);

    do {
        scanf(" %c", &option);

        switch (option) {
            case 'a': {
                char name[50];
                int priority;
                char admitTime[10];
                scanf("%s %d %s", name, &priority, admitTime);
                admitPatient(priorityQ, name, priority, admitTime);
                break;
            }

            case 't': {
                treatNextPatient(priorityQ);
                break;
            }

            case 'c': {
                checkNextPatient(priorityQ);
                break;
            }

            case 'd': {
                char name[50];
                char admitTime[10];
                scanf("%s %s", name, admitTime);
                dischargePatient(priorityQ, name, admitTime);
                break;
            }

            case 'u': {
                char name[50];
                char admitTime[10];
                int newPriority;
                scanf("%s %s %d", name, admitTime, &newPriority);
                updateConditionSeverity(priorityQ, name, admitTime, newPriority);
                break;
            }

            case 'p': {
                printAllPatients(priorityQ);
                break;
            }

            case 'e': {
                // End the program
                break;
            }

            default: {
                printf("Invalid option. Provide valid option.\n");
                break;
            }
        }
    } while (option != 'e');

    // Free allocated memory
    free(priorityQ->array);
    free(priorityQ);

    return 0;
}