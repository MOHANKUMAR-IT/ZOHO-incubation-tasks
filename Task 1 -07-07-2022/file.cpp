#include<stdio.h>
#include<stdlib.h>

#define SIZE 1024

int main()
{
    FILE *fp;
    char *buf = (char*)malloc(SIZE);
    size_t nread;

    fp = fopen("D:/read.txt", "r");
    if(fp)
    {
        while(fgets(buf, SIZE, fp) != NULL)
        {
            printf("%s", buf);
        }
    }
    fclose(fp);
    return 0;
}