#include "../include/tools.h"

void getData(char* file_path, float my_data[]) {
  FILE *fptr = fopen(file_path, "r");
  float data[N_ROWS][N_COLS];
  int count_row = 0;
  int count_col = 0;
  char c;
  char str_var[6] = {'\0'};

  if (fptr == NULL) {
    printf("ERROR: File could not be opened\n");
    return;
  }

  c = fgetc(fptr);
  while (c != EOF) {
    if (c == ',') {
      data[count_row][count_col] = atof(str_var);
      memset(str_var, 0, 6);
      count_col++;
    } else if (c == '\n') {
      if (count_col == 8) count_col--;
      data[count_row][count_col] = atof(str_var);
      memset(str_var, 0, 6);
      count_row++;
      count_col = 0;
    } else {
      sprintf(str_var, "%s%c", str_var, c);
    }
    c = fgetc(fptr);
  }

  decrease_size(data, my_data);
}

float calcDistance(int input_vec[], int training_vec[]);
void knnExe(char *input_file_path, char *training_folder);
void sortDistance(float distances[]);
void predict(char top_predicts[]);
void normalize(float data[]) {}

void decrease_size(float data[N_ROWS][N_COLS], float my_data[]) {
  float sum = 0;
  int i;

  for (i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      sum += data[i][j];
    }
    my_data[i] = sum;
    sum = 0;
  }
}