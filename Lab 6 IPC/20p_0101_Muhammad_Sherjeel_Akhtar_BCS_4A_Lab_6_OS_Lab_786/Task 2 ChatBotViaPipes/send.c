#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    int fd; 
    char * myfifo = "/tmp/myfifo";  
    mkfifo(myfifo, 0666); 
    char MYMESSAGE[100]; 
    char MESSAGEFROM[100];
    while (1) 
    {  
        fd = open(myfifo, O_WRONLY);   
        printf("Type Message: ");
        fgets(MYMESSAGE, 100, stdin); 
        write(fd, MYMESSAGE, strlen(MYMESSAGE)+1); 
        close(fd); 
        if (strcmp(MYMESSAGE, "ImDone\n") == 0) {
            printf("Chat Stopped By User.\n");
            break;
        }
        fd = open(myfifo, O_RDONLY); 
        read(fd, MESSAGEFROM, sizeof(MESSAGEFROM)); 
        printf("Message From Faisal: %s\n", MESSAGEFROM); 
        close(fd); 
    } 
    return 0; 
}
