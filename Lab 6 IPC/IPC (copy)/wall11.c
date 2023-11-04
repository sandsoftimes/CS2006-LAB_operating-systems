#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    mkfifo(myfifo, 0666); 
  
    char MYMESSAGE[100]; 
    while (1) 
    { 
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
  
        // Take an input MYMESSAGE from user.  
        printf("Type Message: ");
        fgets(MYMESSAGE, 100, stdin); 
  
        // Write the input MYMESSAGE on FIFO 
        // and close it 
        write(fd, MYMESSAGE, strlen(MYMESSAGE)+1); 
        close(fd); 
    } 
    return 0; 
}
