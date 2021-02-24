#include "../include/tools.h"

void getData(char* file_path, float my_data[N_ROWS][N_COLS]) {
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
    if (c == EOF) {
      data[count_row][count_col] = atof(str_var);
    }
  }
  
  normalize(data);

  for (int i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      my_data[i][j] = data[i][j];
    }
  }

  fclose(fptr);
}

float calcDistance(float input_vec[N_ROWS][N_COLS], float training_vec[N_ROWS][N_COLS]) {
  float sum = 0;

  for (int i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      sum += pow(input_vec[i][j] - training_vec[i][j], 2);
    }
  }

  return sqrt(sum);
}

void knnExe(int *count_total, int *count_correct, char *testing_file_path, char *training_folder) {
  struct data_info predicts[K];
  char result;

  for (char file_name = 'a'; file_name <= 'z'; file_name++) {
    for (int i = 0; i < N_TRAINING_SAMPLES; i++) {
      char training_file[100];
      sprintf(training_file, "%s/%c/%c%d.txt", training_folder, file_name, file_name, i+1);
      float training_data[N_ROWS][N_COLS];
      float testing_data[N_ROWS][N_COLS];
      float distance = 0;
      struct data_info training_info;
      initMatrix(training_data);
      initMatrix(testing_data);

      getData(training_file, training_data);
      getData(testing_file_path, testing_data);
      
      training_info.name = file_name;
      training_info.distance = calcDistance(testing_data, training_data);
      // printf("char: %c, distance: %f\n", training_info.name, training_info.distance);
      sortDistance(predicts, training_info);
    }
  }
  result = predict(predicts);
  if (result == testing_file_path[8]) {
    (*count_correct)++;
  }
  (*count_total)++;
  // printf("result: %c\n", result);
}

void sortDistance(struct data_info predicts[K], struct data_info training_info) {
  int len = getLen(predicts);

  for (int i = 0; i < len-1; i++) {
    for (int j = i+1; j < len; j++) {
      if (predicts[i].distance > predicts[j].distance) {
        swap(&predicts[i], &predicts[j]);
      }
    }
  }

  if (len == 0) {
    predicts[0].name = training_info.name;
    predicts[0].distance = training_info.distance;
  } else if (len < K) {
    predicts[len].name = training_info.name;
    predicts[len].distance = training_info.distance;
  } else if (predicts[K-1].distance > training_info.distance) {
    predicts[K-1].name = training_info.name;
    predicts[K-1].distance = training_info.distance;
  }
}

char predict(struct data_info predicts[]) {
  int counts[K];
  int check[K];

  for (int i = 0; i < K; i++) {
    counts[i] = 0;
    check[i] = 0;
  }

  for (int i = 0; i < K; i++) {
    if (check[i] == 0) {
      for (int j = i; j < K; j++) {
        if (predicts[i].name == predicts[j].name) {
          counts[i] += 1;
          check[j] = 1;
        }
      }
    }
  }

  int final_result = getIndex(counts);

  for (int i = 0; i < K; i++) {
    if (counts[i] != 0) {
      // printf("Chance of %c: %.2f %%\n", predicts[i].name, (float)counts[i]/K * 100);
    }
  }
  // printf("==>> Prediction: %c\n", predicts[final_result].name);
  return predicts[final_result].name;
}

void normalize(float data[N_ROWS][N_COLS]) {
  float col[N_ROWS];
  float max_of_col;
  float min_of_col;

  for (int j = 0; j < N_COLS; j++) {
    for (int i = 0; i < N_ROWS; i++) {
      col[i] = data[i][j];
    }
    min_of_col = getMin(col);
    if (min_of_col < 0) {
      for (int i = 0; i < N_ROWS; i++) {
        col[i] = col[i] - min_of_col;
      }
    }
    max_of_col = getMax(col);
    for (int i = 0; i < N_ROWS; i++) {
      data[i][j] = col[i] / max_of_col;
    }
  }
}

float getMax(float vector[]) {
  float result = vector[0];

  for (int i = 1; i < N_ROWS; i++) {
    if (result < vector[i]) {
      result = vector[i];
    }
  }

  return result;
}

float getMin(float vector[]) {
  float result = vector[0];

  for (int i = 1; i < N_ROWS; i++) {
    if (result > vector[i]) {
      result = vector[i];
    }
  }

  return result;
}

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

void showMatrix(float data[N_ROWS][N_COLS]) {
  for (int i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      printf("%f,", data[i][j]);
    }
    printf("\n");
  }
}

void initMatrix(float data[N_ROWS][N_COLS]) {
  for (int i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      data[i][j] = 0;
    }
  }
}

void swap(struct data_info *a, struct data_info *b) {
  struct data_info temp = *a;
  *a = *b;
  *b = temp;
}

int getIndex(int counts[]) {
  int result;
  int max = counts[0];

  for (int i = 0; i < K; i++) {
    if (counts[i] > max) {
      max = counts[i];
    }
  }

  for (int i = 0; i < K; i++) {
    if (max == counts[i]) {
      result = i;
    }
  }

  return result;
}

int getLen(struct data_info predicts[]) {
  int result = 0;

  for (int i = 0; i < K; i++) {
    if (predicts[i].name >= 97 && predicts[i].name <= 122) {
      result++;
    }
  }

  return result;
}