#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 128

/* void displayTxtConsole(char *path)
 * 
 * prend en argument le chemin du fichier à afficher 
 * et afficher le contenu du fichier dans la console standard output 
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


/* string readConsole(void)
 * 
 * lit ce qui est écrit dans la console et le retourne en string 
 */
char *readConsole(void) 
{
	ssize_t ret; 
	char *buf = malloc(BUFSIZE);
	
	// on lit la console et on met le truc dans la variable buf
	ret = read(STDIN_FILENO, buf, BUFSIZE - 1);

	if (ret == -1){ perror("error in read");}
	
	return buf;
}

int main (int argc, char *argv[]) 
{
	
	displayTxtConsole("welcome.txt");
	
	while(1) 
	{
		displayTxtConsole("prompt.txt");
		char *command = readConsole();
		command[strcspn(command, "\n")] = 0;	// supprime le retourn a la ling \n à la fin de la commande 
		
		// gestion du exit 
		 if (strcmp(command, "exit") == 0) {
            displayTxtConsole("byebye.txt");
            exit(EXIT_SUCCESS);
        }
		
		// fork et on verifie qu'il n'y a pas d'erreur
		pid_t pid = fork();
		if(pid < 0){
			perror("Erreur lors du fork");
			return EXIT_FAILURE;
		}
		
		// le fork enfant execute la commande 
		if (pid == 0) {
			execvp(command, (char *[]) {command, NULL}); // on execute la commande en ajoute le NULL à la fin de la chaine
			perror("Erreur lors de l'exécution de la commande");
			exit(EXIT_FAILURE);
		}
		// le fork parent attend au cas ou son enfant se fait tué 
		else 
		{
			int status; 
			wait(&status);
			if (!WIFEXITED(status)) 
			{
				exit(EXIT_FAILURE);
			}
		}
		
	}
	
	
}

