#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd; char buf[50];
    fd = open("file.txt", O_CREAT | O_RDWR, 0777);
    write(fd, "File management in OS", 22);
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, 22);
    printf("File content: %s\n", buf);
    close(fd);
    remove("file.txt");
    return 0;
}

