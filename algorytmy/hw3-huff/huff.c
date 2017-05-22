/*
 * @author Tomasz Piątek
 * @brief Huffman encoding algorithm
 */

/*
	load input
	gen dictionary
	save to file
	encode input 
	print encoded data
 */


#include <stdio.h>
#include <stdlib.h> //exit
//------------------------------------------------MACROS
#define PEXIT(str) {perror(str);exit(1);}
//------------------------------------------------DEF
//------------------------------------------------PROTO
void usage(const char* argv);
char* load_file(char* filename);

//------------------------------------------------MAIN
int main(int argc, char **argv){
	
	char* text = NULL;

	if (argc < 2){
		usage(argv[0]);
	} else {
		//load file

		text = load_file(argv[1]);
		puts(text);

	}

	free(text);
	return 0;
}
//------------------------------------------------FUNCS
void usage(const char* file){
		printf("Simple Huffman tree generator\n");
		printf("Usage: %s file_to_encode \n", file);
		exit(0);
}

char* load_file(char* fn){
	char* data = NULL;
	FILE *f;
	size_t sz;

	f = fopen(fn, "rb");
	if(!f){
		PEXIT("File does not exist");
	}

	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	data = (char*) malloc(sz);
	if(data == NULL){
		fclose(f);
		PEXIT("Can't malloc for file");
	}

	fread(data, 1, sz, f);
	fclose(f);
	data[sz] = '\0';
	return(data);
}