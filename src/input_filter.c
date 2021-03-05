#include "../include/input_filter.h"

void getData3(char *file_path, float my_data[N_ROWS2][N_COLS]) {
  FILE *fptr = fopen(file_path, "r");
  float data[N_ROWS2][N_COLS];
  float line[20];
  count_row3 = 0;
  count_col3 = 0;
  char c;
  char str_var[6] = {'\0'};
  bool valid_input = true;

  if (fptr == NULL) {
    printf("ERROR: File could not be opened\n");
    return;
  }

  c = fgetc(fptr);
  while (c != EOF) {
    if ((c == ',') && (valid_input == true)) {
      line[count_col3] = atof(str_var);
      memset(str_var, 0, 6);
      if (line[count_col3] > 500) {
        valid_input = false;
      }
      count_col3++;
    } else if (c == '\n') {
      if (count_col3 == N_COLS-1) {
        line[count_col3] = atof(str_var);
        
        for (int i = 0; i < N_COLS; i++) {
          data[count_row3][i] = line[i];
        }
        count_row3++;
      }
      memset(str_var, 0, 6);
      count_col3 = 0;
      valid_input = true;
    } else if (valid_input == true) {
      sprintf(str_var, "%s%c", str_var, c);
    }

    c = fgetc(fptr);
    if (c == EOF) {
      data[count_row3][count_col3] = atof(str_var);
    }
  }
  
  for (int i = 0; i < count_row3; i++) {
    for (int j = 0; j < N_COLS; j++) {
      my_data[i][j] = data[i][j];
    }
  }
  fclose(fptr);
}

void pass(float data[N_ROWS2][N_COLS], float new_data[N_ROWS2][N_COLS]);

void showMatrix3(float data[N_ROWS2][N_COLS]) {
  for (int i = 0; i < count_row3; i++) {
    for (int j = 0; j < N_COLS; j++) {
      printf("%.2f,", data[i][j]);
    }
    printf("\n");
  }
}

void initMatrix3(float data[N_ROWS2][N_COLS]) {
  for (int i = 0; i < N_ROWS2; i++) {
    for (int j = 0; j < N_COLS; j++) {
      data[i][j] = 0;
    }
  }
}