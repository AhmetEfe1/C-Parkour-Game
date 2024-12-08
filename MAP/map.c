#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // Sleep fonksiyonu için
#include <conio.h>

#define MAP_ROWS 12
#define MAP_COLS 100
#define VIEW_ROWS 12
#define VIEW_COLS 100

// Harita dizisini doğru şekilde tanımla
char bground[MAP_ROWS][MAP_COLS] = {
    "@@@@@             @@@@@@@@            @@@@@@@@@         @@@@@                 @@@@@@@                @@@",
    "@@@@@@              @@@@@               @@@@@         @@@@@@@@@             @@@@@@                  @@@@",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "________________________________________________________________________________________________________",
    "/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / ",
};

// Haritayı çizmek için fonksiyon
void drawScreen(char screenarray[MAP_ROWS][MAP_COLS], int start_row, int start_col) {
    system("cls");
    
    // Ekranın sadece belli bir kısmını göster
    for (int i = start_row; i < start_row + VIEW_ROWS; i++) {
        for (int j = start_col; j < start_col + VIEW_COLS; j++) {
            printf("%c", screenarray[i][j % MAP_COLS]);  // Harita sütunlarını döngüsel yap
        }
        printf("\n");  // Satırdan sonra bir alt satıra geç
    }
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    
    // Cursoru gizle
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int start_row = 0;  
    int start_col = 0;  

    while (1) {
        drawScreen(bground, start_row, start_col); 

        start_col++;  // Haritayı sağa kaydır
        if (start_col >= VIEW_COLS) {
            start_col = 0;  // Sütun limiti aşıldığında sıfırla
        }

        Sleep(50); 
    }

    return 0;
}
