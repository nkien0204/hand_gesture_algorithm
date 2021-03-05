#include "../include/knn.h"
#include "../include/char_finding.h"
#include "../include/input_filter.h"

int main()
{
/*************************************KNN_LIB******************************************/
  // char testing_file[100];
  // char *testing_folder = "testing";
  // char *training_folder = "training";
  // int count_total = 0;
  // int count_correct = 0;

  // for (char i = 'a'; i <= 'z'; i++) {
  //   for (int j = 0; j < N_TESTING_SAMPLES; j++) {
  //     sprintf(testing_file, "%s/%c/%c%d.txt", testing_folder, i, i, j+1);
  //     knnExe(&count_total, &count_correct, testing_file, training_folder);
  //   }
  // }

  // printf("Total: %d, correct: %d\n", count_total, count_correct);
  // printf("Accuracy: %.2f %%\n", (float)count_correct / count_total * 100);


  // knnExe(&count_total, &count_correct, "testing/k/k3.txt", training_folder);
  // printf("Total: %d, correct: %d\n", count_total, count_correct);
  // printf("Accuracy: %.2f %%\n", (float)count_correct / count_total * 100);


/***************************************CHAR_FINDING_LIB****************************************/
  // int data[N_ROWS2][N_COLS2];
  // int fingers[N_COLS2][N_ROWS2];
  // int level[N_COLS2][N_ROWS2];
  // int total_signal[N_ROWS2];
  // initMatrix2(data);
  // getData2("chains/efgh/efgh1.txt", data);
  
  // for (int i = 0; i < N_COLS2; i++) {
  //   getFinger(data, i, fingers[i]);

  //   getLevels(fingers[i], level[i]);
  //   normalizeLevel(level[i]);
    
  //   showArray(level[i]);
  // }

  // buildSignal(level, total_signal);
  // normalizeLevel(total_signal);
  // printf("\n");
  // showArray(total_signal);
  // cutting(data, total_signal);


/************************************INPUT_FILTER_LIB*******************************************/
  float data[N_ROWS2][N_COLS];
  initMatrix3(data);
  getData3("test_input_filter.txt", data);
  showMatrix3(data);

	return (0);
}