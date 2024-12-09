#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 128

/* void displayTxtConsole(char *path)
 * 
 * take in argument the path of the file to display 
 * displays the content of the file in the console standard output
 */
void displayTxtConsole(char *path)
{
	int fd; ssize_t ret; 
	char buf[BUFSIZE];
	
	// open the .txt file in read only and get the file descriptor
	fd = open(path, O_RDONLY);
	if (fd == 0) 
	{
		perror("open file failure");
		exit(EXIT_FAILURE);
	}
	
	// read the file et write the content stored in buf in the console
	while((ret = read(fd, buf, BUFSIZE))>0) {
		if(write(STDOUT_FILENO, buf, ret) == -1) {
			perror("error in write");
			exit(EXIT_FAILURE);
		}
	}
	
	// if error in reading 
	if (ret == -1){ perror("error in read");}
	close(fd);
}


/* char *readConsole(void)
 * 
 * read what is written in the console and return it with a char pointer
 */
char *readConsole(void) 
{
	ssize_t ret; 
	char *buf = malloc(BUFSIZE);
	
	// what is read is in buf
	ret = read(STDIN_FILENO, buf, BUFSIZE - 1);

	if (ret == -1){ perror("error in read");}
	
	return buf;
}

/* void ifExit(char * command)
 * 
 * management of the shell exit 
 */
void ifExit(char * command) 
{
	 if (strcmp(command, "exit") == 0) {
		displayTxtConsole("byebye.txt");
		exit(EXIT_SUCCESS);
	}
}

int main (int argc, char *argv[]) 
{
	int status; 
	// displays welcome message 
	displayTxtConsole("welcome.txt");
	
	while(1) 
	{
		displayTxtConsole("prompt.txt");
		char *command = readConsole();
		command[strcspn(command, "\n")] = 0;	// delete the \n at the end of the command
		
		ifExit(command);
		
		// fork and we check there is no error 
		pid_t pid = fork();
		if(pid < 0){
			perror("Erreur forking");
			return EXIT_FAILURE;
		}
		
		// the fork children execute the command with
		if (pid == 0) {
			execvp(command, (char *[]) {command, NULL}); // children execute command 
			perror("Erreur when executing command");
			exit(EXIT_FAILURE);
		}
		// the fork parent wait in case something wrong happens to his children
		else 
		{
			wait(&status);
			if (!WIFEXITED(status)) 
			{
				exit(EXIT_FAILURE);
			}
		}	
	}
}

