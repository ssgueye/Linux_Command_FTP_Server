/*Protocole FTP du Client*/

// Pour vous connecter, Utilser l'ID : 1ABC
 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <time.h>


void command_ls(int sock)
{
	char buffer[100], *f;
	int size;
	int fich_used;

	
		strcpy(buffer, "ls");
	    send(sock, buffer, 100, 0);
	  	recv(sock, &size, sizeof(int), 0);
	    f = malloc(size);
	    recv(sock, f, size, 0);
	    fich_used = creat(".ls.txt", O_RDWR);
	    write(fich_used, f, size, 0);

	    close(fich_used);

	    printf("La liste des répertoire/fichier de votre répertoire courant est la suivante:\n");
	    system("chmod +rw .ls.txt");
	  	system("cat .ls.txt");
	  	system("rm .ls.txt");

}

void command_cd(int sock)
{
  	char buffer[100];
  	int status;

		strcpy(buffer, "cd ");
	  	printf("Enter le chemin pour changer de répertoire: ");
	  	scanf("%s", buffer + 3);
        send(sock, buffer, 100, 0);
	  	recv(sock, &status, sizeof(int), 0);
        
        if(status)
            printf("Votre changement de répertoire est effectué avec succés: %s\n", buffer + 3);
       	else
            printf("Votre changement de répertoire n'a pas marché :(\n");
	
}

void command_pwd(int sock)
{ 
  	char buffer[100];

		strcpy(buffer, "pwd");
		send(sock, buffer, 100, 0);
		recv(sock, buffer, 100, 0);
		printf("Le chemin de votre répertoire actuel est: %s\n", buffer);
}

void command_put(int sock)
{
	struct stat obj;
	char buffer[100], fich[20];
	int size, status;
	int fich_used;

	 printf("Entrer le fichier à envoyer: ");
     scanf("%s", fich);

	  fich_used = open(fich, O_RDONLY);

      if(fich_used == -1)
        {
          printf("Ce fichier n'existe pas dans le dossier local\n\n");
        }
     
      	strcpy(buffer, "put ");
		strcat(buffer, fich);
		send(sock, buffer, 100, 0);
		stat(fich, &obj);

		size = obj.st_size;

		send(sock, &size, sizeof(int), 0);
		sendfile(sock, fich_used, NULL, size);
		recv(sock, &status, sizeof(int), 0);
          
	  if(status)
	    printf("Fichier bien stocké\n");
	  else
	    printf("Le stockage du fichier a échoué\n");
}

void command_get(int sock)
{
	int i = 1;
	char buffer[100], fich[20], *f;
	int size;
	int fich_used;

		printf("Enter fich to get: ");
	  	scanf("%s", fich);
	  	strcpy(buffer, "get ");
	  	strcat(buffer, fich);
	  	send(sock, buffer, 100, 0);
	  	recv(sock, &size, sizeof(int), 0);

	  if(!size)
	    {
	      printf("Pas de fichier de ce nom\n\n");
	    }
	    else
	    {
	    	f = malloc(size);
		  recv(sock, f, size, 0);
		  
		  fich_used = open(fich, O_CREAT | O_EXCL | O_WRONLY, 0666);
		      
		  write(fich_used, f, size, 0);
		  close(fich_used);
		  
		  strcpy(buffer, "cat ");
		  strcat(buffer, fich);
		  system(buffer);
		}
}
	   

void command_quit(int sock)
{
	char buffer[100];
	int status;

		strcpy(buffer, "quit");
        send(sock, buffer, 100, 0);
        recv(sock, &status, 100, 0);
	  
	  	if(status)
	    {
	      printf("Fermeture du Serveur\nServeur Fermé avec succés..\n");
	      exit(0);
	    }
	    printf("Déconnexion du serveur échouée..\n");
}

