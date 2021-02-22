#include "../include/tools.h"

int main()
{
	float data[N_ROWS];
  
  //knnExe("", "");
  
  getData("a1.txt", data);
  normalize(data);

  // for (int i = 0; i < N_ROWS; i++) {
  //   printf("%f\n", data[i]);
  // }

	return (0);
}