#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<semaphore.h>
#include<sys/types.h> //这个头文件不能少，否则pid_t没有定义 
#include <sys/wait.h>


sem_t *P1_signal = NULL;
sem_t *P2_signal = NULL;
sem_t *P3_signal = NULL;
//sem_t sem_open(const char * name, int oflag, mode_t mode, unsigned int value)
//返回值sem_t 是一个结构，如果函数调用成功，则返回指向这个结构的指针，里面装着当前信号量的资源数。

int main(int argc, char *argv[])
{
    pid_t pid;
    P1_signal = sem_open("P1_signal",O_CREAT,0666,0);
    P2_signal = sem_open("P2_signal",O_CREAT,0666,0);
    P3_signal = sem_open("P3_signal",O_CREAT,0666,0);

    pid = fork();

    if(pid < 0)
    {
        printf("进程为创建失败！");
        
    }


    else if(pid == 0)
    {
        sleep(1);
        sem_wait(P1_signal);
        printf("I am the process P2\n");
        sem_post(P1_signal);
        sem_post(P2_signal);
       
         pid = fork();

            if(pid < 0)
            {
                printf("进程为创建失败！");
                
            }

            else if(pid == 0)
            {
                sem_wait(P2_signal);
                sem_wait(P3_signal);
                printf("I am the process P4\n");
              
            }
    }

   else 
    {
        printf("I am the process P1\n");
        sem_post(P1_signal);

        pid = fork();

        if(pid < 0)
        {
        printf("进程为创建失败！");
       
        }

        else if(pid == 0)
        {
            sem_wait(P1_signal);
            printf("I am the process P3\n");
            sem_post(P1_signal);
            sem_post(P3_signal);
            return 0;

        }
    }

    sem_close(P1_signal);
    sem_unlink("P1_signal");
    sem_close(P2_signal);
    sem_unlink("P2_signal");
    sem_close(P3_signal);
    sem_unlink("P3_signal");
    return 0;

}