//Fonction main() 
int main(int argc,char *argv[])
{
	  struct sockaddr_in serveur;
	  int sock;
	  char choice[5], id[5];
	  int k;

	  printf("Bonjour, Merci de vous identifier pour accéder au serveur\n");
	  printf("ID:");
	  scanf("%s", id);

	
  		if((strcmp(id, "1ABC")==0) || (strcmp(id, "2345")==0)||(strcmp(id, "5468")==0)||(strcmp(id, "KE34")==0)||(strcmp(id, "9OLM")==0)||(strcmp(id, "9834")==0)||(strcmp(id, "IK34")==0)||(strcmp(id, "PO23")==0)||(strcmp(id, "5973")==0)||(strcmp(id, "3ERZ")==0))
  		{
	  		printf("***Identification valide***!!\n\n");

			  sock = socket(AF_INET, SOCK_STREAM, 0);

			  if(sock == -1)
			    {
			      printf("Création du Socket échouée!");
			      exit(1);
			    }
			  serveur.sin_family = AF_INET;
			  serveur.sin_port = htons(atoi(argv[1]));
			  serveur.sin_addr.s_addr = INADDR_ANY;
			  k = connect(sock,(struct sockaddr*)&serveur, sizeof(serveur));
			  if(k == -1)
			    {
			      printf("Erreur de connexion\n");
			      exit(1);
			    }
			 
			  printf("\t=======>Bienvenue sur le Serveur de port %d<=======\n",atoi(argv[1]) );
			  printf("\n Ceci est un terminal virtuel dont vous pourrez utiliser ces commmandes: ls, get, put, pwd, cd et quit(pour quitter le serveur)\n\n");
			  command_pwd(sock);

			  int i = 1;
			  while(1)
			    {
			      printf("\t====================><====================");
			      printf("\n\nTapez le nom de la commande:<");
			      scanf("%s", choice);

			    //Commande "ls"
			    if(strcmp(choice, "ls")==0)
			    {
			    	long clk_tck = CLOCKS_PER_SEC;
					clock_t t1, t2;
					int i;
					int a = 0;
   
					t1 = clock();/* Recuperation du temps initial en "clock ticks" */

					for ( i = 0; i < 10000000; i++) {a++;}

			    	command_ls(sock);

			    	t2 = clock();/* Recuperation du temps final en "clock ticks" */

			    	(void)printf("Temps consommé (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
			    } 

			    //Commande "cd"
			    else if(strcmp(choice, "cd")==0)
			    {
			    	long clk_tck = CLOCKS_PER_SEC;
					clock_t t1, t2;
					int i;
					int a = 0;

					t1 = clock();/* Recuperation du temps initial en "clock ticks" */

					for ( i = 0; i < 10000000; i++) {a++;}

			    	command_cd(sock);

			    	t2 = clock();/* Recuperation du temps final en "clock ticks" */

			    	(void)printf("Temps consommé (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
			    	
			    } 

			    //commande "pwd"
			    else if(strcmp(choice, "pwd")==0)
			    {
			    	long clk_tck = CLOCKS_PER_SEC;
					clock_t t1, t2;
					int i;
					int a = 0;
   
					t1 = clock();/* Recuperation du temps initial en "clock ticks" */
					for ( i = 0; i < 10000000; i++) {a++;}

			    	command_pwd(sock);

			    	t2 = clock();/* Recuperation du temps final en "clock ticks" */

			    	(void)printf("Temps consommé (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
			    	
			    }

			    //commande "quit"
			    else if(strcmp(choice, "quit")==0)
			    {
			   
			    	command_quit(sock);
			    	
			    }

			    //commande "put"
			    else if(strcmp(choice, "put")==0)
			    {
			    	long clk_tck = CLOCKS_PER_SEC;
					clock_t t1, t2;
					int i;
					int a = 0;

					t1 = clock();/* Recuperation du temps initial en "clock ticks" */

					for ( i = 0; i < 10000000; i++) {a++;}

			    	command_put(sock);
			    	
			    	t2 = clock();/* Recuperation du temps final en "clock ticks" */

			    	(void)printf("Temps consommé (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
			    	
			    }

			    //commande "get"
		     	else if(strcmp(choice,"get") == 0)
				{
					long clk_tck = CLOCKS_PER_SEC;
					clock_t t1, t2;
					int i;
					int a = 0;
   
					t1 = clock();/* Recuperation du temps initial en "clock ticks" */

					for ( i = 0; i < 10000000; i++) {a++;}

			    	command_get(sock);
			    	
			    	t2 = clock();/* Recuperation du temps final en "clock ticks" */

			    	(void)printf("Temps consommé (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
			  		
				}

				else
				{
					printf("Commande introuavable\n");

				}
			
		    }
		}
	  	else
	  	{
	  		printf("Identifiant invalide\n");
	  		exit(0);
	  	}

	  

    return 0;
}
