#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 40

// Haritayı dosyadan yükleme fonksiyonu
void load_map(const char *filename, char map[ROWS][COLS]) {
    FILE *file = fopen(filename, "r"); // Dosyayı okuma modunda aç
    if (!file) {
        perror("Harita dosyasi acilamadi");
        exit(1);
    }

    // Haritayı satır satır okuyup diziye aktar
    for (int i = 0; i < ROWS; i++) {
        fgets(map[i], COLS + 2, file); 
        map[i][COLS] = '\0'; // Yeni satır karakterini kaldır
    }

    fclose(file); // Dosyayı kapat
}

// Haritayı ekranda çizme fonksiyonu
void draw_map(char map[ROWS][COLS]) {
    system("cls"); 
    for (int i = 0; i < ROWS; i++) {
        printf("%s", map[i]); 
    }
}

int main() {
    char map[ROWS][COLS];
    
    load_map("./map.txt", map);

    draw_map(map);

    return 0;
}