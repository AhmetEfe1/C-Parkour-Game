#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAP_ROWS 11
#define MAP_COLS 100
#define VIEW_ROWS 11
#define VIEW_COLS 100
#define CHAR_HEIGHT 3
#define CHAR_WIDTH 5
int score = 0; 
int score1 = 0;
int manX = 6, manY = 40;  // Karakterin pozisyonu
int is_jumping = 0;       // Karakter yukarıda mı?
int jump_timer = 0;       // Yukarıda kalma zamanlayici
int obstacles[MAP_COLS] = {0}; // Engel konumlarını saklayan dizi

// Harita tanımı
char bground[MAP_ROWS][MAP_COLS] = {
    "@@@@@             @@@@@@@@            @@@@@@@@@         @@@@@                 @@@@@@@                @@@",
    "@@@@@@              @@@@@               @@@@@         @@@@@@@@@             @@@@@@                  @@@@",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "                                                                                                        ",
    "           #            #     #                           #                  #        #                 ",
    "________________________________________________________________________________________________________",
    "/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / ",
};
// Baslangic ekrani
char start_screen[MAP_ROWS][MAP_COLS] = {
"                         @@@@@@@           @@@@             @@@@@         @@@@@             @@@@@     ",
"         _^_            @@@@@         @@@@@@          @@@@@          @@@@@                @@@@@       ",
"       _/   \\_                                                                                        ",
"     _/_______\\_                                                                                      ",
"    |---SCHOOL--|                           Okuldan kacmak icin W tusu ile engelleri gec!             ",
"    |  #     #  |                     Herhangi bir tusa basarak oyunu basalt, Q oyunu durdurur.       ",
"    |           |                                                                                     ",
"    |  #     #  |                                                                                     ",
"    |     _     |             ##           #       ##                              ##                 ",
"____|____|_|____|____________###___________##______###___________##_______________###_________________",
"//////////////////////////////////////////////////////////////////////////////////////////////////////",

};

// Karakter modeli
char man[CHAR_HEIGHT][CHAR_WIDTH] = {
    " _0_ ",
    "\\ l \\",
    " L L "
};

char man_jump[CHAR_HEIGHT][CHAR_WIDTH] = {
    "/_0_/",
    " _l_ ",
    "  L L",
};


// Haritayı ekrana çizme
void drawScreen(int start_col) {
    system("cls"); // Ekranı temizle

    // Skor tablosunu çiz
    printf("Skor: %d\n", score);

    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < VIEW_COLS; col++) {

            // Eğer bu hücre karakterin bir parçasıysa
            if (row >= manX && row < manX + CHAR_HEIGHT &&
                col >= manY && col < manY + CHAR_WIDTH) {
                printf("%c", man[row - manX][col - manY]);
            } else {
                    // Karakterin olmadığı yerlere haritayı çiz
                    printf("%c", bground[row][(start_col + col) % MAP_COLS]);
            }
        }           printf("\n"); 
    }
}

// Zıplama fonksiyonu
void jump() {
    if (!is_jumping) {
        manX = (manX - 3 >= 0) ? manX - 3 : 0; // Harita sınır kontrolü
    
        man[0][0] = '/'; man[0][1] = '_'; man[0][2] = '0'; man[0][3] = '_'; man[0][4] = '/';
        man[1][0] = ' '; man[1][1] = '_'; man[1][2] = 'l'; man[1][3] = '_'; man[1][4] = ' ';
        man[2][0] = ' '; man[2][1] = ' '; man[2][2] = 'L'; man[2][3] = ' '; man[2][4] = 'L';

        is_jumping = 1;
        jump_timer = 6; // Yukarıda kalma süresi
    }
}

// Karakter haraketi
void move_man() {
    if (is_jumping) {
        if (jump_timer > 0) {
            jump_timer--;
        } else {
            manX = (manX + 3 < MAP_ROWS) ? manX + 3 : MAP_ROWS - CHAR_HEIGHT; // Aşağı in
            // Karakteri tekrar normal hale getir
            man[0][0] = ' '; man[0][1] = '_'; man[0][2] = '0'; man[0][3] = '_'; man[0][4] = ' ';
            man[1][0] = '\\'; man[1][1] = ' '; man[1][2] = 'l'; man[1][3] = ' '; man[1][4] = '\\';
            man[2][0] = ' '; man[2][1] = 'L'; man[2][2] = ' '; man[2][3] = 'L'; man[2][4] = ' ';

            is_jumping = 0;
        }
    }
}

// Çarpışma kontrolü
int checkCollision(int start_col) {
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            int char_row = manX + i;
            int char_col = (manY + j + start_col) % MAP_COLS; // Karakterin global haritadaki sütunu

            // Harita sınırları içinde mi ve engelle çakışıyor mu?
            if (char_row >= 0 && char_row < MAP_ROWS && bground[char_row][char_col] == '#') {
            
            return 1; // Çarpışma var
            }
        }
    }
    return 0; // Çarpışma yok
}

// Skor tablosu
void updateScore(int start_col) {
    for (int col = 0; col < CHAR_WIDTH; col++) {
        int char_col = (start_col + manY + col) % MAP_COLS; // Karakterin sütunu

        // Eğer karakter engelin üstünden geçtiyse
        if (is_jumping && 
            bground[MAP_ROWS - 3][char_col] == '#') { // Engel tam zemin seviyesinde
            score1++; // Skoru artır
            score = score1 /5;
        }
    }
}

// Oyun döngüsü
void game_loop() {
    int start_col = 0;
    while (1) {
        // Kullanıcı girdisi kontrolü
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w' || input == ' ') jump(); // Zıplama
            if (input == 'q') break;                 // Çıkış
        }

        // Çarpışma kontrolü
        if (checkCollision(start_col)) {
            system("cls"); // Ekranı temizle
            printf("Oyun Bitti! Karakter bir engele carpti.\n");
            printf("Final Skorunuz: %d\n", score);
            break; // Oyun döngüsünden çık
        }

          // Skoru güncelle
        updateScore(start_col);

        // Haritayı ve engelleri güncelle
        move_man();
        start_col = (start_col + 1) % MAP_COLS;

        // Haritayı çiz
        drawScreen(start_col);
        Sleep(40); // Hız ayarı
        }
}
 
// Ana fonksiyon
int main() {
    
    // İmleci gizle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    system("cls");
    printf("                      @@@@@@@           @@@@             @@@@@         @@@@@             @@@@@        \n");
    printf("          _^_            @@@@@         @@@@@@          @@@@@          @@@@@                @@@@@      \n");
    printf("        _/   \\_                                                                                       \n");
    printf("      _/_______\\_                                                                                     \n");
    printf("     |---SCHOOL--|                       Okuldan kacmak icin W tusu ile engelleri gec!                \n");
    printf("     |  #     #  |                  Herhangi bir tusa basarak oyunu baslat, Q oyunu durdurur.         \n");
    printf("     |           |                                                                                    \n");
    printf("     |  #     #  |                                                                                    \n");
    printf("     |     _     |             ##           #       ##                              ##                \n");
    printf("_____|____|_|____|____________###___________##______###___________##_______________###________________\n");
    printf("//////////////////////////////////////////////////////////////////////////////////////////////////////\n");
    
    _getch(); // Oyuna başlamak için herhangi bir tuşa bas
    game_loop(); // Oyun döngüsünü başlat
    return 0;
}
