#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int value;
    int heuristic;
    struct Node* next;
} Node;

Node* createNode(int value, int heuristic) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->heuristic = heuristic;
    newNode->next = NULL;
    return newNode;
}

Node* graph[7] = {NULL};

void addEdge(int source, int dest, int heuristic) {
    Node* newNode = createNode(dest, heuristic);
    newNode->next = graph[source];
    graph[source] = newNode;
}

void bestFirstSearch(int start, int goal) {
    int visited[7] = {0};
    Node* queue[7] = {NULL};
    int front = -1, rear = -1;

    queue[++rear] = createNode(start, 0);
    visited[start] = 1;

    while (front != rear) {
        Node* currentNode = queue[++front];
        printf("Visited node: %d\n", currentNode->value);
        if (currentNode->value == goal) {
            printf("Goal node reached!\n");
            break;
        }

        Node* neighbor = graph[currentNode->value];
        while (neighbor != NULL) {
            if (!visited[neighbor->value]) {
                queue[++rear] = createNode(neighbor->value, neighbor->heuristic);
                visited[neighbor->value] = 1;
            }
            neighbor = neighbor->next;
        }
    }
}

void aStarSearch(int start, int goal) {
    int visited[7] = {0};
    Node* queue[7] = {NULL};
    int front = -1, rear = -1;

    queue[++rear] = createNode(start, 0);
    visited[start] = 1;

    while (front != rear) {
        Node* currentNode = queue[++front];
        printf("Visited node: %d\n", currentNode->value);
        if (currentNode->value == goal) {
            printf("Goal node reached!\n");
            break;
        }

        Node* neighbor = graph[currentNode->value];
        while (neighbor != NULL) {
            if (!visited[neighbor->value]) {
                int newHeuristic = currentNode->heuristic + neighbor->heuristic;
                queue[++rear] = createNode(neighbor->value, newHeuristic);
                visited[neighbor->value] = 1;
            }
            neighbor = neighbor->next;
        }
    }
}

int main() {
    addEdge(0, 1, 5);
    addEdge(0, 2, 4);
    addEdge(2, 3, 3);
    addEdge(1, 4, 2);
    addEdge(2, 5, 2);
    addEdge(3, 6, 1);

    int startNode = 0;
    int goalNode = 6;

    printf("Best-First Search:\n");
    bestFirstSearch(startNode, goalNode);

    printf("\nA* Search:\n");
    aStarSearch(startNode, goalNode);

    return 0;
}

