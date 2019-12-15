// Assignment 1: Solvability of the NxN sliding tile puzzle
// Created by Rongtao Shen on 2019-06-25.
// Student ID: z5178114

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "boardADT.h"

#define MAX_SIZE 2048

// 建立一个board结构体
struct board {
    int *tile;
    int number_of_tile;
};
// 初始化board
Board init_board(char *input) {
    //判断输入开头是否有空格，如果有把开头空格去掉
    char *p;
    while (*input == ' ') {
        for (p = input; *p != '\0'; p++) {
            *p = *(p + 1);
        }
    }
    //数空格
    int number_of_space = 0;
    for (p = input; *p != '\0'; p++) {
        if (*p == ' ') {
            if ((*(p + 1) >= '0' && *(p + 1) <= '9') || *(p + 1) == 'b') {
                number_of_space = number_of_space + 1;
            }
        }
    }
    // 定义一个结构体指针
    Board b;
    // 为结构体动态分配内存空间
    b = malloc(sizeof(struct board));
    // 如果地址为NULL，输出Out of memory并退出
    if (b == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    b->number_of_tile = 0;
    // 通过空格数量得到tile的数量
    b->number_of_tile = number_of_space + 1;
    // 为tile分配内存空间
    b->tile = malloc(b->number_of_tile * sizeof(int));
    char *p1 = input; // 定义一个循环指针p1指向输入
    int *p2 = b->tile; // 定义一个循环指针p2指向整型数组
    // 把'b'换成'0'并把数字存入数组
    while (*p1 != '\0') {
        int sum = 0;
        while ((*p1 >= '0') && (*p1 <= '9')) {
            sum = sum * 10 + (*p1 - '0');
            p1++;
        }
        if (sum != 0) {
            *p2 = sum;
            if (*p1 != '\0') {
                p1++;
            }
            p2++;
        }
        else {
            if (*p1 == 'b') {
                *p2 = 0;
                p1++;
                p2++;
            }
            else if (*p1 == ' ') {
                p1++;
            }
            else {
                p1++;
            }
        }
    }
    return b;
}
// 判断board是否有效
bool valid(Board b) {
    // 判断是否缺'b'
    int correct_sum = 0;
    int actual_sum = 0;
    int blank = 0;
    int *p = b->tile; // 定义一个循环指针p指向整型数组
    for (int i = 0; i < b->number_of_tile; i++) {
        if (*(p + i) == 0) {
            blank = blank + 1;
        }
    }
    // 判断是否有两个相同的数字或者缺数字
    for (int j = 0; j < b->number_of_tile; j++) {
        correct_sum = correct_sum + j;
    }
    int *p1 = b->tile; // 定义一个循环指针p1指向整型数组
    for (int k = 0; k < b->number_of_tile; k++) {
        actual_sum = actual_sum + *(p1 + k);
    }
    // 如果空格数不为1或有相同数字或缺数字或不是NxN board，返回false
    if (blank != 1 || actual_sum != correct_sum || b->number_of_tile < 4 || sqrt(b->number_of_tile) != (int)sqrt(b->number_of_tile)) {
        return false;
    }
    else {
        return true;
    }
}
// 判断start_board和goal_board的长度是否一致
int board_length(Board b) {
    return b->number_of_tile;
}
// 计算disorder
int disorder(Board b) {
    // 定义变量，disorder的数量
    int num_of_disorder = 0, row_of_b = 0;
    int size_of_board = (int)sqrt(b->number_of_tile);
    // num_of_tile为奇数时
    if (b->number_of_tile % 2 != 0) {
        int *p = b->tile;
        for (int i = 0; i < b->number_of_tile; i++) {
            for (int j = i + 1; j < b->number_of_tile; j++) {
                if (*(p + i) == 0 || *(p + j) == 0) {
                    continue;
                }
                else {
                    if (*(p + j) < *(p + i)) {
                        num_of_disorder = num_of_disorder + 1;
                    }
                }
            }
        }
        return num_of_disorder;
    }
    else {
        // num_of_tile为偶数时
        int *p1 = b->tile;
        for (int k = 0; k < b->number_of_tile; k++) {
            if (*(p1 + k) == 0) {
                if ((k + 1) % size_of_board == 0) {
                    row_of_b = (k + 1) / size_of_board;
                }
                else {
                    row_of_b = ((k + 1) / size_of_board) + 1;
                }
            }
        }
        int *p2 = b->tile;
        for (int i = 0; i < b->number_of_tile; i++) {
            for (int j = i + 1; j < b->number_of_tile; j++) {
                if (*(p2 + i) == 0 || *(p2 + j) == 0) {
                    continue;
                }
                else {
                    if (*(p2 + j) < *(p2 + i)) {
                        num_of_disorder = num_of_disorder + 1;
                    }
                }
            }
        }
        return row_of_b + num_of_disorder;
    }
}
// 判断parity属性,even返回1，odd返回0
int parity(int disorder) {
    if (disorder % 2 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
// 定义打印函数
void output(Board b) {
    for (int i = 0; i < b->number_of_tile; i++) {
        if (*(b->tile + i) == 0) {
            if (i != b->number_of_tile - 1) {
                printf("%c ", 'b');
            }
            else {
                printf("%c\n", 'b');
            }
        }
        else {
            if (i != b->number_of_tile - 1) {
                printf("%d ", *(b->tile + i));
            }
            else {
                printf("%d\n", *(b->tile + i));
            }
        }
    }
}
// 释放内存空间
void free_board(Board b) {
    if (b != NULL) {
        if (b->tile != NULL) {
            free(b->tile);
        }
        free(b);
    }
}