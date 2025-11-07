#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char msg[] = "Hello OS File Management!";
    char buff[50];

    fd = open("demo.txt", O_CREAT | O_RDWR, 0777);
    write(fd, msg, sizeof(msg));
    lseek(fd, 0, SEEK_SET);
    read(fd, buff, sizeof(msg));
    printf("File content: %s\n", buff);
    close(fd);
    return 0;
}

