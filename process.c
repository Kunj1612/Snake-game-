
//process
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

// file open clsoe write copy etc
#include<fcntl.h>

int main() {

    int i = 5;

    switch(fork()) {
        case -1:
            printf("Error");
        case 0:
            //in child process 
            sleep(5);

            printf("Child id %d\n",getpid());
            printf("Parent process id: %d\n",getppid());
            break;
        
        default:
            // in parent process
            printf("Process id %d\n",getpid());
            printf("Parent process id: %d\n",getppid());
            break;

    }
    printf("%d\n",i);

}