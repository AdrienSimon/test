#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define TRUE 1
int main (void){
	int fd;
	fd=open("verrou.txt",O_RDWR);
	int a;
	while(TRUE)
	{
		a=rand(1100000,9999999);
		if(lockf(fd,F_TLOCK,0)==0)
		{
			printf(" %d", a);
			printf(" %d", a);
			lockf(fd,F_LOCK,0);
			if(lockf(fd,F_ULOCK,0)==0)

			{
				printf(" %d", a);
				
			}
		}
			else
			{
				printf("\nattente\n");
				sleep(1);
			}
		
	}

}
