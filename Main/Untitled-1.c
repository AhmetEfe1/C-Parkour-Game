#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // getch() ve kbhit() için
#include <windows.h> // Sleep() için

#define WIDTH 40
#define HEIGHT 10

// Oyuncunun başlangıç pozisyonu
#define PLAYER_X 5
#define PLAYER_Y 8

char screen[HEIGHT][WIDTH]; // Oyun ekranı
int player_y = PLAYER_Y;    // Oyuncunun mevcut y pozisyonu
int obstacle_x = WIDTH - 1; // Engel başlangıç pozisyonu

// Oyun ekranını sıfırla
void clear_screen() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }
}

// Ekranı güncelle
void update_screen() {
    system("cls"); // Windows için terminali temizle
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

// Oyuncuyu çiz
void draw_player() {
    screen[player_y][PLAYER_X] = '@';
}

// Engeli çiz
void draw_obstacle() {
    if (obstacle_x >= 0 && obstacle_x < WIDTH) {
        screen[PLAYER_Y][obstacle_x] = '#';
    }
}

// Çarpışma kontrolü
int check_collision() {
    return (obstacle_x == PLAYER_X && player_y == PLAYER_Y);
}

// Oyunu çalıştır
void game_loop() {
    int jump = 0;          // Oyuncu zıpladı mı?
    int score = 0;         // Skor
    obstacle_x = WIDTH - 1; // Engel başlangıç pozisyonu

    while (1) {
        clear_screen(); // Ekranı sıfırla

        // Tuş kontrolü
        if (_kbhit()) { // Bir tuşa basılıp basılmadığını kontrol et
            char key = _getch();
            if (key == ' ') { // Boşluk tuşu ile zıpla
                jump = 1;
            }
        }

        // Oyuncunun pozisyonunu güncelle
        if (jump) {
            player_y = PLAYER_Y - 1; // Zıplama yüksekliği
        } else {
            player_y = PLAYER_Y; // Yere in
        }
        jump = 0; // Zıplama durumu sıfırla

        // Engelin pozisyonunu güncelle
        obstacle_x--;
        if (obstacle_x < 0) {
            obstacle_x = WIDTH - 1; // Engel yeniden başlasın
            score++;                // Skoru artır
        }

        // Çarpışma kontrolü
        if (check_collision()) {
            printf("ÇARPIŞMA! Oyun bitti. Skorunuz: %d\n", score);
            break;
        }

        // Oyuncu ve engeli çiz
        draw_player();
        draw_obstacle();

        // Ekranı güncelle
        update_screen();

        // Kısa bir süre bekle
        Sleep(100); // 100 milisaniye bekle (Windows için)
    }
}

int main() {
    printf("Terminal Oyununa Hoş Geldiniz!\n");
    printf("Oyuncuyu '@' sembolü temsil eder. Engeller '#' olarak görünür.\n");
    printf("Boşluk tuşu ile zıplayın. Başlamak için bir tuşa basın.\n");
    _getch(); // Oyuna başlamak için herhangi bir tuşa bas
    game_loop(); // Oyun döngüsünü başlat
    return 0;
}
