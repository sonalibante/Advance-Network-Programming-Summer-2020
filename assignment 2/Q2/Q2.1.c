#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

/* function to be executed by the new thread */
void* PrintHello(void* data)
{
    int my_data = (int)data;     	/* data received by thread */
    printf("Hello from new thread - got %d\n", pthread_self());
    pthread_exit(NULL);			/* terminate the thread */
}

void* Question(void )
{
    int        rc;          /* return value                           */
    pthread_t  thread_id;       /* thread's ID (just an integer)          */
    int        t         = 11;  /* data passed to the new thread          */

    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)t);  
    if(rc)          /* could not create thread */
    {
        printf("\n [-]ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    printf("\n [+]Created new thread (%u) ... \n", thread_id);

    printf("Hello from Question - got %d\n", pthread_self());
}


int main(int argc, char* argv[])
{
    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    int        t         = 1;  /* data passed to the new thread          */
printf("In main() before Q1() call\n");
Question();
printf("In main() \n");
Question();
PrintHello((void*)t);
    
}