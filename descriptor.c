#include<fcntl.h>
#include<unistd.h>

int main(){
	int descriptor;
	char buffer[100];
	descriptor = open("out.txt", O_RDWR | O_CREAT, S_IRWXU);
	ssize_t n;
	while ((n=read(0,buffer,50))>0){
		write(descriptor, buffer, n);
	}
	
	close(descriptor);
}
