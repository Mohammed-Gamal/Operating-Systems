// to compile this program you have to add the linking option (-pthread) to "compilation command" or to  "linker setting>>other linking options" in code::blocks

#include <pthread.h>
#include <stdio.h>

int sum; /* this data is shared by the thread(s) */\

/* threads call this function */
void *runner(void *param)
{
    int i, upper = atoi(param); // atoi: a string to integer;
    sum = 0;
    for (i = 1; i <= upper; i++)
        sum += i;
    pthread_exit(0);
}

int main(int argc, char *argv[]) // argc: arguments count, argv[]: arguments vector/array
{
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    if (argc != 2) {
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }

    /* get the default attributes */
    pthread_attr_init(&attr);
    
    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    
    /* wait for the thread to exit */
    pthread_join(tid, NULL);
    
    printf("sum = %d\n", sum);
}
