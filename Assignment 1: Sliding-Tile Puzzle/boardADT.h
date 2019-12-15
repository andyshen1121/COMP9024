// Assignment 1: Solvability of the NxN sliding tile puzzle
// Created by Rongtao Shen on 2019-06-25.
// Student ID: z5178114

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_SIZE 2048

typedef struct board *Board;

// 声明初始化board函数
Board init_board(char *input);

// 声明判断board是否valid函数
bool valid(Board b);

// 声明判断start_board和goal_board长度是否一致的函数
int board_length(Board b);

// 声明disorder函数
int disorder(Board b);

// 声明parity函数
int parity(int disorder);

// 声明打印函数
void output(Board b);

// 声明释放memory函数
void free_board(Board b);

