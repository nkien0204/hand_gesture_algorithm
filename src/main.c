#include "../include/tools.h"

int main()
{
  char testing_file[100];
  char *testing_folder = "testing";
  char *training_folder = "training";
  int count_total = 0;
  int count_correct = 0;

  for (char i = 'a'; i <= 'z'; i++) {
    for (int j = 0; j < N_TESTING_SAMPLES; j++) {
      sprintf(testing_file, "%s/%c/%c%d.txt", testing_folder, i, i, j+1);
      knnExe(&count_total, &count_correct, testing_file, training_folder);
    }
  }

  printf("Total: %d, correct: %d\n", count_total, count_correct);
  printf("Accuracy: %.2f %%\n", (float)count_correct / count_total * 100);
	return (0);
}