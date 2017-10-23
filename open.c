#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	 int filedirector = open("test.txt", O_RDWR | O_CREAT, S_IRWXU);
	 close(1);
	 dup(filedirector);
	 printf("ça marche!");
	 close(filedirector);

}
