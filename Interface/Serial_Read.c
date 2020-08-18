#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

const char connectionEstablished_char = 1;
 
int main(int argc,char** argv)
{
	struct termios tio;
	struct termios stdio;
	struct termios old_stdio;
	int tty_fd;

	unsigned char c = 'D';
	tcgetattr(STDOUT_FILENO,&old_stdio);

	memset(&stdio,0,sizeof(stdio));
	stdio.c_iflag = 0;
	stdio.c_oflag = 0;
	stdio.c_cflag = 0;
	stdio.c_lflag = 0;
	stdio.c_cc[VMIN] = 1;
	stdio.c_cc[VTIME]= 0;
	tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
	tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // make the reads non-blocking

	memset(&tio,0,sizeof(tio));
	tio.c_iflag = 0;
	tio.c_oflag = 0;
	tio.c_cflag = CS8 | CREAD | CLOCAL; // 8n1, see termios.h for more information
	tio.c_lflag = 0;
	tio.c_cc[VMIN] =1;
	tio.c_cc[VTIME]=5;

	tty_fd = open(argv[1], O_RDWR | O_NONBLOCK);
	cfsetospeed(&tio,B57600);
	cfsetispeed(&tio,B57600);

	tcsetattr(tty_fd,TCSANOW,&tio);

	write(tty_fd, &connectionEstablished_char ,1);
	
	read(tty_fd,&c,1);
	puts("Connecting...\r");

	u_int8_t count = 0;
	while(c != connectionEstablished_char)
	{
		puts("Unable to establish connection! Trying again.\r");

		for(size_t i = 0; i<700000; i++)
		{
			read(STDIN_FILENO,&c,1);
		}

		if(c == 3)
			break;

		read(tty_fd,&c,1);
		if(c == connectionEstablished_char)
			break;

		count++;
		if(count == 10)
		{
			puts("Couldn't establish connection\r");
			return 1;
			break;
		}
	}

	c = 'D';

	//Ctrl + c
	while(c && c!= 3)
	{
		// if new data is available on the serial port, print it out
		if (read(tty_fd,&c,1)>0)        write(STDOUT_FILENO,&c,1);

		// if new data is available on the console, send it to the serial port
		if (read(STDIN_FILENO,&c,1)>0)  write(tty_fd,&c,1);
	}

	close(tty_fd);
	tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);

	return EXIT_SUCCESS;
}