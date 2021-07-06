#include <sys/wait.h>

#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <unistd.h>

main() {

//changing home directory to working directory

chdir("UR_tests");

//file descriptor | channel descriptor | process's id

int f, fd[2], id_1, id_2, id_3;

printf("P0: begin [%d]\n", getpid());

//creating pipe

if (pipe(fd) == -1)

{

fprintf(stderr, "Pipe didn't created.\n");

exit(1);

}

printf("P0: Pipe created\n");

//create fork P1

id_1 = fork();

if (id_1 == 0) {

printf("P1: begin\n");

//opening file a.txt

f = open("a.txt", O_RDONLY);

printf("P1: open a.txt\n");

//closing standard read file

close(0);

//making file read descriptor the standart read file

fcntl(f, F_DUPFD, 0);

//closing standard write file

close(1);

//making channel write descriptor the standart write file

fcntl(fd[1], F_DUPFD, 1);

//calling tr -d "[p-z]" function

execl("/usr/bin/tr", "tr", "-d", "\"[p-z]\"", 0);

//P1 exit

exit(0);

}

printf("P0: wait for P1\n");

//P0 wait for P1 exit

wait(&id_1);

//case of success exit

if (id_1 == 0) {

printf("P1: a.txt -> (tr -d \"[p-z]\") -> Pipe\n");

printf("P1: exit\n");

}

//closing channel write descriptor

close(fd[1]);

printf("P0: close Pipe for write\n");

//create fork P2

id_2 = fork();

if (id_2 == 0) {

printf("P2: begin\n");

//closing standard read file

close(0);

//making channel read descriptor the standart read file

fcntl(fd[0], F_DUPFD, 0);

printf("P2: Pipe -> (wc -c) -> \n");

//calling wc -c function

execl("/usr/bin/wc", "wc", "-c", 0);

//P2 exit

exit(0);

}

sleep(1);//some wait

//create fork P3

id_3 = fork();

if (id_3 == 0) {

printf("P3: begin\n");

//open file a.txt

f = open("a.txt", O_RDONLY);

//closing standard read file

close(0);

//making file read descriptor the standart read file

fcntl(f, F_DUPFD, 0);

printf("P3: a.txt -> (wc -c < a.txt) ->\n");

//calling wc -c function

execl("/usr/bin/wc", "wc", "-c", 0);

//P3 exit

exit(0);

}

printf("P0: wait for P2\n");

wait(&id_2);

//case of success exit

if(id_2 == 0) printf("P2: exit\n");

printf("P0: wait for P3\n");

wait(&id_3);

//case of success exit

if (id_3 == 0) printf("P3: exit\n");

printf("P0: close a.txt\n");

//closing file a.txt

close(f);

printf("P0: close Pipe for read\n");

//closing channel read descriptor

close(fd[0]);

printf("P0: exit\n");

return 0;

} 
