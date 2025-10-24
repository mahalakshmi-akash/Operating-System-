#include <stdio.h>
#include <string.h>

struct Directory {
    char fname[10][20];  // up to 10 files, each up to 19 chars + '\0'
    int count;
};

int main() {
    struct Directory dir;
    dir.count = 0;
    int choice;
    char name[20];

    while (1) {
        printf("\n1. Create File\n2. Delete File\n3. Search File\n4. Display Files\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (dir.count >= 10) {
                    printf("Directory full! Cannot create more files.\n");
                    break;
                }
                printf("Enter file name: ");
                scanf("%s", name);

                int exists = 0;
                for (int i = 0; i < dir.count; i++) {
                    if (strcmp(name, dir.fname[i]) == 0) {
                        exists = 1;
                        break;
                    }
                }

                if (exists)
                    printf("File already exists!\n");
                else {
                    strcpy(dir.fname[dir.count], name);
                    dir.count++;
                    printf("File created successfully.\n");
                }
                break;
            }

            case 2: {
                if (dir.count == 0) {
                    printf("Directory is empty.\n");
                    break;
                }
                printf("Enter file name to delete: ");
                scanf("%s", name);

                int found = 0;
                for (int i = 0; i < dir.count; i++) {
                    if (strcmp(name, dir.fname[i]) == 0) {
                        for (int j = i; j < dir.count - 1; j++) {
                            strcpy(dir.fname[j], dir.fname[j + 1]);
                        }
                        dir.count--;
                        found = 1;
                        printf("File deleted successfully.\n");
                        break;
                    }
                }
                if (!found)
                    printf("File not found.\n");
                break;
            }

            case 3: {
                if (dir.count == 0) {
                    printf("Directory is empty.\n");
                    break;
                }
                printf("Enter file name to search: ");
                scanf("%s", name);

                int present = 0;
                for (int i = 0; i < dir.count; i++) {
                    if (strcmp(name, dir.fname[i]) == 0) {
                        printf("File found.\n");
                        present = 1;
                        break;
                    }
                }
                if (!present)
                    printf("File not found.\n");
                break;
            }

            case 4: {
                if (dir.count == 0)
                    printf("Directory is empty.\n");
                else {
                    printf("Files in directory:\n");
                    for (int i = 0; i < dir.count; i++)
                        printf("%s\n", dir.fname[i]);
                }
                break;
            }

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please enter 1–5.\n");
        }
    }
}

