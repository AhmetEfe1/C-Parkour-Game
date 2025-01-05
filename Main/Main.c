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

// Global değişkenler
int manX = 6, manY = 40;  // Karakterin sol üst köşe pozisyonu
int is_jumping = 0;       // Karakter yukarıda mı?
int jump_timer = 0;       // Yukarıda kalma süresi
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
    "                                                                                                        ",
    "________________________________________________________________________________________________________",
    "/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / ",
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

// Engel oluşturma
void spawnObstacle() {
    int obstaclePos = MAP_COLS - 1;
    bground[8][obstaclePos] = '#';
    obstacles[obstaclePos] = 1;
}

// Engelleri güncelleme
void updateObstacles() {
    for (int col = MAP_COLS - 1; col > 0; col--) {
        if (obstacles[col]) {
            bground[8][col] = ' ';  // Eski pozisyonu temizle
            bground[8][col - 1] = '#';  // Yeni pozisyona engel ekle
            obstacles[col] = 0;  // Eski pozisyonu temizle
            obstacles[col - 1] = 1;  // Yeni pozisyonda engel var
        }
    }
}

// Haritayı ekrana çizme
void drawScreen(int start_col) {
    system("cls"); // Ekranı temizle

    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < VIEW_COLS; col++) {
            if (row >= manX && row < manX + CHAR_HEIGHT &&
                col >= manY && col < manY + CHAR_WIDTH) {
                // Karakterin bulunduğu alanı çiz
                printf("%c", man[row - manX][col - manY]);
            } else {
                // Diğer alanları çiz
                printf("%c", bground[row][(start_col + col) % MAP_COLS]);
            }
        }
        printf("\n");
    }
}

// Zıplama fonksiyonu
void jump() {
    if (!is_jumping) {
        manX = (manX - 3 >= 0) ? manX - 3 : 0; // Harita sınır kontrolü
        memcpy(man, man_jump, sizeof(man));
        is_jumping = 1;
        jump_timer = 5; // Yukarıda kalma süresi
    }
}

// Karakteri hareket ettirme
void move_man() {
    if (is_jumping) {
        if (jump_timer > 0) {
            jump_timer--;
        } else {
            manX = (manX + 3 < MAP_ROWS) ? manX + 3 : MAP_ROWS - CHAR_HEIGHT; // Aşağı in
            memcpy(man, (char[CHAR_HEIGHT][CHAR_WIDTH]) {
                " _O_ ",
                "\\ l \\",
                " L L "
            }, sizeof(man));
            is_jumping = 0;
        }
    }
}

// Çarpışma kontrolü
int checkCollision() {
    // Karakterin en sağdaki ve en solundaki pozisyonlarını kontrol et
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            int charRow = manX + i;
            int charCol = manY + j;
            
            // Eğer karakterin pozisyonu harita sınırlarında ve engelle çakışıyorsa
            if (charRow < MAP_ROWS && charCol < MAP_COLS && bground[charRow][charCol] == '#') {
                exit;
            }
        }
    }
    return 0;  // Çarpışma yok
}

// Oyun döngüsü
void game_loop() {
    srand(time(NULL)); // Rastgelelik için
    clock_t last_spawn_time = clock();
    int spawn_delay = (rand() % 3 + 3) * CLOCKS_PER_SEC; // 3 ila 5 saniye
    int start_col = 0;

    while (1) {
        // Kullanıcı girdisi kontrolü
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w') jump();
            if (input == 'q') break;
        }

        // Çarpışma kontrolü
        if (checkCollision()) {
            system("cls"); // Ekranı temizle
            printf("Oyun Bitti! Çarpışma oldu.\n");
            break;
        }

        // Haritayı ve engelleri güncelle
        move_man();
        start_col = (start_col + 1) % MAP_COLS;

        // Engel oluşturma zamanı
        clock_t current_time = clock();
        if (current_time - last_spawn_time >= spawn_delay) {
            spawnObstacle();
            last_spawn_time = current_time;
            spawn_delay = (rand() % 3 + 3) * CLOCKS_PER_SEC;
        }

        updateObstacles();

        // Haritayı çiz
        drawScreen(start_col);

        Sleep(50); // Hız ayarı
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

    printf("Terminal Oyununa Hoş Geldiniz!\n");
    printf("Oyuncuyu '@' sembolü temsil eder. Engeller '#' olarak görünür.\n");
    printf("'w' tuşu ile zıplayın. 'q' ile çıkış yapın. Başlamak için bir tuşa basın.\n");
    _getch(); // Oyuna başlamak için herhangi bir tuşa bas
    game_loop(); // Oyun döngüsünü başlat
    return 0;
}
