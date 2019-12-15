// COMP9024
// Assignment 2: Ordered Word Ladders
// Created by Rongtao Shen on 2019-08-11.
// Student ID: z5178114
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"
#define WORD_NUM 1001
#define LETTER_NUM 21

int main() {
    bool differByOne(char *word1, char *word2);
    int find_max_length(Graph g, int numVertices, int *path_length);
    void print_path(Graph g, Vertex start, int numVertices, int length, int max_length, int *count, int *visit, char **array);
//store words in array and delete duplicates
    char *array[WORD_NUM];
	for (int v = 0; v < WORD_NUM; v++) {
		array[v] = malloc(LETTER_NUM * sizeof(char));
	}
	int numVertices = 0;
	while ((scanf("%s", array[numVertices])) != EOF) {
		if (numVertices == 0) {
            numVertices++;
        }
        else {
            if ((strcmp(array[numVertices], array[numVertices - 1])) != 0) {
                numVertices++;
            }
            else {
                continue;
            }  
        }	
	}
//determines whether the file is empty
    if (numVertices == 0) {
        return EXIT_SUCCESS;
    }
//print dictionary words
    printf("Dictionary\n");
    for (int num = 0; num < numVertices; num++) {
        printf("%d: %s\n", num, array[num]);
    }
//create a ordered word ladder graph and insert edges into the graph
    printf("Ordered Word Ladder Graph\n");
    Graph g = newGraph(numVertices);
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) {
                continue;
            }
            else {
                if (differByOne(array[i], array[j])) {
                    Edge e = newEdge(i, j);
                    insertEdge(e, g);
                }
            }
        }
    }
//show graph
    showGraph(g);
//find the longest length and print the longest path
    int path_length[numVertices];
    int max_length = find_max_length(g, numVertices, path_length);
    printf("Longest ladder length: %d\n", max_length);
//print the longest path
    printf("Longest ladders:\n");
    int count = 1;
    int visit[numVertices];
    for (int l = 0; l < numVertices; l++) {
        visit[l] = 0;
    }
    for (int k = 0; k < numVertices; k++) {
        if (path_length[k] == max_length) {
            int length = 1;
            print_path(g, k, numVertices, length, max_length, &count, visit, array);
        }
    }
//free Graph and memory
    freeGraph(g);
    for (int m = 0; m < WORD_NUM; m++) {
        free(array[m]);
    }
//return    
	return EXIT_SUCCESS;
}
//find length of path for every start node and print the longest path
int find_max_length(Graph g, int numVertices, int *path_length) {
    int dfsR(Graph g, Vertex start, int numVertices, int length, int max);
    if (g == NULL) {
        fprintf(stderr, "Graph not initialised");
        exit(1);
    }
//find the length of every start node
    for (int i = 0; i < numVertices; i++) {
        int length = 1;
        int max = 1;
        path_length[i] = dfsR(g, i, numVertices, length, max);
    }
    int max_length = path_length[0];
//find max length
    for (int j = 0; j < numVertices; j++) {
        if (path_length[j] > max_length) {
            max_length = path_length[j];
        }
    }
//return max length    
    return max_length;
}
//recursive dfs algorithm to computer the longest length
int dfsR(Graph g, Vertex start, int numVertices, int length, int max) {
    int *pre = &length;
    for (int i = 0; i < numVertices; i++) {
        if (i > start) {
            Edge e = newEdge(start, i);
            if (isEdge(e, g)) {
                max = dfsR(g, i, numVertices, *pre + 1, max);
            }
        }
    }
    if (length > max) {
        max = length;
    }
    return max;
}
//print the longest path
void print_path(Graph g, Vertex start, int numVertices, int length, int max_length, int *count, int *visit, char **array) {
    int *pre = &length;
    visit[start] = 1;
    for (int i = 0; i < numVertices; i++) {
        if (i > start) {
            Edge e = newEdge(start, i);
            if (isEdge(e, g)) {
                print_path(g, i, numVertices, *pre + 1, max_length, count, visit, array);
            }
        }
    }
    if (length == max_length && *count <= 99) {
        int seq = 0;
        printf("%2d: ", *count);
        for (int j = 0; j < numVertices; j++) {
            if (visit[j] == 1) {
                if (seq != max_length - 1) {
                    printf("%s ", array[j]);
                    printf("-> ");
                    seq = seq + 1;
                }
                else {
                    printf("%s\n", array[j]);
                }
            }
        }
        *count = *count + 1;
        visit[start] = 0;
    }
    else {
        visit[start] = 0;
    }
}
//a function to compare 2 arbitrary null-terminated strings
bool differByOne(char *word1, char *word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    char *p1 = word1;
    char *p2 = word2;
    int same_num = 0;
    if (len1 == len2) {
        for (int i = 0; i < len1; i++) {
            if (*(p1 + i) == *(p2 + i)) {
                same_num = same_num + 1;
            }
        }
        if (same_num == len1 - 1) {
            return true;
        }
        else {
            return false;
        }       
    }
    else if (len1 - len2 == 1) {
        for (int i = 0; i < len2; i++) {
            if (*(p1 + i) != *(p2 + i)) {
                for (int j = i + 1; j < len1; j++) {
                    if (*(p1 + j) != *(p2 + j - 1)) {
                        return false;
                    }
                }
                return true;
            }
        }
        return true;
    }    
    else if (len2 - len1 == 1) {
        for (int i = 0; i < len1; i++) {
            if (*(p1 + i) != *(p2 + i)) {
                for (int j = i + 1; j < len2; j++) {
                    if (*(p1 + j - 1) != *(p2 + j)) {
                        return false;
                    }
                }
                return true;
            }
        }
        return true;
    }     
    else {
        return false;
    }  
}