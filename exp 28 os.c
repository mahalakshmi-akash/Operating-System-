#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[100], pattern[20];
    fp = fopen("sample.txt", "r");
    printf("Enter pattern to search: ");
    scanf("%s", pattern);
    while(fgets(line, sizeof(line), fp))
        if(strstr(line, pattern))
            printf("%s", line);
    fclose(fp);
    return 0;
}

