==========================================
This is a README file about the operation of the FTP client server program and Makefile.
=========================================
---How the program work?----

The current "project" folder contains two directories( test_file and FTP_client_server), two hidden files(.ls, .pwd and a README.txt file.

In the "test_file" we still have a test directory and a test file(test_folder and test_file.txt).
We have two files(pwd.txt and ls.txt) which will allow us to put the result of the commands "ls" and "pwd" at each execution. Both files will be updated at each execution.

In the file "FTP_client_server" we have three files(client.c, Makefile and server.c).
The files "client.c" and "server.c" are the respective source codes for the FTP client and the FTP server.
The Makefile file allows you to compile the "client.c" and "server.c" files in a simplified way, just use the "make" command to
make the compilation. Then you will have the server and client executable files and the .o files that correspond to them. You can use the "make clean" command to remove the .o files (they are optional).
To make the program work, you run the new files(server and client) in two terminals by first putting "./server num_port" (in one of the two terminals) and "./client num_port" (in the other).

==> IMPORTANT: You must put the same port numbers. 
				Example: In terminal 1, put: ./server 1234 
						 And in terminal 2, put: ./client 1234

The program(./client num_port) will ask you to identify yourself, in this case you can put 
one of these IDs: 1ABC, 2345, 5468, KE34, 9OLM, 9834, IK34, PO23, 5973, 3ERZ
The program is a virtual terminal, so you can interact with the server by putting commands like "ls", "pwd", "cd", "get", "put" and "quit".

=======================================
GOOD USE!!

Thank for following me on Github
