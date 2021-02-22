#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_ROWS 25
#define N_COLS 8
#define K 5

char top_predicts[K]; 
void getData(char* file_path, float data[]);
float calcDistance(int input_vec[], int training_vec[]);
void knnExe(char *input_file_path, char *training_folder);
void sortDistance(float distances[]);
void predict(char top_predicts[]);
void normalize(float data[]);
void decrease_size(float data[N_ROWS][N_COLS], float my_data[]);

#endif