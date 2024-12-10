#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <conio.h>

#define MAP_ROWS 12
#define MAP_COLS 100
#define VIEW_ROWS 12
#define VIEW_COLS 100

char bground[MAP_ROWS][MAP_COLS] = {
    "@@@@@             @@@@@@@@            @@@@@@@@@         @@@@@                 @@@@@@@                @@@  ",
    "@@@@@@              @@@@@               @@@@@         @@@@@@@@@             @@@@@@                  @@@@ ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                #                       ",
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
        printf("\n"); 
    }
}

int manX = 8, manY = 50;
int is_jumping = 0;  
int jump_timer = 0;   

void move_man(char input) {
    static int originalX = 0; // Karakterin orijinal X pozisyonunu saklar

    if (is_jumping) {
        if (jump_timer > 0) {
            jump_timer--;  
        } else {
           
            bground[manX][manY] = ' ';  // Eski konumu temizle
            manX = originalX;           // Orijinal X pozisyonuna dön
            bground[manX][manY] = 'P';  // Karakteri yeni konuma koy
            is_jumping = 0;             // Atlama durumunu sıfırla
        }
        return;  
    }

    if (input == 'w') {
     originalX = manX;           // Orijinal X pozisyonunu kaydet
      
      int nextY = (manY + 5) % MAP_COLS;
        bground[manX][manY] = ' ';  
        manY = nextY;              
        bground[manX][manY] = 'P'; 

        if (manX > 1) {             // Harita sınırını kontrol et
            bground[manX][manY] = ' ';  
            manX -= 2;  
            bground[manX][manY] = 'P';  
            is_jumping = 1;         // Atlama durumunu başlat
            jump_timer = 4;         // Yukarıda kalma süresi 
        }
    }
}


int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int start_row = 0;
    int start_col = 0;

    bground[manX][manY] = 'P'; // Karakteri başlangıç konumuna koy

    while (1) {
        if (_kbhit()) {  // Kullanıcı girişi varsa
            char input = _getch();
            move_man(input); // Kullanıcı girdisine göre hareket
        } else {
            move_man('\0'); // Atlama durumunu kontrol et
        }

        // Karakterin sağa hareketi
        int nextY = (manY + 1) % MAP_COLS;
        if (!is_jumping && bground[manX][nextY] == ' ') {
            bground[manX][manY] = ' ';  
            manY = nextY;              
            bground[manX][manY] = 'P'; 
        }

        // Ekranı güncelle
        drawScreen(bground, start_row, start_col); 

        // Haritayı sağa kaydır
        start_col = (start_col + 1) % MAP_COLS;

        Sleep(100); // Bekleme süresi (hızı kontrol eder)
    }

    return 0;
}





