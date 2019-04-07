#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sched.h>
#include <semaphore.h>

int ticketCount = 1000;
sem_t *flag = NULL;

void *SellTicket()
{ 
    for(int i=100;i>0;i--)
    {
    //sem_wait(flag);
    int temp;
    printf("当前票数为：%d\n",ticketCount);
    temp = ticketCount;
    temp = temp - 1;
    sched_yield();
    ticketCount = temp;
    //sem_post(flag);
    }
}

void *ReturnTicket()
{
   for(int i=200;i>0;i--)
    {
    //sem_wait(flag);
    printf("当前票数为：%d\n",ticketCount);
    int temp;
    temp = ticketCount;
    temp = temp + 1;
    
    ticketCount = temp;
    //sem_post(flag);
    }
     
}

int main()
{
    pthread_t Sell,Return;
    flag = sem_open("flag",O_CREAT,0666,1);
    
    pthread_create(&Sell,NULL,SellTicket,NULL);
    pthread_create(&Return,NULL,ReturnTicket,NULL);

    pthread_join(Sell,NULL);
    pthread_join(Return,NULL);

    sem_close(flag);
    sem_unlink("flag");

    printf("最终票数为：%d \n",ticketCount);
    return 0;
}



