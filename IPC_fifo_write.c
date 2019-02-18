#include<stdio.h>
#include<stdlib.h>   // exit
#include<fcntl.h>    // O_WRONLY
#include<sys/stat.h>
#include<time.h>     // time
#include <unistd.h>  //write() fuction nead

int main()
{
    int    fd;
    int    n, i;
    char   buf[1024] = {0};
    time_t tp;

    printf("I am %d process.\n", getpid()); // ˵������ID
    
    if((fd = open("fifo1", O_WRONLY)) < 0) // ��д��һ��FIFO����һֱ�����ȵ�IPC_fifo_read.c mkfifo()������fifo
    {
        perror("Open FIFO Failed");
        exit(1);
    }
    
    printf("<lihf> ����һ��open�᲻������\n");

    for(i=0; i<10; ++i)
    {
        time(&tp);  // ȡϵͳ��ǰʱ��
        n=sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
        printf("Send message: %s", buf); // ��ӡ
        if(write(fd, buf, n+1) < 0)  // д�뵽FIFO��
        {
            perror("Write FIFO Failed");
            close(fd);
            exit(1);
        }
        sleep(1);  // ����1��
    }

    close(fd);  // �ر�FIFO�ļ�
    return 0;
}