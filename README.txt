==========================================
Ceci est un fichier README concernant le fonctionnement du programme FTP serveur client et Makefile
=========================================
---Fonctionnement du programme----

Le dossier actuel "projet" contient trois répertoires(commandfile,  fich_test et  FTP_client_serveur) et un fichier README.txt.

Dans le "fich_test", nous avons  encore un répertoire test et un fichier test(dossier_test et fichier_test.txt).

Dans le "commandfile", nous avons deux fichiers(pwd.txt et ls.txt) qui nous permettront de mettre le résutat des commandes "ls" et "pwd" à chaque exécution. Les deux fichiers seront mise à jours à chque exécution.

Dans le fichier "FTP_client_serveur", nous avons trois fichiers(client.c, Makefile et  serveur.c).
Les fichiers "client.c" et "serveur.c" sont les codes sources respectifs pour le FTP client et le FTP serverur.
Le fichier Makefile permet de compiler de façon simplifiée les fichiers "client.c" et "serveur.c".Il suffit juste d'utilisr la commande "make" pour
faire la compilation. Aprés vous aurez les fichier exécutable du serveur et du client ainsi que les fichier .o qui leur correspondent. Vous pouvez utiliser la commande "make clean" pour supprimer les fichiers .o (ils sont optionnels).
Pour faire fonctionner le programme, on exécute les nouveaux fichier(serveur et client) dans deux terminaux en mettant d'abord "./serveur num_port" (dans l'un des deux terminaux) et "./client num_port" (dans l'autre).

==> IMPORTANT: Vous devez mettre les mêmes numéros de port. 
				Exemple: Dans le terminal 1, on met: ./serveur 1234 
						 Et dans le terminal 2, on met : ./client 1234

L'exécution du programme(./client num_port) vous demandera de vous identifier, vous pouvez dans ce cas mettre 
l'un de ces ID: 1ABC, 2345, 5468, KE34, 9OLM, 9834, IK34, PO23, 5973, 3ERZ
Le programme est un terminal virtuel, donc vous pouvez interagir avec le serveur en mettant des commandes comme "ls", "pwd", "cd", "get" et "put"

=======================================
BON USAGE!!