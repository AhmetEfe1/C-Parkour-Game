#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define MAP_ROWS 12
#define MAP_COLS 100
#define VIEW_ROWS 12
#define VIEW_COLS 100
#define CHAR_HEIGHT 3
#define CHAR_WIDTH 5

// Global değişkenler
int manX = 6, manY = 40;  // Karakterin sol üst köşe pozisyonu
int is_jumping = 0;       // Karakter yukarıda mı?
int jump_timer = 0;       // Yukarıda kalma süresi


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
    "                                                                         #                              ",
    "________________________________________________________________________________________________________",
    "/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / ",
};

// Karakter modeli
char man[CHAR_HEIGHT][CHAR_WIDTH] = {
    " _O_ ",
    "\\ l \\",
    " L L "
};

char man_jump [CHAR_HEIGHT][CHAR_WIDTH] = {

   "/_O_/",
   " _l_ ",
   "  L L",

};







// Haritayı ekrana çizme
void drawScreen(char screenarray[MAP_ROWS][MAP_COLS], int start_row, int start_col) {
    system("cls");
    for (int i = start_row; i < start_row + VIEW_ROWS; i++) {
        for (int j = start_col; j < start_col + VIEW_COLS; j++) {
            printf("%c", screenarray[i % MAP_ROWS][j % MAP_COLS]);
        }
        printf("\n");
    }
}

// Haritada karakteri temizleme
void clear_man() {
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            if (manX + i < MAP_ROWS && manY + j < MAP_COLS) {
                bground[manX + i][manY + j] = ' ';
            }
        }
    }
}

// Haritaya karakteri yerleştirme
void place_man() {
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            if (manX + i < MAP_ROWS && manY + j < MAP_COLS) {
                bground[manX + i][manY + j] = man[i][j];
            }
        }
    }
}

void update_model(char target[CHAR_HEIGHT][CHAR_WIDTH], char source[CHAR_HEIGHT][CHAR_WIDTH]) {
    memcpy(target, source, sizeof(char) * CHAR_HEIGHT * CHAR_WIDTH); 
}

// Karakterin hareket fonksiyonu
void move_man() {
    if (is_jumping) {
        // Zıplama sırasında
        if (jump_timer > 0) {
            jump_timer--; // Yukarıda kalma süresini azalt
        } else {
            clear_man();  // Eski konumu temizle
            manX += 2;    // Karakter aşağı iner
            update_model(man, (char[CHAR_HEIGHT][CHAR_WIDTH]){
                " _O_ ",
                "\\ l \\",
                " L L "
            }); // Modeli eski haline döndür
            place_man();  // Yeni konuma karakteri koy
            is_jumping = 0; // Zıplama durumu sıfırla
        }
    } else {
        // Karakterin sağındaki alanın kontrolü
        int nextY = manY + CHAR_WIDTH; // Karakterin hemen sağındaki sütun
        int can_move = 1;             // Hareket durumu

        for (int i = 0; i < CHAR_HEIGHT; i++) {
            if (manX + i < MAP_ROWS && nextY < MAP_COLS) {
                if (bground[manX + i][nextY] != ' ') { // Sağındaki alan boş değilse
                    can_move = 0;
                    break;
                }
            }
        }

        if (can_move) { // Eğer hareket edilebilirse
            clear_man(); // Eski konumu temizle
            manY = (manY + 1) % MAP_COLS; // Yeni Y pozisyonu
            place_man(); // Yeni konuma karakteri koy
        }
    }
}






// `w` tuşuyla karakterin yukarı çıkmasını başlat
void jump() {
    if (!is_jumping) {
        clear_man(); // Eski konumu temizle
        manX -= 2;         // Yukarı hareket
        update_model (man, man_jump);
        place_man(); // Yeni konuma karakteri koy
        is_jumping = 1;    // Atlama durumunu başlat
        jump_timer = 7;    // Yukarıda kalma süresini ayarla
        int nextY = (manY + 8) % MAP_COLS;
        clear_man(); // Eski konumu temizle
        manY = nextY;      // Yeni Y pozisyonu
        
        place_man(); // Yeni konuma karakteri koy
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


 
    place_man(); // Karakter başlangıç konumunu haritaya yerleştir


    

        while (1) {
        // Kullanıcı girdisi kontrolü
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w') {
                jump(); // Yukarı çıkış
                }if (input == 'q') break;
        }

        // Karakteri hareket ettir
        move_man();

        // Haritayı sağa kaydır
        start_col = (start_col + 1) % MAP_COLS;

        // Haritayı ve karakteri çiz
        drawScreen(bground, start_row, start_col);

        Sleep(100); // Hız ayarı
    }

    return 0;
}
