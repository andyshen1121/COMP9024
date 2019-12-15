// Assignment 1: Solvability of the NxN sliding tile puzzle
// Created by Rongtao Shen on 2019-06-25.
// Student ID: z5178114

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "boardADT.h"

#define MAX_SIZE 2048

int main() {
    // 为输入的start动态分配内存空间
    char *start = malloc(MAX_SIZE * sizeof(char));
    // 为输入的goal动态分配内存空间
    char *goal = malloc(MAX_SIZE * sizeof(char));
    // 将输入存入start和goal
    fgets(start, MAX_SIZE, stdin);
    fgets(goal, MAX_SIZE, stdin);
    // 将输入存入ADT
    Board start_board = init_board(start);
    Board goal_board = init_board(goal);
    // 判断是否valid,是否start_board和goal_board长度相同以及是否solvable
    if (valid(start_board) && valid(goal_board) && (board_length(start_board) == board_length(goal_board))) {
        // 判断start_board和goal_board的parity是否一致
        if (parity(disorder(start_board)) == parity(disorder(goal_board))) {
            printf("start: ");
            output(start_board);
            printf("goal: ");
            output(goal_board);
            printf("solvable");
        }
        else {
            printf("start: ");
            output(start_board);
            printf("goal: ");
            output(goal_board);
            printf("unsolvable");
        }
    }
    else {
        printf("Incorrect input");
    }
    // 释放memory
    free_board(start_board);
    free_board(goal_board);
    free(start);
    free(goal);
    // exit with EXIT_SUCCESS
    return EXIT_SUCCESS;
}

