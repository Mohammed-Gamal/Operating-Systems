#include <windows.h>
#include <stdio.h>

int sum;  /* data is shared by the thread(s) */

/* the thread runs in this separate function */
int WINAPI summation(LPVOID param)
{
    int upper = *(int*)param;
    int i;
    for (i = 0; i <= upper; i++)
        sum += i;
    return 0;
}

int main(int argc, char *argv[])
{
    int threadId;
    HANDLE threadHandle;
    int param;

    if (argc != 2) {
        fprintf(stderr, "An integer parameter is required\n");
        return -1;
    }

    param = atoi(argv[1]);
    if (param < 0) {
        fprintf(stderr, "An integer >= 0 is required\n");
        return -1;
    }

    /* Create the thread */
    threadHandle = CreateThread(
    NULL,         /* default security attributes */
    0,            /* default stack size */
    summation,    /* thread function */
    &param,       /* parameter to thread function */
    0,            /* default creation flags */
    &threadId);   /* returns the thread identifier */

    if (threadHandle != NULL) {
        /* now wait for the thread to finish */
        WaitForSingleObject(threadHandle, INFINITE);  // pthread_join() in linux

        /* close the thread handle */
        CloseHandle(threadHandle);
        
        printf("sum = %d\n", sum);
    }
}
