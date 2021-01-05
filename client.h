//
// Created by matus on 2. 1. 2021.
//

#ifndef SEMPRACA_CLIENT_H
#define SEMPRACA_CLIENT_H

#define N 1024
#define NB_CMDS 11

#define OPEN 0
#define CD 1
#define MKD 2
#define RMD 3
#define QUIT 4
#define DIR 5
#define GET 6
#define PUT 7
#define PWD 8
#define DEL 9
#define HELP 10


const char *PROMPT = "ftp>";

void prompt(void);

void connect(char *, char *, char *);
void help(void);


#endif //SEMPRACA_CLIENT_H
