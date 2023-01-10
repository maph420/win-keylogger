# win-keylogger
## Usage
Script will start running on background just opening the ``keylogger.vbs`` file. The process can be stopped anytime from task manager (you will notice something occupying 60% of your CPU lol).

## Manual compilation of source files

From src directory:

> gcc -Wall -o klg readfile.c keylogger.c queue.c settings.h

There are two running arguments:

* Logs file location (default location is logs/dest.txt)
* Num of seconds between key detection pauses (default time is 5 secs)

Default args execution:

> ./klg "default"

Logs will be saved at "logs/mylogs.txt" (path MUST exist):
> ./klg "mylogs/logs.txt"

Logs will be saved at default path and pauses will last 6 seconds:
> ./klg "default" 6

NOTICE: if you want the script to be ~100% effective you oughta set ``0 pause seconds``, at your own risk.