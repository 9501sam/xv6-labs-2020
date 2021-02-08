#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void firstInput(int p[])
{
  for(int i = 2; i <= 35; i++) {
    write(p[1], &i, sizeof(i));
  }
  close(p[1]);
}

void inputNumber(int leftPipe[], int rightPipe[], int primeNumber)
{
  int num;
  while(read(leftPipe[0], &num, sizeof(int)) != 0)
    if(num % primeNumber != 0)
      write(rightPipe[1], &num, sizeof(int));
  close(leftPipe[0]);
  close(rightPipe[1]);
}

int
main(int argc, char *argv[])
{
  int leftPipe[2];
  int rightPipe[2];

  pipe(rightPipe);

  int childPid = fork();
  if(childPid == 0){                    //***child***//
    leftPipe[0] = rightPipe[0];
    leftPipe[1] = rightPipe[1];
    close(leftPipe[1]);
    int primeNumber;
    while(read(leftPipe[0], &primeNumber, sizeof(int)) != 0) {
      printf("prime %d\n", primeNumber);
      pipe(rightPipe);
      childPid = fork();
      if(childPid == 0) {
        leftPipe[0] = rightPipe[0];
        leftPipe[1] = rightPipe[1];
        close(leftPipe[1]);

      } else {
        close(rightPipe[0]);
        inputNumber(leftPipe, rightPipe, primeNumber);
        wait((int *) 0);
        exit(0);
      }
    }

  } else {                              //***first proccess***//
    close(rightPipe[0]);
    firstInput(rightPipe);
    wait((int *) 0);
  }

  exit(0);
}
