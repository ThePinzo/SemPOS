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
#define NB_CMDS 11
#define SERVER_PORT 21
#define OPEN 0  //TEORETICKY POJDE/bez hesla zatial/
#define CD 1    //kk
#define MKD 2   //kk
#define RMD 3   //kk
#define QUIT 4  //kk
#define DIR 5   //kk
#define GET 6   //
#define PUT 7   //
#define PWD 8   //kk
#define DEL 9   //kk
#define HELP 10 //kk


const char *PROMPT = "Pinzov a Matusov FTP>";

void prompt(void);

void pripojit(char *, char *, char *);

void help(void);

void pwd(void);

void cd(char *);

void quit(void);

void dir(void);

void del(char *);

void mkd(char *);

void rmd(char *);

#endif //SEMPRACA_KLIENT_H