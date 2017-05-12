#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> //memcpy
#define BUFF_SIZE 256
#define CDELIM "="

typedef struct config{
	int *port = NULL;
	int *max_clients = NULL;
} config;


struct config load_cfg(char * fname){
	config result;
	FILE * file = fopen(fname, "r");

	if(file != NULL){
		char line[BUFF_SIZE];
		int i = 0;
		while(fgets(line, sizeof(line), file) != NULL){
			char *cfline;
			cfline = strstr((char*)line, CDELIM);
			cfline = cfline + strlen(CDELIM);
			if (i == 0){
				memcpy(result.port, cfline, strlen(cfline));
			} else if (i == 1){
				memcpy(result.max_clients, cfline, strlen(cfline));
			}
			i++;
		} // end while
		fclose(file);
	} // end if(file!=NULL)
	return result;
}

int main(int argc, char **argv){
//arg z linii
	if (argc < 2){
		printf("Usage: %s config_file_name\n", argv[0]);
		exit(0);
	}

	config cfg = load_cfg(argv[1]);

	printf("Config:port, %d",*cfg.port);
	printf("Config:max_clients, %d",*cfg.max_clients);


	return 0;
}