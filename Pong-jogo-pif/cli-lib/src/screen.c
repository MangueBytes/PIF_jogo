/**
 * screen.c
 * Created on Aug 23rd, 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include "screen.h"

// Desenha as bordas do jogo
void screenDrawBorders() {
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenClear();
    screenBoxEnable();

    // Canto superior esquerdo
    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);

    // Linha superior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }

    // Canto superior direito
    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    // Laterais
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    // Canto inferior esquerdo
    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);

    // Linha inferior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }

    // Canto inferior direito
    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);

    screenBoxDisable();
    
}

// Inicializa a tela (limpa e desenha borda se necessário)
void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders)
        screenDrawBorders();
    screenHomeCursor();
    screenHideCursor();
}

// Restaura a tela ao estado normal ao sair
void screenDestroy() {
    printf("%s[0;39;49m", ESC); // Resetar cores
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

// Move o cursor para a posição (x, y)
void screenGotoxy(int x, int y) {
    printf("%s[%d;%dH", ESC, y, x);
}

// Define a cor de primeiro plano (fg) e fundo (bg)
void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";

    // Se for cor clara (acima de LIGHTGRAY), ativa atributo negrito
    if (fg > LIGHTGRAY) {
        atr[1] = '1';
        fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}
