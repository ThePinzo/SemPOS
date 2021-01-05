//
// Created by stefa on 5. 1. 2021.
//

#include "client.h"

static char *prikazy[NB_CMDS] = {
        "open", "cd", "mkd", "rmd", "quit", "dir", "get", "put", "pwd", "del", "help"
};

int main(int argc, char *argv[]) {

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
