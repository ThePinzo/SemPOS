//
// Created by stefa on 5. 1. 2021.
//

#include "klient.h"


static char *prikazy[NB_CMDS] = {
        "open", "cd", "mkd", "rmd", "quit", "dir", "get", "put", "pwd", "del", "help", "dirU", "cdU", "pwdU", "mkdU",
        "rmdU", "delU", "ls"
};
int sd = 0;
int dat_soc = 0;
int connected = 0;


int main(int argc, char *argv[]) {
    char buffer[N], *param;
    char uname[N], pass[N];
    int j = 0;

    do {
        memset(buffer, '\0', N * sizeof(char));
        memset(uname, '\0', N * sizeof(char));
        memset(pass, '\0', N * sizeof(char));

        prompt();
        gets(buffer);

        param = strchr(buffer, ' ');
        if (param) {
            *param = 0;
            param++;
        }
        for (int i = 0; i < NB_CMDS; i++)
            if (!strcmp(buffer, prikazy[i])) {
                j = i;
                break;
            }
        if (j == 0 && strcmp(buffer, "open") != 0) {
            printf("Unkown command\n");
            j = 10;
        }
        switch (j) {
            case (OPEN):
                if (strcmp(buffer, "") != 0) {
                    if (connected == 1) printf("You are already connected\n");
                    else {
                        printf("Username: ");
                        gets(uname);
                        if (strcmp(uname, "anonymous") != 0) {
                            printf("Password: ");
                            gets(pass);
                            if (strcmp(pass, "") == 0) {
                                printf("Enter your password please!\n");
                                break;
                            }
                        }
                        if (strcmp(uname, "") != 0) {
                            pripojit(argv[1], uname, pass);
                        }
                    }
                }
                break;
            case (PWD):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else pwd();
                break;
            case (CD):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    if (param == NULL || strcmp(param, "") == 0) {
                        printf("Enter parameter please!\n");
                        break;
                    } else {
                        cd(param);
                    }
                }
                break;

            case (QUIT):
                quit();
                return 0;
            case (MKD):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    if (param == NULL || strcmp(param, "") == 0) {
                        printf("Enter parameter please!\n");
                        break;
                    } else {
                        mkd(param);
                    }
                }
                break;
            case (RMD):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    if (param == NULL || strcmp(param, "") == 0) {
                        printf("Enter parameter please!\n");
                        break;
                    } else {
                        rmd(param);
                    }
                }
                break;
            case (DIR):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    dir();
                }
                break;
            case (DEL):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    if (param == NULL || strcmp(param, "") == 0) {
                        printf("Enter parameter please!\n");
                        break;
                    } else {
                        del(param);
                    }
                }
                break;
            case (GET):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    if (param == NULL || strcmp(param, "") == 0) {
                        printf("Enter parameter please!\n");
                        break;
                    } else {
                        get(param);
                    }
                }
                break;
            case (PUT):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    if (param == NULL || strcmp(param, "") == 0) {
                        printf("Enter parameter please!\n");
                        break;
                    } else {
                        put(param);
                    }
                }
                break;
            case (HELP):
                help();
                break;
            case (DIRU):
                dirU();
                break;
            case (CDU):
                if (param == NULL || strcmp(param, "") == 0) {
                    printf("Enter parameter please!\n");
                    break;
                } else {
                    cdU(param);
                }
                break;
            case (PWDU):
                pwdU();
                break;
            case (RMDU):
                if (param == NULL || strcmp(param, "") == 0) {
                    printf("Enter parameter please!\n");
                    break;
                } else {
                    rmdU(param);
                }
                break;
            case (MKDU):
                if (param == NULL || strcmp(param, "") == 0) {
                    printf("Enter parameter please!\n");
                    break;
                } else {
                    mkdU(param);
                }
                break;
            case (DELU):
                if (param == NULL || strcmp(param, "") == 0) {
                    printf("Enter parameter please!\n");
                    break;
                } else {
                    delU(param);
                }
                break;
            case (LS):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    ls();
                }
                break;
            default:
                help();
                break;
        }


    } while (1);
}

