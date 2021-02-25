#ifndef CHAR_FINDING_H
#define CHAR_FINDING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N_COLS2 5
#define N_LEVELS 5
#define N_ROWS2 200
#define THUMB  0
#define INDEX  1
#define MIDDLE 2
#define RING   3
#define PINKIE 4

static int count_row2 = 0;
static int count_col2 = 0;

void getData2(char *input_file_path, int data[N_ROWS2][N_COLS2]);
void getFinger(int data[N_ROWS2][N_COLS2], int which, int finger[]);
void getLevels(int finger[], int level[]);
void cutting(int data[N_ROWS2][N_COLS2], int total_signal[]);
void write2file(int data[N_ROWS2][N_COLS2], int count, int begin, int end);
void initMatrix2(int data[N_ROWS2][N_COLS2]);
void showMatrix2(int data[N_ROWS2][N_COLS2]);
int getMax2(int array[]);
int getMin2(int array[]);
void normalizeLevel(int level[]);
void showArray(int array[]);
void eliminateNoise(int level[]);
void buildSignal(int fingers[N_COLS2][N_ROWS2], int total_signal[]);

#endif