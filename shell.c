// lixianxie	
// a simple unix shell.


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void error();
bool cmdIsExit(char* command);
int cmdIsTyepe();
int cmdIsCopy();
int cmdIsDelete();
int cmdIsExecutable();
void type();
char* filenname();
char* filename();
void copy();
void delete();
void excute();


int main(int argc, char** argv) {
	printf("hello world!\n");
	char command[100];
        while(true){
		printf("> ");
		scanf("%s",command);
		if(cmdIsExit(command)){
			break;			
			}

	}
	return 0;
}


bool cmdIsExit(char* command){
	return !strcmp(command,"exit");
	}
