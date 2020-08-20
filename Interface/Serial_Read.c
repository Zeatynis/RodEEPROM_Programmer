#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "_RodSerial_ProcessArguments.h"

const char connectionEstablished_char = 1;
 
int main(int argc, char** argv)
{
	if(_RodSerial_ProcessArguments(argc, argv))
		goto END;

	struct termios tio;
	struct termios stdio;
	struct termios old_stdio;
	int tty_fd;

	unsigned char c = 'D';

	//gets the parameters associated with the stdout object
	//and stores them in the referenced termios structure
	tcgetattr(STDOUT_FILENO, &old_stdio);

	//Clears stdio
	memset(&stdio, 0 ,sizeof(stdio));
	stdio.c_iflag = 0;
	stdio.c_oflag = 0;
	stdio.c_cflag = 0;
	stdio.c_lflag = 0;
	stdio.c_cc[VMIN] = 1;
	stdio.c_cc[VTIME]= 0;

	//sets the parameters associated with the terminal from the termios structure referred
	//TCSANOW applies those chnages NOW, immeaditely 
	tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);

	//Does the same above, but after all output written to stdio has been transmitted
	//all input that has been received but not read will be discarded before the change is made 
	tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);

	//hmmm ahh?
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // make the reads non-blocking

	memset(&tio,0,sizeof(tio));
	tio.c_iflag = 0;
	tio.c_oflag = 0;
	tio.c_cflag = CS8 | CREAD | CLOCAL; // 8n1, see termios.h for more information
	tio.c_lflag = 0;
	tio.c_cc[VMIN] =1;
	tio.c_cc[VTIME]=5;

	//open ports with the flags specified
	//O_RDWR for read/write
	tty_fd = open(PortString, O_RDWR | O_NONBLOCK);

	//sets the output baud rate stored in the termios structure pointed to
	cfsetospeed(&tio,B57600);
	cfsetispeed(&tio,B57600);


	tcsetattr(tty_fd,TCSANOW,&tio);

	//writes to tty_fd, the buffer chosen, 1 time
	write(tty_fd, &connectionEstablished_char ,1);
	
	//reads from tty_fd, to the buffer chosen, 1 time
	read(tty_fd,&c,1);
	puts("Connecting...\r");

	uint8_t count = 0;
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
			RETURN_ERROR = 1;
			goto END_WITH_CLOSE;
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

	END_WITH_CLOSE:
	//Close file used for serial comms
	close(tty_fd);

	//set stdio to old stdio parameters
	tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);

	END:
	return RETURN_ERROR;
}

/*
	ERROR NUMBER | ERROR DESCRIPTION
	1			 | Couldn't establish serial connection
	2			 | No Serial port specified
	3 			 | No File Name specified
	4			 | Invalid Argument
	5			 | Repeated Argument
*/