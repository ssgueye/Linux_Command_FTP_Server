all : client.o serveur.o
	gcc serveur.o -o serveur
	gcc client.o  -o client 
client.o : client.c
	gcc -c client.c -o client.o
serveur.o : serveur.c
	gcc -c serveur.c -o serveur.o
clean :
	rm -rf *.o 