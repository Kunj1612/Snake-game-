#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    int shm_fd;

    shm_fd = shm_open("mem", O_CREAT | O_RDWR, 0777);

    ftruncate(shm_fd, 32);

    void *ptr = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    time_t now;
    time(&now);

    sprintf((char *)ptr, "%s", ctime(&now));

    printf("Time written: %s\n", (char *)ptr);

    return 0;
}