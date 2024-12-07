#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <conio.h>

#define ROWS 11
#define COLS 500


void load_map(const char *filename, char map[ROWS][COLS]) {
    FILE *file = fopen(filename, "r"); // Dosyayı okuma modunda aç
    if (!file) {
        perror("Harita dosyasi acilamadi");
        exit(1);
    }

    // Haritayı satır satır okuyup diziye aktar
    for (int i = 0; i < ROWS; i++) {
        if (fgets(map[i], COLS + 2, file)) {
            map[i][strcspn(map[i], "\n")] = '\0'; // Satır sonundaki '\n' karakterini kaldır
        } 
    }

    fclose(file); 
}

void draw_map(char map[ROWS][COLS]) {
    system("cls"); // Terminali temizle
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", map[i]); // \n karakteri eklenmezse fazladan boşluk olmaz
    }
}





int main() {
    char map[ROWS][COLS];
    
    load_map("C:\\Users\\ahmet\\Documents\\GitHub\\C-Parkour-Game\\MAP\\map.txt", map);

    draw_map(map);

    return 0;
}