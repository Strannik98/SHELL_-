# SHELL
Описание задачи

Составить программу моделирующую работу Shell-интерпретатора при обработке командной строки, указанной в варианте. 
tr-d "[p-z]" < a.txt | wc -c & wc -c < a.txt

1. Процесс P0 создает информационный канал Pipe
2. Процесс P0 порождает процесс P1
3. Процесс P1 запускает tr -d “[p-z]” (чтение: файл a.txt, запись: канал Pipe)
4. Процесс P1 завершается
5. Процесс P0 порождает процесс P2
6. Процесс P2 запускает wc -c (чтение: канал Pipe, запись: консоль)
7. Процесс P2 завершается
8. Процесс P0 порождает процесс P3
9. Процесс P3 запускает wc -c < a.txt (чтение: файл a.txt, запись: консоль)
11. Процесс P3 завершается
12. Процесс P0 завершается

Компиляция:
Для создания исполняемого файла, необходим исходный файл lab6.cpp и установленный компилятор GNU C++ под ОС UNIX.
Исполняемый файл lab6.cpp компилируется командой: g++ lab6.cpp -o lab6.exe

Вызов:
· Программа вызывается из домашнего каталога
· Вызов происходит при помощи команды: ./lab6.exe

Условия вызова:
Файл a.txt находится в папке UR_TESTS домашнего каталога. 

 В программе были использованы системные вызовы

 1. int chdir(char* pathname) - смена текущего каталога на выбранный.
 2. int fork() - системный вызов fork() используется для порождения нового процесса
 3. int fcntl(int fd, char command, int argument) - системный вызов fcntl () выполняет действия по разделению пользовательских дескрипторов в зависимости от пяти значений аргумента command, специфицированных в файле fcntl.h.
 4. int pipe(int *fildes) - создание канала
 5. sleep(int t) - приостановить выполнение на заданный интервал времени
 6. int wait(int *status) - ожидание завершения процесса-потомка родительским процессом
 7. execl(name, arg0, arg1, ... , argn, 0) - осуществляется смена программы, определяющей функционирование данного процесса
 8. exit(int status) - завершить процесс


 Аргумент status является статусом завершения, который передается отцу процесса, если он выполнял системный вызов wait(). 
