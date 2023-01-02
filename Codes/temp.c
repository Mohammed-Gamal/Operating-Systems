#include <stdio.h>
#include <unistd.h>

int main()
{

  /* fork child processes */
  fork();
  fork();
  fork();
  fork();
  fork();

  printf("Hello!\n");

  return 0;
}
