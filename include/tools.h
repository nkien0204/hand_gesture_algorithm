#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define N_ROWS 25
#define N_COLS 8
#define K 5
#define N_TRAINING_SAMPLES 8
#define N_TESTING_SAMPLES 2

struct data_info {
  char name;
  float distance;
};

char top_predicts[K]; 
void getData(char* file_path, float data[N_ROWS][N_COLS]);
float calcDistance(float input_vec[N_ROWS][N_COLS], float training_vec[N_ROWS][N_COLS]);
void knnExe(int *count_total, int *count_correct, char *input_file_path, char *training_folder);
void sortDistance(struct data_info *predicts, struct data_info training_info);
char predict(struct data_info predicts[]);
void normalize(float data[N_ROWS][N_COLS]);
void decrease_size(float data[N_ROWS][N_COLS], float my_data[]);
float getMax(float vector[]);
float getMin(float vector[]);
float getMinDistance(struct data_info predicts[]);
void showMatrix(float data[N_ROWS][N_COLS]);
void initMatrix(float data[N_ROWS][N_COLS]);
void swap(struct data_info *a, struct data_info *b);
int getIndex(int counts[]);
int getLen(struct data_info predicts[]);

#endif