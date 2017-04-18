#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LSH_TOK_BUFSIZE 256
#define LSH_TOK_DELIM " \t\r\n\a"
//http://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
//http://man7.org/linux/man-pages/man3/getopt.3.html
//https://brennan.io/2015/01/16/write-a-shell-in-c/


int main(int argc, char *argv[]){
    /*
    int i = 0;
    for(i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    */
    char buffer[LSH_TOK_BUFSIZE] = {0};
    char **tokens = malloc(LSH_TOK_BUFSIZE * sizeof(char*));
    char *token;
    tokens[0] = argv[0];
while(1){
    printf(">: ");
	fgets(buffer, sizeof(buffer), stdin);
	//buffer[strcspn(buffer,"\r\n")] = 0;
    
    int position = 1;
    
    token = strtok(buffer, LSH_TOK_DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;
    
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    //free(token);
    //tokens[position] = "-1";

    
    /*int i = 0;
    for(i = 0; i < position; i++){
        printf("%s\n", tokens[i]);
    }*/
    
    
    int opt;
    while((opt = getopt(position, tokens, "li:asm46")) != -1)
        //printf("c = %c (%d)\n",(char) opt, opt);
        switch(opt) {
            case 'l':
                puts("list");
                break;
            case 'i':
                printf("set interface: %s\n", optarg);
                break;
            case 'a':
                puts("show all for selected interface");
                break;
            case 's' :
                puts("show status for selected if");
                break;
            case 'm':
                puts("show mac for selected if");
                break;
            case '4':
                puts("show ipv4 + mask for selected if");
                break;
            case '6':
                puts("show ipv4 + mask for selected if");
                break;
            default:
                printf("opt: %d\n", opt);
                fprintf(stderr, "Usage: %s [l] [-i if] [asm46]\n", argv[0]);
                //exit(EXIT_FAILURE);
        }
    
    //free(tokens);
}    
    return 0;
}