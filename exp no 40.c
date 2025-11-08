#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    struct stat fileStat;
    const char *filename = "demo_file.txt";

    // Step 1: Create a demo file
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fp, "This is a demo file for permission illustration.\n");
    fclose(fp);

    // Step 2: Get and display initial file permissions
    if (stat(filename, &fileStat) < 0) {
        perror("Error getting file status");
        return 1;
    }

    printf("\n--- BEFORE CHANGING PERMISSIONS ---\n");
    printf("File: %s\n", filename);
    printf("Owner: Read[%c] Write[%c] Execute[%c]\n",
           (fileStat.st_mode & S_IRUSR) ? 'Y' : 'N',
           (fileStat.st_mode & S_IWUSR) ? 'Y' : 'N',
           (fileStat.st_mode & S_IXUSR) ? 'Y' : 'N');
    printf("Group: Read[%c] Write[%c] Execute[%c]\n",
           (fileStat.st_mode & S_IRGRP) ? 'Y' : 'N',
           (fileStat.st_mode & S_IWGRP) ? 'Y' : 'N',
           (fileStat.st_mode & S_IXGRP) ? 'Y' : 'N');
    printf("Others: Read[%c] Write[%c] Execute[%c]\n",
           (fileStat.st_mode & S_IROTH) ? 'Y' : 'N',
           (fileStat.st_mode & S_IWOTH) ? 'Y' : 'N',
           (fileStat.st_mode & S_IXOTH) ? 'Y' : 'N');

    // Step 3: Change file permission (Owner: rwx, Group: r-x, Others: r--)
    if (chmod(filename, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH) < 0) {
        perror("Error changing file permissions");
        return 1;
    }

    // Step 4: Get and display updated file permissions
    if (stat(filename, &fileStat) < 0) {
        perror("Error getting file status after chmod");
        return 1;
    }

    printf("\n--- AFTER CHANGING PERMISSIONS (chmod 754) ---\n");
    printf("Owner: Read[%c] Write[%c] Execute[%c]\n",
           (fileStat.st_mode & S_IRUSR) ? 'Y' : 'N',
           (fileStat.st_mode & S_IWUSR) ? 'Y' : 'N',
           (fileStat.st_mode & S_IXUSR) ? 'Y' : 'N');
    printf("Group: Read[%c] Write[%c] Execute[%c]\n",
           (fileStat.st_mode & S_IRGRP) ? 'Y' : 'N',
           (fileStat.st_mode & S_IWGRP) ? 'Y' : 'N',
           (fileStat.st_mode & S_IXGRP) ? 'Y' : 'N');
    printf("Others: Read[%c] Write[%c] Execute[%c]\n",
           (fileStat.st_mode & S_IROTH) ? 'Y' : 'N',
           (fileStat.st_mode & S_IWOTH) ? 'Y' : 'N',
           (fileStat.st_mode & S_IXOTH) ? 'Y' : 'N');

    printf("\nPermission change demonstration completed successfully.\n");
    return 0;
}