void help(void) {
    printf("Prikazy pre pracu s klientom: \n");
    printf("Pozor! Prikazy su case-sensitive!\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("quit    Zatvori ftp klienta\n");
    printf("open    Pripoji klienta ku serveru\n");
    printf("cd      Zmeni sa pracovny adresar na serveri\n");
    printf("pwd     Zobrazi cesta ku pracovnemu adresaru na serveri\n");
    printf("get     Stiahne subor zo serveru\n");
    printf("put     Nahra subor na server\n");
    printf("del     Vymaze subor na serveri\n");
    printf("mkd     Vytvori adresar na serveri\n");
    printf("rmd     Vymaze adresar na serveri\n");
    printf("dir     Zobrazi sa obsah pracovneho adresara na serveri\n");
    printf("ls      Zobrazi sa obsah pracovneho adresara na serveri\n");
    printf("help    Zobrazi zoznam pouzitelnych prikazov\n");
    printf("cdU     Zmeni sa pracovny adresar u klienta\n");
    printf("pwdU    Zobrazi cesta ku pracovnemu adresaru u klienta\n");
    printf("dirU    Zobrazi sa obsah pracovneho adresara u klienta\n");
    printf("mkdU    Vytvori adresar u klienta\n");
    printf("rmdU    Vymaze adresar u klienta\n");
    printf("delU    Vymaze subor u klienta\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void prompt(void) {
    printf("%s", PROMPT);
    fflush(stdout);
}

void pwd(void) {
    char buffer[N];
    char *pwd = "XPWD\r\n";

    send_rq(sd, pwd);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);
}

void cd(char *repo) {
    char chd[N];
    char bufffer[N];

    memset(chd, '\0', N * sizeof(char));
    strcat(chd, "CWD ");
    strcat(chd, repo);
    strcat(chd, "\n");

    send_rq(sd, chd);

    memset(bufffer, '\0', N * sizeof(char));
    if (recv(sd, bufffer, sizeof(bufffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("cd %s \n", bufffer);
}

void quit(void) {
    char *quit = "QUIT\r\n";
    char buffer[N];

    send_rq(sd, quit);
    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

    close(sd);
    sd = 0;

}

void dir(void) {
    char ipAddr[32];
    int port;
    char *dir = "LIST\r\n";
    char buffer[N];
    int tolen;
    struct sockaddr_in to;
    struct hostent *host;

    pasv(ipAddr, &port);

    dat_soc = socket(AF_INET, SOCK_STREAM, 0);
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = htons(INADDR_ANY);
    host = gethostbyname(ipAddr);
    memcpy(&(to.sin_addr), host->h_addr, host->h_length);
    tolen = sizeof(to);
    to.sin_port = htons(port);


    if (connect(dat_soc, (struct sockaddr *) &to, tolen) < 0) {
        perror("Error connecting socket");
        exit(1);
    }

    send_rq(sd, dir);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    bzero(buffer, sizeof(buffer));

    if (recv(dat_soc, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    bzero(buffer, sizeof(buffer));
    close(dat_soc);

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);


}

void del(char *file) {
    char del[N];
    char buffer[N];

    memset(del, '\0', N * sizeof(char));
    strcat(del, "DELE ");
    strcat(del, file);
    strcat(del, "\n");

    send_rq(sd, del);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

}

void mkd(char *directory) {
    char mkd[N];
    char buffer[N];

    memset(mkd, '\0', N * sizeof(char));
    strcat(mkd, "XMKD ");
    strcat(mkd, directory);
    strcat(mkd, "\n");

    send_rq(sd, mkd);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

}

void pripojit(char *host_serv, char *uname, char *password) {
    struct sockaddr_in to;
    struct hostent *host;
    int tolen;
    char buffer[N];
    char user[N];
    char pass[N];

    memset(user, '\0', N * sizeof(char));
    memset(pass, '\0', N * sizeof(char));

    sd = socket(AF_INET, SOCK_STREAM, 0);
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = htons(INADDR_ANY);
    host = gethostbyname(host_serv);
    memcpy(&(to.sin_addr), host->h_addr, host->h_length);
    tolen = sizeof(to);
    to.sin_port = htons(SERVER_PORT);


    if (connect(sd, (struct sockaddr *) &to, tolen) < 0) {
        perror("Error connecting socket");
        exit(1);
    }

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recievieng");
        exit(5);
    } else { printf("%s \n", buffer); }

    //USER
    if (strcmp(uname, "anonymous") != 0) {
        strcat(user, "user ");
        strcat(user, uname);
        strcat(user, "\r\n");

        send_rq(sd, user);

        memset(buffer, '\0', N * sizeof(char));

        if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
            perror("Error recievieng");
            exit(5);
        } else printf("%s\n", buffer);

        strcat(pass, "PASS ");
        strcat(pass, password);
        strcat(pass, "\r\n");

        send_rq(sd, pass);

        memset(buffer, '\0', N * sizeof(char));

        if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
            perror("Error recievieng");
            exit(5);
        } else printf("%s\n", buffer);
        connected = 1;
    } else {
        strcat(user, "user ");
        strcat(user, uname);
        strcat(user, "\n");

        send_rq(sd, user);

        memset(buffer, '\0', N * sizeof(char));

        if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
            perror("Error recievieng");
            exit(5);
        } else printf("%s\n", buffer);

        connected = 1;
    }
}

void rmd(char *directory) {
    char rmd[N];
    char buffer[N];

    memset(rmd, '\0', N * sizeof(char));
    strcat(rmd, "XRMD ");
    strcat(rmd, directory);
    strcat(rmd, "\n");

    send_rq(sd, rmd);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

}

void send_rq(int sock, char command[]) {

    if (send(sock, command, strlen(command), 0) < 0) {
        perror("Error sending");
        exit(2);
    }
}

void get(char *file) {
    char ipAddr[32];
    int port;
    char get[N];
    char buffer[N];
    int tolen;
    FILE* fd;
    struct sockaddr_in to;
    struct hostent *host;

    memset(get, '\0', N * sizeof(char));

    strcat(get, "RETR ");
    strcat(get, file);
    strcat(get, "\r\n");

    pasv(ipAddr, &port);

    dat_soc = socket(AF_INET, SOCK_STREAM, 0);
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = htons(INADDR_ANY);
    host = gethostbyname(ipAddr);
    memcpy(&(to.sin_addr), host->h_addr, host->h_length);
    tolen = sizeof(to);
    to.sin_port = htons(port);

    if (connect(dat_soc, (struct sockaddr *) &to, tolen) < 0) {
        perror("Error connecting socket");
        exit(1);
    }

    send_rq(sd, get);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    bzero(buffer, sizeof(buffer));

    if(recv(dat_soc, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    }

    fd = fopen(file, "w");

    fwrite(buffer, sizeof(char), strlen(buffer) , fd);

    fclose(fd);
    close(dat_soc);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);
}

void put(char *file) {
    char ipAddr[32];
    int port;
    char put[N];
    char buffer[N];
    int tolen;
    FILE* fd;
    struct sockaddr_in to;
    struct hostent *host;

    memset(put, '\0', N * sizeof(char));

    strcat(put, "STOR ");
    strcat(put, file);
    strcat(put, "\r\n");

    pasv(ipAddr, &port);

    dat_soc = socket(AF_INET, SOCK_STREAM, 0);
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = htons(INADDR_ANY);
    host = gethostbyname(ipAddr);
    memcpy(&(to.sin_addr), host->h_addr, host->h_length);
    tolen = sizeof(to);
    to.sin_port = htons(port);

    if (connect(dat_soc, (struct sockaddr *) &to, tolen) < 0) {
        perror("Error connecting socket");
        exit(1);
    }

    send_rq(sd, put);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    bzero(buffer, sizeof(buffer));

    fd = fopen(file, "r");

    fread(buffer, sizeof(char), N, fd);

    send_rq(dat_soc, buffer);

    fclose(fd);
    close(dat_soc);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

}

void dirU() {
    system("dir");
}

void cdU(char *directory) {
    char dir[N];
    memset(dir, '\0', N * sizeof(char));
    strcat(dir, directory);
    chdir(dir);
}

void pwdU() {
    system("pwd");
}

void mkdU(char *directory) {
    char dir[N];
    memset(dir, '\0', N * sizeof(char));
    strcat(dir, "mkdir ");
    strcat(dir, directory);
    system(dir);
}

void rmdU(char *directory) {
    char dir[N];
    memset(dir, '\0', N * sizeof(char));
    strcat(dir, "rmdir ");
    strcat(dir, directory);
    system(dir);
}

void delU(char *file) {
    char del[N];
    memset(del, '\0', N * sizeof(char));
    strcat(del, "rm ");
    strcat(del, file);
    system(del);
}

void pasv(char *ipaddr, int *port) {
    char *pasv = "PASV \r\n";
    char buffer[N];
    char *find;
    int a, b, c, d, pa, pb;
    send_rq(sd, pasv);

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s\n", buffer);
    find = strrchr(buffer, '(');
    sscanf(find, "(%d, %d, %d, %d, %d, %d", &a, &b, &c, &d, &pa, &pb);
    sprintf(ipaddr, "%d.%d.%d.%d", a, b, c, d);
    *port = pa * 256 + pb;

}

void ls(void) {
    char ipAddr[32];
    int port;
    char *ls = "NLST\r\n";
    char buffer[N];
    int tolen;
    struct sockaddr_in to;
    struct hostent *host;

    pasv(ipAddr, &port);

    dat_soc = socket(AF_INET, SOCK_STREAM, 0);
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = htons(INADDR_ANY);
    host = gethostbyname(ipAddr);
    memcpy(&(to.sin_addr), host->h_addr, host->h_length);
    tolen = sizeof(to);
    to.sin_port = htons(port);


    if (connect(dat_soc, (struct sockaddr *) &to, tolen) < 0) {
        perror("Error connecting socket");
        exit(1);
    }

    send_rq(sd, ls);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    bzero(buffer, sizeof(buffer));

    if (recv(dat_soc, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    bzero(buffer, sizeof(buffer));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error receiving");
        exit(5);
    } else printf("%s \n", buffer);

    close(dat_soc);
}





