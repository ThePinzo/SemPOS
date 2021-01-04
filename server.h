//
// Created by stefa on 2. 1. 2021.
//

#ifndef SEMPRACA_SERVER_H
#define SEMPRACA_SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void error(const char *msg) {
    perror(msg);
    exit(1);
};


#endif

