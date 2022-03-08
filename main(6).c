#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int parseInput(char *input, char *splitWords[]);
bool exitProgram(char *tokens[], int numTokens);
void printError();
void promptUser(bool isBatch);
void printHelp(char* tokens[], int numTokens);
void changeDirectories(char *tokens[], int numTokens);
char *redirectCommand(char *special, char *cmd, bool *isRedirect, char *tokens[], char *outputTokens[]);
char *executeCommand(char *cmd, bool *isRedirect, char* tokens[], char* outputTokens[],  bool *isExits);
void launchProcesses(char *tokens[], int numTokens, bool isRedirect);
int main(int argc, char *argv[])
{
    char inputz[256];
    char *parsedInputs[256];
    char *outputTokenz[256];
    bool batch=argc-1;
    bool *redirect;
    bool *Exit;
    int numOfArgs=0;
    switch(batch){
        case 0:
        while(strcmp(inputz,"exit\n")!=0){
            promptUser(batch);
        fgets(inputz, 256, stdin);
        executeCommand(inputz, redirect, parsedInputs, outputTokenz,Exit);
        }
        break;
    }
    return 0;
}
int parseInput(char *input, char *splitWords[]){
      int wordInd = 0;
      splitWords[0] = strtok(input, " ");
      while(splitWords[wordInd] != NULL){
              splitWords[++wordInd] = strtok(NULL, " ");
      }

      return wordInd;
}
bool exitProgram(char *tokens[], int numTokens){
    char key[]="exit";
    if(numTokens>1){
        printError();
        return 0;
    }
    if(strcmp(key,tokens[0])==0){
        return 1;
    }
    else{
        return 0;
    }
}
void printError(){
    printf("Shell program error occurred");
}
void promptUser(bool isBatch){
    if(isBatch==false){
       char *user;
    user=getenv("ROOT");
    printf("%s ", user);
    char host[256];
    gethostname(host,256);
    printf("%s ", host);
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    printf("%s: ", cwd);
    }

}
void printHelp(char* tokens[], int numTokens){
    char key[]="help\n";
    if(numTokens!=1){
        printError();
    }
    if(strcmp(key, tokens[0])==0){
        printf("This is my help screen.\n The commands are internally defined.\ncd changes directory.\nexit closes this program\nls lists contents of the current directory\n");
    }
}
void changeDirectories(char *tokens[], int numTokens){
    char key[]="cd\n";
    if(numTokens==2&&strcmp(key,tokens[0])==0){
        char directory[256];
        strcpy(directory,tokens[1]);
        chdir(directory);
    }
    else{
        printError();
    }
    
}
char *redirectCommand(char *special, char *cmd, bool *isRedirect, char *tokens[], char *outputTokens[]){
    int NumOfTokens;
    NumOfTokens=0;
    char *inputFile;
    char *outputFile;
    char c;
    char *command;
    strcpy(command,cmd);
    NumOfTokens=parseInput(">", command);
    if(NumOfTokens==1){
        inputFile=strtok(cmd,">");
        outputFile=strtok(NULL,">");
        FILE *one, *two;
        one=fopen(inputFile, "r");
        two=fopen(outputFile, "w");
        c=fgetc(one);
        while(c!=EOF){
            fputc(c,two);
            c=fgetc(one);
        }
        isRedirect=1;
        return outputFile;
    }
}
char *executeCommand(char *cmd, bool *isRedirect, char* tokens[], char* outputTokens[],  bool *isExits){
     char *command=strdup(cmd);
     char *output;
     char *numofgreat;
     int numOfArgs;
     numofgreat=strchr(command, '>');
     if(numofgreat==NULL){
         numOfArgs=parseInput(command,tokens);
         if(strcmp(tokens[0],"help\n")==0){
             printHelp(tokens, numOfArgs);
         }
         if(strcmp(tokens[0],"cd\n")==0){
             changeDirectories(tokens, numOfArgs);
             
         }
     }
}
void launchProcesses(char *tokens[], int numTokens, bool isRedirect){  
}
