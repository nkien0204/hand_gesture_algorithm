#ifndef INPUT_FILTER_H
#define INPUT_FILTER_H

#include <stdio.h>
#include <stdbool.h>
#include "../include/char_finding.h"
#include "../include/knn.h"

static int count_row3 = 0;
static int count_col3 = 0;

void getData3(char *file_path, float data[N_ROWS2][N_COLS]);
void pass(float data[N_ROWS2][N_COLS], float new_data[N_ROWS2][N_COLS]);
void showMatrix3(float data[N_ROWS2][N_COLS]);
void initMatrix3(float data[N_ROWS2][N_COLS]);

#endif