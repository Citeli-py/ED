#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main()
{
    char tad[] = "fila";
    char main[] = "main";
    char cmd[80] = "gcc -c ";

    //printf("TAD sem a extensao: ");
    //scanf("%s", tad);
    //printf("Principal sem a extensao: ");
    //scanf("%s", main);

    strcat(cmd, tad);
    strcat(cmd, ".c -o ");
    strcat(tad, ".o");
    strcat(cmd, tad);

    printf("%s\n", cmd);
    system(cmd);

    strcpy(cmd, "gcc ");
    strcat(cmd, main);
    strcat(cmd, ".c ");
    strcat(cmd, tad);
    strcat(cmd, " -o ");
    strcat(cmd, main);
    strcat(cmd, ".exe");

    printf("%s", cmd);
    system(cmd);

    return 0;
}