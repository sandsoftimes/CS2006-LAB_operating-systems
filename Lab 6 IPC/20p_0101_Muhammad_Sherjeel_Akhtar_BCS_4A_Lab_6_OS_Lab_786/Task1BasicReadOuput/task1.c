#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>


int main() {
    int n; 
    int p[2];
    int file;
    char buffer[1025];

  if ((file=open("file.txt", O_RDONLY))<0)
    exit(2);
  if (pipe(p) < 0)
    exit(1);

  if((n=read(file, buffer, sizeof(buffer))) >=0){
      printf("File Context: %s\n", buffer);
    }
    else{
        perror("read");
        exit(0);
    }
    return 0;
}