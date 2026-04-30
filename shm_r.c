#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    int shm_fd;

    shm_fd = shm_open("mem", O_RDONLY, 0777);


    void *ptr = mmap(NULL, 32, PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("Time read: %s\n", (char *)ptr);

    shm_unlink("mem");

    return 0;
}