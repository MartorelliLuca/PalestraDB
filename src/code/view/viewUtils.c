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
    printf("\033[47m\033[30m%s\033[0m", successMessage);
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
    puts("                                   By Luca Martorelli [m:0281213]");
    puts("");
    printf("\033[47m\033[30m\033[0m");
}