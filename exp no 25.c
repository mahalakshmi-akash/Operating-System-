#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // for open(), fcntl()
#include <unistd.h>     // for lseek(), read(), write(), close()
#include <sys/stat.h>   // for stat()
#include <dirent.h>     // for opendir(), readdir()
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    struct stat fileStat;

    // Step 1: Create and write to a file
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    write(fd, "Hello, this is a UNIX system call demo.\n", 40);
    printf("File 'demo.txt' created and written successfully.\n");

    // Step 2: Demonstrate lseek() - reposition file offset
    lseek(fd, 0, SEEK_SET); // move to beginning
    read(fd, buffer, sizeof(buffer));
    printf("\n[Using lseek() and read()]\nFile content: %s\n", buffer);

    // Step 3: Demonstrate fcntl() - duplicate file descriptor
    int new_fd = fcntl(fd, F_DUPFD, 0);
    if (new_fd < 0) {
        perror("Error using fcntl()");
        close(fd);
        return 1;
    } else {
        printf("\n[Using fcntl()]\nDuplicated file descriptor: %d\n", new_fd);
    }

    // Step 4: Demonstrate stat() - get file information
    if (stat("demo.txt", &fileStat) < 0) {
        perror("Error using stat()");
        close(fd);
        return 1;
    }

    printf("\n[Using stat()]\n");
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Number of Links: %ld\n", fileStat.st_nlink);
    printf("File Permissions: %o (octal)\n", fileStat.st_mode & 0777);
    printf("Last Access Time: %ld\n", fileStat.st_atime);

    // Step 5: Demonstrate opendir() and readdir() - read current directory
    DIR *dir;
    struct dirent *entry;

    printf("\n[Using opendir() and readdir()]\n");
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        close(fd);
        return 1;
    }

    printf("Contents of current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }

    closedir(dir);
    close(fd);
    close(new_fd);

    printf("\nAll UNIX I/O system calls executed successfully.\n");
    return 0;
}

