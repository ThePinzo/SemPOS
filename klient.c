//
// Created by stefa on 5. 1. 2021.
//

#include "klient.h"


static char *prikazy[NB_CMDS] = {
        "open", "cd", "mkd", "rmd", "quit", "dir", "get", "put", "pwd", "del", "help"
};
int sd = 0;
int data_sock = 0;
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
                        }
                        pripojit(argv[1], uname, pass);
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
                    cd(param);
                }
                break;

            case (QUIT):
                quit();
                return 0;
                break;
            case (MKD):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    mkd(param);
                }
                break;
            case (RMD):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    rmd(param);
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
                    del(param);
                }
                break;
            case (GET):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    get(param);
                }
                break;
            case (PUT):
                if (connected == 0) {
                    printf("You are not connected\n");
                } else {
                    put(param);
                }
                break;
            case (HELP):
                help();
                break;
            default:
                help();
                break;
        }


    } while (1);
}

void help(void) {
    printf("Prikazy pre pracu s klientom: \n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("QUIT    Zatvori ftp klienta\n");
    printf("OPEN    Pripoji klienta ku serveru\n");
    printf("CD      Zmeni sa pracovny adresar\n");
    printf("PWD     Zobrazi cesta ku pracovnemu adresaru\n");
    printf("GET     Stiahne subor zo serveru\n");
    printf("PUT     Nahra subor na server\n");
    printf("DEL     Vymaze subor\n");
    printf("MKD     Vytvori adresar\n");
    printf("RMD     Vymaze adresar\n");
    printf("DIR     Zobrazi sa obsah pracovneho adresara\n");
    printf("HELP    Zobrazi zoznam pouzitelnych prikazov\n");
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
    char *pasv = "PORT **,208,138\r\n";
    char *dir = "LIST\r\n";
    char buffer[N];

    send_rq(sd, pasv);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

    send_rq(sd, dir);

    bzero(buffer, sizeof(buffer));

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
    char buffer[N];
    char get[N];

    strcat(get, "RETR ");
    strcat(get, file);
    strcat(get, "\r\n");


    send_rq(sd, get);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);
}

void put(char *file) {
    char buffer[N];
    char put[N];

    strcat(put, "STOR ");
    strcat(put, file);
    strcat(put, "\r\n");

    send_rq(sd, put);

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);
}




