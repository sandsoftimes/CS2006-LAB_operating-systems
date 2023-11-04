#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    int fd1; 
    char * myfifo = "/tmp/myfifo";  
    mkfifo(myfifo, 0666); 
    char MYMESSAGE[100];
    char MESSAGEFROM[100]; 
    while (1) 
    { 
        fd1 = open(myfifo,O_RDONLY); 
        read(fd1, MESSAGEFROM, 100); 
        if (strcmp(MESSAGEFROM, "Stop\n") == 0) {
            printf("Chat stopped by user.\n");
            close(fd1);
            break;
        } 
        printf("Message From Ali Shahid: %s\n", MESSAGEFROM); 
        close(fd1);  
        fd1 = open(myfifo,O_WRONLY); 
        printf("Type Message: ");
        fgets(MYMESSAGE, 100, stdin);  
        write(fd1, MYMESSAGE, strlen(MYMESSAGE)+1); 
        close(fd1); 
        if (strcmp(MYMESSAGE, "ImDone\n") == 0) {
            printf("Chat Stopped by user.\n");
            break;
        }
    } 
    return 0; 
}
