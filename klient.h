//
// Created by matus on 2. 1. 2021.
//

#ifndef SEMPRACA_KLIENT_H
#define SEMPRACA_KLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define N 1024
#define NB_CMDS 18
#define SERVER_PORT 21
#define OPEN 0  //FUNGUJE
#define CD 1    //FUNGUJE
#define MKD 2   //FUNGUJE
#define RMD 3   //FUNGUJE
#define QUIT 4  //FUNGUJE
#define DIR 5   //FUNGUJE
#define GET 6   //FUNGUJE
#define PUT 7   //FUNGUJE
#define PWD 8   //FUNGUJE
#define DEL 9   //FUNGUJE
#define HELP 10 //FUNGUJE
#define DIRU 11 //FUNGUJE
#define CDU 12  //FUNGUJE
#define PWDU 13 //FUNGUJE
#define MKDU 14 //FUNGUJE
#define RMDU 15 //FUNGUJE
#define DELU 16 //FUNGUJE
#define LS 17 //FUNGUJE

const char *PROMPT = "Pinzov a Matusov FTP> ";

void prompt(void);

void pripojit(char *, char *, char *);

void help(void);

void pwd(void);

void cd(char *);

void quit(void);

void dir(void);

void ls(void);

void del(char *);

void mkd(char *);

void rmd(char *);

void get(char *);

void put(char *);

void send_rq(int, char []);

void dirU(void);

void cdU(char *);

void pwdU(void);

void mkdU(char *);

void rmdU(char *);

void delU(char *);

void pasv(char *, int *);

#endif //SEMPRACA_KLIENT_H
