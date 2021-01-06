//
// Created by stefa on 5. 1. 2021.
//

#include "klient.h"


static char *prikazy[NB_CMDS] = {
        "open", "cd", "mkd", "rmd", "quit", "dir", "get", "put", "pwd", "del", "help"
};
int sd = 0;
int connected = 0;


int main(int argc, char *argv[]) {
    char buffer[N], *param;
    int j = 0;

    do {
        memset(buffer, '\0', N * sizeof(char));
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
        switch (j) {
            case (OPEN):
                if (connected == 1) printf("You are already connected\n");
                else pripojit(argv[1], argv[2], argv[3]);
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
            case (HELP):
                help();
                break;
        }


    } while (1);
    return 0;
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
    char *pwd = "XPWD \n";

    if (send(sd, pwd, strlen(pwd) + 1, 0) < 0) {
        perror("Error sending");
        exit(2);
    }
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
    strcat(chd, "CD ");
    strcat(chd, repo);
    strcat(chd, "\n");


    if (send(sd, chd, strlen(chd) + 1, 0) < 0) {
        perror("Error sending");
        exit(2);
    }

    memset(bufffer, '\0', N * sizeof(char));
    if (recv(sd, bufffer, sizeof(bufffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("cd %s \n", bufffer);
}

void quit(void) {
    char quit[N];
    char buffer[N];
    memset(quit, '\0', N * sizeof(char));
    strcat(quit, "QUIT \n");

    if (connected == 1)
        if (send(sd, quit, strlen(quit) + 1, 0) < 0) {
            perror("Error sending");
            exit(2);
        }
    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

    close(sd);
    sd = 0;
    printf("Goodbye \n");

}

void dir(void) {
    char *dir = "DIR \n";
    char buffer[N];
    if (send(sd, dir, strlen(dir) + 1, 0) < 0) {
        perror("Error sending");
        exit(2);
    }
    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("'%s' \n", buffer);

}

void del(char *file) {
    char del[N];
    char buffer[N];

    memset(del, '\0', N * sizeof(char));
    strcat(del, "DELETE ");
    strcat(del, file);
    strcat(del, "\n");
    if (send(sd, del, strlen(del) + 1, 0) < 0) {
        perror("Error sending");
        exit(2);
    }
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
    strcat(mkd, "MKDIR ");
    strcat(mkd, directory);
    strcat(mkd, "\n");

    if (send(sd, mkd, strlen(mkd) + 1, 0) < 0) {
        perror("Error sending");
        exit(2);
    }

    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

}

void pripojit(char *host_serv, char *uname, char *password) {
    struct sockaddr_in to;
    struct hostent *host;
    char *server_port = "21";
    int tolen, len;
    char buffer[N];

    char user[N];
    char pass[N];

    memset(user, '\0', N * sizeof(char));
    memset(pass, '\0', N * sizeof(char));


    to.sin_family = AF_INET;
    to.sin_port = htons(SERVER_PORT);
    host = gethostbyname(host_serv);
    memcpy(&(to.sin_addr), host->h_addr, sizeof(to.sin_addr));
    tolen = sizeof(to);
    sd = socket(AF_INET, SOCK_STREAM, 0);


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
    strcat(user, "user ");
    strcat(user, uname);
    strcat(user, "\n");
//
//    strcat(pass, "PASS ");
//    strcat(pass, password);
//    strcat(pass, "\n");


    if (send(sd, user, 1024, 0) < 0) {
        perror("Error sending");
        exit(2);
    }
    memset(buffer, '\0', N * sizeof(char));

    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recievieng");
        exit(5);
    } else printf("%s\n", buffer);
//
//    if (send(sd, pass, 1024, 0) < 0) {
//        perror("Error sending");
//        exit(2);
//    }
//    memset(buffer, '\0', N * sizeof(char));
//
//    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
//        perror("Error recievieng");
//        exit(5);
//    } else printf("%s\n", buffer);
    connected = 1;
}

void rmd(char *directory) {
    char rmd[N];
    char buffer[N];

    memset(rmd, '\0', N * sizeof(char));
    strcat(rmd, "RMDIR ");
    strcat(rmd, directory);
    strcat(rmd, "\n");

    if (send(sd, rmd, strlen(rmd) + 1, 0) < 0) {
        perror("Error sending");
        exit(2);
    }
    memset(buffer, '\0', N * sizeof(char));
    if (recv(sd, buffer, sizeof(buffer), 0) < 0) {
        perror("Error recieving");
        exit(5);
    } else printf("%s \n", buffer);

}




