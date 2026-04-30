
//process
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

// file open clsoe write copy etc
#include<fcntl.h>

int main() {

    int fd1,fd2,fd3;
    char buffer[50];
    ssize_t r;

    fd1 = open("name.txt",O_RDONLY);
    fd3 = open("name1.txt",O_RDONLY);

    fd2 = open("copy.txt",O_WRONLY | O_CREAT | O_APPEND, 0644);

    while((r = read(fd1,buffer,50)) > 0) {
        write(fd2,buffer,r);
    }

    write(fd2,"\n",1);

    while((r = read(fd3,buffer,50)) > 0) {
        write(fd2,buffer,r);
    }
    write(fd2,"\n",1);


    return 0;
}