#include "viewUtils.h"

void clearScreen() {
    printf("\033[2J\033[H");
}

void printBoldGreen(char *str){
    printf("\033[1;32m%s\033[0m",str);
}

void printError (char *errorMessage){
    puts("");
    printf("\033[41m%s\033[0m",errorMessage);
    puts("");
    puts("");
}

void printSuccess (char *successMessage){  
    puts("");
    printf("\033[42m%s\033[0m",successMessage);
    puts("");
    puts("");
}

void showMyTitle() {
    printf("\033[1;32m");
    puts("");
    puts("                                   ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠉⠀⠀⠀⠀⠈⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡁⣀⢰⡀⢠⣀⣾⡇⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠾⠿⢿⡟⠉⣉⣿⣾⠂⠀⠹⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣧⠀⠀⠈⢿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠹⣿⣿⣿⣿");
    puts("                                   ⣿⣿⡿⠟⠋⠉⠉⠉⠙⠻⣿⣿⣿⣿⡿⠿⠿⠿⣿⣿⣿⠃⠀⠀⠀⠀⠘⣿⣿⣿");
    puts("                                   ⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠯⡁⠀⠀⠀⠀⠈⠙⠳⢄⠀⠀⠀⠀⠀⠘⣿⣿");
    puts("                                   ⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⢸⣿");
    puts("                                   ⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡴⢶⣤⣀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⢸⣿");
    puts("                                   ⣿⠀⠀⠀⠀⠀⠀⠀⠀⢰⡟⠀⠀⠈⢙⣿⠷⠶⠿⠛⠉⠀⠠⠤⣤⣤⣤⣤⣼⣿");
    puts("                                   ⣿⠀⠀⠀⠀⠀⠀⠀⢀⣿⣁⣤⣴⣾⣯⣅⣀⣀⣀⣤⣤⣶⣾⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⠀⠀⠀⠀⠀⠀⣠⡾⠋⠉⠁⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⠀⠀⠀⠀⣀⣴⠏⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
    puts("                                   ⣿⣤⣤⣴⣾⣯⣤⣤⣤⣤⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");
    puts("                                      By Luca Martorelli [m:0281213]");
    puts("");
    printf("\033[0m");
}


void printConqueredTerritory() {
    puts("\n");
    printf("\033[44m%s\033[0m","\t\t\t\t        CONGRATULAZIONI!        ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢻⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣆⠈⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠁⣰⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣦⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⣴⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣷⡀⠀⠀⠀⠈⠻⢿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⢀⣾⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⣿⣆⠀⠀⢶⣄⠈⠛⢿⣿⣿⡿⠋⠁⣠⡶⠀⠀⣰⣿⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠙⢷⣄⠀⠙⠿⣄⣠⡾⠋⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠙⢷⣄⠀⠈⠻⣦⣀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⠟⢿⣿⣿⣿⣿⠿⣦⡀⠀⠙⢷⣄⠀⠈⠻⣿⣿⣿⣿⡿⠻⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣧⡀⠈⢻⣿⠟⠁⠀⣨⣿⣦⡀⠀⠙⢷⣄⠀⠈⠻⣿⡟⠁⢀⣼⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⣦⡀⠁⠀⣠⡾⠋⠀⢈⣿⣦⡀⠀⠙⢷⣄⠀⠈⢀⣴⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⣿⡿⠀⠀⠉⠀⢀⣴⣿⣿⣿⣿⣦⡀⠀⠉⠀⠀⢿⣿⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⠏⠀⣠⣶⣦⡀⠈⠻⢿⣿⣿⡿⠟⠁⢀⣴⣶⣄⠀⠹⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⡿⠋⠁⣴⣿⣿⣿⣿⣿⣦⡀⢀⣽⣯⡀⢀⣴⣿⣿⣿⣿⣿⣦⠈⠙⢿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣇⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⣸⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ ");puts("");
    printf("\033[44m%s\033[0m","\t\t\t\t     TERRITORIO CONQUISTATO     ");puts("");
    puts("\n");
}

void printAttackResults(char *terr1, char *terr2, int carriPersiAtt, int carrPersiDif){
    printf("\033[1;31m");
    puts("\n");
    printf("\t\t $$\\    $$\\  $$$$$$\\      \033[0m\033[41m'%s' HA ATTACCATO '%s'\033[0m\033[1;31m",terr1,terr2);puts("");   
    printf("\t\t $$ |   $$ |$$  __$$\\                                    ");puts("");
    printf("\t\t $$ |   $$ |$$ /  \\__|     RISULTATO ATTACCO:          ");puts("");
    printf("\t\t \\$$\\  $$  |\\$$$$$$\\                                  ");puts("");
    if(carriPersiAtt == 1){
        printf("\t\t  \\$$\\$$  /  \\____$$\\      ⊙ %d carro armato perso in %s    ",carriPersiAtt,terr1);puts("");
    }else{
        printf("\t\t  \\$$\\$$  /  \\____$$\\      ⊙ %d carri armati persi in %s    ",carriPersiAtt,terr1);puts("");
    }
    printf("\t\t   \\$$$  /  $$\\   $$ |                                  ");puts("");
    if(carrPersiDif == 1){
        printf("\t\t    \\$  /   \\$$$$$$  |     ⊙ %d carro armato perso in %s      ",carrPersiDif,terr2);puts("");
    }else{
        printf("\t\t    \\$  /   \\$$$$$$  |     ⊙ %d carri armati persi in %s      ",carrPersiDif,terr2);puts("");
    }
    printf("\t\t     \\_/     \\______/                                   ");puts("");
    puts("");
    printf("\033[0m");
}
