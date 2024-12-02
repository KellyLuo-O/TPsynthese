#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 128

/*
 * Fonction displayTxtConsole(char *path)
 * 
 * prend en argument le chemin du fichier à afficher 
 * et afficher le contenu du fichier dans la console standard output 
 * 
 */
void displayTxtConsole(char *path)
{
	int fd; ssize_t ret; 
	char buf[BUFSIZE];
	
	// on ouvre le fichier txt en lecture seule, on reccupere le file desriptor 
	fd = open(path, O_RDONLY);
	if (fd == 0) 
	{
		perror("open file failure");
		exit(EXIT_FAILURE);
	}
	
	// on lit le fichier qu'on a ouvert et on l'écrit dans la console
	while((ret = read(fd, buf, BUFSIZE))>0) {
		if(write(STDOUT_FILENO, buf, ret) == -1) {
			perror("error in write");
			exit(EXIT_FAILURE);
		}
	}
	
	if (ret == -1){ perror("error in read");}
	close(fd);
}


int main (int argc, char *argv[]) 
{
	
	displayTxtConsole("welcome.txt");
	displayTxtConsole("prompt.txt");
	
}

