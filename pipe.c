#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main() {
    int pipe1[2]; // client → server
    int pipe2[2]; // server → client

    pipe(pipe1);
    pipe(pipe2);

    switch(fork()) {

        case 0: {  // Child (client)

            close(pipe1[0]);
            close(pipe2[1]);

            char filename[100];  // ✅ FIXED
            printf("Enter filename: ");
            scanf("%s", filename);

            write(pipe1[1], filename, strlen(filename) + 1);

            char buffer[100];
            read(pipe2[0], buffer, sizeof(buffer));

            printf("Server Response: %s\n", buffer);

            close(pipe1[1]);
            close(pipe2[0]);
            break;  // ✅ IMPORTANT
        }

        default: { // Parent (server)

            close(pipe1[1]);
            close(pipe2[0]);

            char filename[100];  // ✅ FIXED
            read(pipe1[0], filename, sizeof(filename));

            char buffer[100];

            int fd = open(filename, O_RDONLY);

            if (fd < 0) {
                strcpy(buffer, "File not found");
            } else {
                ssize_t r = read(fd, buffer, sizeof(buffer)-1);
                buffer[r] = '\0';
                close(fd);
            }

            write(pipe2[1], buffer, strlen(buffer) + 1);

            close(pipe1[0]);
            close(pipe2[1]);
            break;
        }
    }

    return 0;
}
