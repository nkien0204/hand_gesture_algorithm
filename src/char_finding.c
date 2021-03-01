#include "../include/char_finding.h"
#include "../include/knn.h"

void getData2(char *input_file_path, int my_data[N_ROWS2][N_COLS2]) {
  FILE *fptr = fopen(input_file_path, "r");
  float data[N_ROWS2][N_COLS];
  count_row2 = 0;
  count_col2 = 0;
  char c;
  char str_var[6] = {'\0'};

  if (fptr == NULL) {
    printf("ERROR: File could not be opened\n");
    return;
  }

  c = fgetc(fptr);
  while (c != EOF) {
    if (c == ',') {
      data[count_row2][count_col2] = atof(str_var);
      memset(str_var, 0, 6);
      count_col2++;
    } else if (c == '\n') {
      if (count_col2 == N_COLS) count_col2--;
      data[count_row2][count_col2] = atof(str_var);
      memset(str_var, 0, 6);
      count_row2++;
      count_col2 = 0;
    } else {
      sprintf(str_var, "%s%c", str_var, c);
    }
    c = fgetc(fptr);
    if (c == EOF) {
      data[count_row2][count_col2] = atof(str_var);
      count_row2++;
    }
  }
  count_col2 = 5;
  for (int i = 0; i < count_row2; i++) {
    for (int j = 0; j < count_col2; j++) {
      my_data[i][j] = (int)data[i][j];
    }
  }
  fclose(fptr);
}

void getFinger(int data[N_ROWS2][N_COLS2], int which, int finger[]) {
  for (int i = 0; i < count_row2; i++) {
    finger[i] = data[i][which];
  }
}

void getLevels(int finger[], int level[]) {
  int max = getMax2(finger);
  int min = getMin2(finger);
  int threshold = (max - min) / N_LEVELS;

  for (int i = 0; i < N_ROWS2; i++) {
    if (finger[i] < min + (N_LEVELS/2)*threshold) {
      level[i] = 1;
    } else if (finger[i] < min + (N_LEVELS/2+1)*threshold) {
      level[i] = 2;
    } else {
      level[i] = 3;
    }
  }
}

void cutting(int data[N_ROWS2][N_COLS2], int total_signal[]) {
  int begin = -1;
  int end = -1;
  int count = 0;

  for (int i = 0; i < count_row2-1; i++) {
    if ((total_signal[i] == 2) && (total_signal[i+1] == 3)) {
      begin = i;
    } else if ((total_signal[i] == 3) && total_signal[i+1] == 2) {
      end = i+1;
      count++;
    }

    if ((begin != -1) && (end != -1)) {
      write2file(data, count, begin, end);
      begin = -1;
      end = -1;
    }
  }
}

void write2file(int data[N_ROWS2][N_COLS2], int count, int begin, int end) {
  char file_path[10];

  sprintf(file_path, "%d.txt", count);
  FILE *fptr = fopen(file_path, "w");

  if (fptr == NULL) {
    printf("ERROR: Could not write to file\n");
    return;
  }

  for (int i = begin; i < end+1; i++) {
    char str[6] = {'\0'};
    char ch;
    for (int j = 0; j < N_COLS; j++) {
      if (j == N_COLS-1) {
        ch = '\n';
      } else {
        ch = ',';
      }
      sprintf(str, "%d%c", data[i][j], ch);

      fputs(str, fptr);
    }
  }
  fclose(fptr);
}

void initMatrix2(int data[N_ROWS2][N_COLS2]) {
  for (int i = 0; i < N_ROWS2; i++) {
    for (int j = 0; j < N_COLS2; j++) {
      data[i][j] = 0;
    }
  }
}

void showMatrix2(int data[N_ROWS2][N_COLS2]) {
  for (int i = 0; i < count_row2; i++) {
    for (int j = 0; j < count_col2; j++) {
      printf("%d,", data[i][j]);
    }
    printf("\n");
  }
}

int getMax2(int array[]) {
  int result = array[0];

  for (int i = 1; i < count_row2; i++) {
    if (result < array[i]) {
      result = array[i];
    }
  }
  return result;
}

int getMin2(int array[]) {
  int result = array[0];

  for (int i = 1; i < count_row2; i++) {
    if (result > array[i]) {
      result = array[i];
    }
  }
  return result;
}

void normalizeLevel(int level[]) {
  int first_target_index = 0;
  int count = 1;

  for (int i = 0; i < count_row2-1; i++) {
    if ((level[i] == 2) && (level[i+1] == 2)) {
      if (count == 1) {
        first_target_index = i;
      }
      count++;
    } else if (count > 1) {
      int mid = first_target_index + count / 2;
      for (int j = first_target_index; j < first_target_index+count; j++) {
        if (j < mid) {
          level[j] = level[j-1];
        } else if (j > mid) {
          level[j] = level[first_target_index+count];
        }
      }
      count = 1;
    }

    if ((level[i] == 3) && (level[i+1] == 1)) {
      level[i+1] = 2;
    }
    if ((level[i] == 1) && (level[i+1] == 3)) {
      level[i] = 2;
    }
  }

  eliminateNoise(level);
}

void eliminateNoise(int level[]) {
  int count = 0;
  int pos_edge;
  int neg_edge;
  for (int i = 1; i < count_row2-1; i++) {
    if ((level[i-1] == 1) && (level[i] == 2) && (level[i+1] == 1)) {
      level[i] = 1;
    } else if ((level[i] == 2) && (level[i+1] == 3)) {
      pos_edge = i;
    } else if (level[i] == 3) {
      count++;
    }

    if ((level[i] == 3) && (level[i+1] == 2)) {
      neg_edge = i+1;
      if (count < 5) {
        for (int j = pos_edge+1; j < pos_edge+count+1; j++) {
          level[j] = 1;
        }
      }
      count = 0;
    }
  }
}

void buildSignal(int fingers[N_COLS2][N_ROWS2], int total_signal[]) {
  for (int i = 0; i < count_row2; i++) {
    if (fingers[THUMB][i] == 2 || fingers[INDEX][i] == 2 || fingers[MIDDLE][i] == 2 ||
        fingers[RING][i] == 2 || fingers[PINKIE][i] == 2) {
      total_signal[i] = 2;
    } else if (fingers[THUMB][i] == 3 || fingers[INDEX][i] == 3 || fingers[MIDDLE][i] == 3 ||
               fingers[RING][i] == 3 || fingers[PINKIE][i] == 3) {
      total_signal[i] = 3;
    } else {
      total_signal[i] = 1;
    }
  }
}

void showArray(int array[]) {
  for (int i = 0; i < count_row2; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}