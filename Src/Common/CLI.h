#include <stdio.h>
#include <string.h>

#include "terminal.h"
#include "defines.h"

void ModifiyFileName(char *file)
{
    static char defaultFile[BUFFER_MAX_LEN] = { 0 };
    sprintf(defaultFile, "Maps/%s/%s.txt", PHASE, file + 1);
    strcpy(file, defaultFile);
}

int IsFileFromMapSet(const char *file)
{
    return file[0] == '!';
}

const char *GetFileName(int (*isFileValid)(const char *))
{
    static char fileName[256];
    int isValid = 0;
    while(!isValid)
    {
        printf("Enter map file name: ");
        scanf("%s", fileName);

        if(IsFileFromMapSet(fileName)) {
            ModifiyFileName(fileName);
            printf("Loading %s from default instead\n", fileName);
        }
        isValid = isFileValid(fileName);
        if(!isValid) {
            printf("File not found.\n");
        }
    }
    return fileName;
}


int IsFileValid(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}
