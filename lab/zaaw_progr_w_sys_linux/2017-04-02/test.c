#include <stdio.h>

//http://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
//http://man7.org/linux/man-pages/man3/getopt.3.html
int main(int argc, char *argv[]){
    int i = 0;
    for(i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    return 0;
}