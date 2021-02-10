/*Protocole FTP serveur*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <time.h>



int main(int argc,char *argv[])
{
  struct sockaddr_in serveur, client;
  struct stat obj;
  int sock1, sock2;
  char buffer[100], command[5], fich[20];
  int k, i, size, len, c;
  int fich_used;
  sock1 = socket(AF_INET, SOCK_STREAM, 0);

  if(sock1 == -1)
    {
      printf("La Création du Socket a échoué");
      exit(1);
    }
  	serveur.sin_family = AF_INET;
	serveur.sin_port = htons(atoi(argv[1]));
	serveur.sin_addr.s_addr = htonl(INADDR_ANY);

	for(i = 0; i< 8; i++)
	{
		serveur.sin_zero[i] = 0;
	}
	k = bind(sock1, (struct sockaddr *)&serveur, sizeof(serveur));
	if(k < 0)
	{
		printf("Erreur du Bind\n");
		exit(EXIT_FAILURE);
	}

  k = listen(sock1,1);
  if(k == -1)
    {
      printf("Listen a échoué\n");
      exit(1);
    }
  len = sizeof(client);
  sock2 = accept(sock1,(struct sockaddr*)&client, &len);

  i = 1;
  while(1)
    {
      recv(sock2, buffer, 100, 0);
      sscanf(buffer, "%s", command);
      if(!strcmp(command, "ls"))
	{
	  system("ls >.ls.txt");
	  i = 0;
	  stat(".ls.txt",&obj);
	  size = obj.st_size;
	  send(sock2, &size, sizeof(int),0);
	  fich_used = open(".ls.txt", O_RDONLY);
	  sendfile(sock2,fich_used,NULL,size);
	}

      else if(!strcmp(command,"get"))
	{
	  sscanf(buffer, "%s%s", fich, fich);
	  stat(fich, &obj);
	  fich_used = open(fich, O_RDONLY);
	  size = obj.st_size;
	  if(fich_used == -1)
	      size = 0;
	  send(sock2, &size, sizeof(int), 0);
	  if(size)
	  sendfile(sock2, fich_used, NULL, size);
      
	}
      else if(!strcmp(command, "put"))
    {
	  int c = 0, len;
	  char *f;
	  sscanf(buffer+strlen(command), "%s", fich);
	  recv(sock2, &size, sizeof(int), 0);
	  i = 1;
	  while(1)
	    {
	      fich_used = open(fich, O_CREAT | O_EXCL | O_WRONLY, 0666);
	      if(fich_used == -1)
		{
		  sprintf(fich + strlen(fich), "%d", i);
		}
	      else
		break;
	 	}
	  f = malloc(size);
	  recv(sock2, f, size, 0);
	  c = write(fich_used, f, size);
	  close(fich_used);
	  send(sock2, &c, sizeof(int), 0);
    }
      else if(!strcmp(command, "pwd"))
	{
	  system("pwd > .pwd.txt");
	  i = 0;
          FILE*f = fopen(".pwd.txt","r");
          while(!feof(f))
            buffer[i++] = fgetc(f);
          buffer[i-1] = '\0';
	  fclose(f);
          send(sock2, buffer, 100, 0);
	}
      else if(!strcmp(command, "cd"))
        {
          if(chdir(buffer+3) == 0)
	    c = 1;
	  else
	    c = 0;
          send(sock2, &c, sizeof(int), 0);
        }
      else if(!strcmp(command, "bye") || !strcmp(command, "quit"))
	{
	  printf("Le serveur FTP a quitté ..\n");
	  i = 1;
	  send(sock2, &i, sizeof(int), 0);
	  exit(0);
	}
    }
    
  return 0;
}