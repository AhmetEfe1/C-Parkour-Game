#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ROWS 20
#define COLS 240

#define SSROWS 20
#define SSCOLS 60

char bground[SSROWS][SSCOLS] = {
 "############################################################",
 "#                                                          #", 
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "#                                                          #",
 "############################################################",


};


void drawmap (char screenarray [SSROWS][SSCOLS]) {
system("clear");
 for (int i = 0; i < SSROWS; i++) {
        printf("%s\n", screenarray[i]);

 }
}



int main () {
 
 
 drawmap(bground);
    sleep(2);




}






