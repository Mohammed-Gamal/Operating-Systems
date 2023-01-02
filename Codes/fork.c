#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid;
  
  /* fork a child process */
  pid = fork();

  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) { /* child process */
    printf("I'm the Child!\n");
    execlp("/bin/ls", "ls", NULL);
  }
  else { /* parent process */
    /* parent will wait for the child to complete */
    wait(NULL);
    printf("I'm the parent with id %d, child's pid is %d, calling process id is %d.\n", getppid(), pid, getpid());
    printf("Child Complete!");
  }

  return 0;
}
