#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

void* func(void* data)
{
    pthread_t tid = (pthread_t)data;    /* data received by thread */

    //pthread_join(tid, NULL);            /* wait for thread tid     */
    sleep(1);
    printf("\n From func()... Hello from new thread %u - received %u\n", pthread_self(), data);
    //pthread_exit(NULL);                   /* terminate the thread    */
}

void* Question(void* data)
{
    int        rc;                 /* return value                  */
    pthread_t  thread_id;              /* thread's ID (just an integer) */
    
    pthread_t tid = (pthread_t)data;    /* data received by thread */
    int y = 15;

    pthread_detach(pthread_self());            /* wait for thread tid     */
    
    rc = pthread_create(&thread_id, NULL, func, (void*)y);  
    if(rc)                             /* could not create thread */
    {
        printf("\n [-]ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    
    printf("From Q1()... Created new thread (%u) ... from a thread (%u)\n", thread_id, tid);

    
    printf("From Q1()... Hello from new thread %u, and received calling thraed ID %u\n", pthread_self(), data);
    
    sleep(5);
    exit(NULL);
}

void* Q4(void* data)
{
    int        rc;                 /* return value                  */
    pthread_t  thread_id;              /* thread's ID (just an integer) */
    
    pthread_t tid = (pthread_t)data;    /* data received by thread */
    
    sleep(1);
    printf("[+]Hello  %u, and received: %u\n", pthread_self(), data);
    pthread_exit(NULL);                   /* terminate the thread    */
    
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    int        rc;         	       /* return value                  */
    pthread_t  thread_id;     	       /* thread's ID (just an integer) */
    int        tid;

    tid = pthread_self();
    int x = 10;

    rc = pthread_create(&thread_id, NULL, Question, (void*)tid);  
    if(rc)                             /* could not create thread */
    {
        printf("\n [-]ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    //sleep(1);
    printf("\n From main().. Created new thread (%u) ... \n", thread_id);

    //sleep(2);
    rc = pthread_create(&thread_id, NULL, func, (void*)x);  
    if(rc)                             /* could not create thread */
    {
        printf("\n[-] ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    
    printf("\n From main().. Created second thread (%u) ... \n", thread_id);
    pthread_exit(NULL);	
    	
}
