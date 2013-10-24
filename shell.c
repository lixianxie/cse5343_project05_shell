//lixian xie
//a simple unix shell.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>  
#include <stdbool.h> 
#include <sys/wait.h>


bool cmdIsExit(char* command){
	return !strcmp(command,"exit");
}
bool cmdIsType(char* command){
	return !strcmp(command,"type");
}

bool cmdIsCopy(char* command){
	return !strcmp(command,"copy");
}

bool cmdIsDelete(char* command){
	return !strcmp(command,"delete");
}

bool cmdIsExecutable(char* command){
	if(access(command,F_OK)!=-1){ //check existence first
		if(access(command,X_OK)!=-1)return 1;//X_OK means execute permission
	}else return 0;
}

int countArgs(char* cmdLine){
	char temp[100];
	strcpy(temp,cmdLine);
	char* delim;
	int i=0;
	for(delim=strtok(temp," ");delim!=NULL;delim=strtok(NULL," "))i++;
	return i;		
}

void getCommand(char* cmdLine,char* command){
	char temp[100];
	strcpy(temp,cmdLine);
	char* delim;
	if((delim=strtok(temp," "))!=NULL)strcpy(command,delim);
	else strcpy(command,"\n"); 
}

void type(char* cmdLine){
	if(countArgs(cmdLine)>2){
		printf("Error: too many arguments for type-commandline!\n");
	}else if(countArgs(cmdLine)<2){
		printf("Error: too few arguments for type-commandline!\n");
	}else{
		char* delim;
		char firstFileName[100];
		delim=strtok(cmdLine," ");
		delim=strtok(NULL," ");
		strcpy(firstFileName,delim);
		FILE *fp;
		char ch;
		if(access(firstFileName,F_OK)!=-1){      //F_OK means its existence.
			if((fp=fopen(firstFileName,"r"))!=NULL){//fp!=NULL means it can be read.
				while((ch=fgetc(fp))!=EOF)putchar(ch);
			}
		fclose(fp);
		}else printf("Error: %s doesn't exist!\n",firstFileName);
		
	}	
}

void copy(char* cmdLine){
	if(countArgs(cmdLine)>3){
		printf("Error: too many arguments for copy-commandline!\n");
	}else if(countArgs(cmdLine)<3){
		printf("Error: too few arguments for copy-commandline!\n");
	}else{
		char* delim;
		char firstFileName[100];
	 	char secondFileName[100];
		delim=strtok(cmdLine," ");
		delim=strtok(NULL," ");
		strcpy(firstFileName,delim);
		delim=strtok(NULL," ");
		strcpy(secondFileName,delim);
		if(access(firstFileName,F_OK)!=-1){
			FILE *in,*out;
			char ch;
			in=fopen(firstFileName,"r");
			out=fopen(secondFileName,"w");
			if(in!=NULL){
				while((ch=fgetc(in))!=EOF)fputc(ch,out);			
			}
			fclose(in);
			fclose(out);
		}else printf("Error: %s doesn't exist!\n",firstFileName);

	}
	
}

void delete(char* cmdLine){
	if(countArgs(cmdLine)>2){
		printf("Error: too many arguments for delete-commandline!\n");
	}else if(countArgs(cmdLine)<2){
		printf("Error: too few arguments for delete-commandline!\n");
	}else{
		char* delim;
		char firstFileName[100];
		delim=strtok(cmdLine," ");
		delim=strtok(NULL," ");
		strcpy(firstFileName,delim);
		if(access(firstFileName,F_OK)!=-1){
			if(remove(firstFileName)!=0)printf("Error: unable to delete!\n");
			//remove()=0 means it can be deleted.
		}else printf("%s doesn't exist!",firstFileName);
	} 
}

/*void execute(char* command){
	char args[1][1]='\0';
	int status;
	int subPid=fork();
	if(subPid==0){
		execvp(command,args);
		exit(status);
	}else{
		wait(status);
	}	
}*/// execute part should be wrong right now.

void error(char* cmdLine){
	printf("Command not found: %s\n",cmdLine);
}

int main(int args, char** argv){
	printf("Hello:yet unix shell!\n");
	char cmdLine[100];
	char command[100];
	while(true){
		printf("> ");
		scanf("%[^\n]%*c",cmdLine);
		getCommand(cmdLine,command); //get the 1st part(named command) from cmdLine.
		if(cmdIsExit(command)){
			break;
		}else if(cmdIsType(command)){
			type(cmdLine);
		}else if(cmdIsCopy(command)){
			copy(cmdLine);
		}else if(cmdIsDelete(command)){
			delete(cmdLine);
		}/*else if(cmdIsExecutable(command)){
			execute(cmdLine);
		}*/else{
			error(cmdLine);
		}
	}
	return 0;
}