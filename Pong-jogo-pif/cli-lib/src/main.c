#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// === Estruturas ===
typedef struct {
    int x, y;
    int dirX, dirY;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

typedef struct {
    int x, y;
} Portal;

// === Constantes ===
#define PADDLE_HEIGHT 4
#define BALL_CHAR 'O'
#define PADDLE_CHAR '|'
#define PORTAL_CHAR '#'

#define SCORE_POS_X (MAXX / 2 - 8)
#define SCORE_POS_Y MINY + 1

// === Variáveis globais ===
Ball ball;
Paddle leftPaddle, rightPaddle;
Portal portalIn, portalOut;
int scoreLeft = 0, scoreRight = 0;

// === Utilitários ===
void drawChar(int x, int y, char c) {
    screenSetColor(RED, BLACK);
    screenGotoxy(x, y);
    printf("%c", c);
}

int isInsidePaddle(Paddle p, int x, int y) {
    return (x == p.x && y >= p.y && y < p.y + p.height);
}

int isNearBorder(int x, int y) {
    return (x <= SCRSTARTX + 1 || x >= SCRENDX - 1 || y <= SCRSTARTY + 1 || y >= SCRENDY - 1);
}

// === Inicialização do jogo ===
void initGame() {
    // Raquetes
    leftPaddle.x = SCRSTARTX + 1;
    leftPaddle.y = MAXY / 2 - PADDLE_HEIGHT / 2;
    leftPaddle.height = PADDLE_HEIGHT;

    rightPaddle.x = SCRENDX - 1;
    rightPaddle.y = MAXY / 2 - PADDLE_HEIGHT / 2;
    rightPaddle.height = PADDLE_HEIGHT;

    // Bola
    ball.x = MAXX / 2;
    ball.y = MAXY / 2;
    ball.dirX = (rand() % 2 == 0) ? -1 : 1;
    ball.dirY = (rand() % 2 == 0) ? -1 : 1;

    // Portais (evita sobrepor raquetes ou bordas)
    do {
        portalIn.x = (rand() % (SCRENDX - SCRSTARTX - 4)) + SCRSTARTX + 2;
        portalIn.y = (rand() % (SCRENDY - SCRSTARTY - 4)) + SCRSTARTY + 2;
    } while (isInsidePaddle(leftPaddle, portalIn.x, portalIn.y) || isInsidePaddle(rightPaddle, portalIn.x, portalIn.y));

    do {
        portalOut.x = (rand() % (SCRENDX - SCRSTARTX - 4)) + SCRSTARTX + 2;
        portalOut.y = (rand() % (SCRENDY - SCRSTARTY - 4)) + SCRSTARTY + 2;
    } while ((portalOut.x == portalIn.x && portalOut.y == portalIn.y) ||
             isInsidePaddle(leftPaddle, portalOut.x, portalOut.y) ||
             isInsidePaddle(rightPaddle, portalOut.x, portalOut.y));
}

// === Desenho ===
void drawPaddle(Paddle p) {
    for (int i = 0; i < p.height; i++)
        drawChar(p.x, p.y + i, PADDLE_CHAR);
}

void drawBall() {
    drawChar(ball.x, ball.y, BALL_CHAR);
}

void drawPortals() {
    drawChar(portalIn.x, portalIn.y, PORTAL_CHAR);
    drawChar(portalOut.x, portalOut.y, PORTAL_CHAR);
}

void drawScore() {
    screenSetColor(LIGHTCYAN, BLACK);
    screenGotoxy(SCORE_POS_X, SCORE_POS_Y);
    printf("P1: %d   P2: %d", scoreLeft, scoreRight);
}

// === Lógica do jogo ===
void updateBall() {
    ball.x += ball.dirX;
    ball.y += ball.dirY;

    // Rebater nas bordas superior/inferior
    if (ball.y <= SCRSTARTY + 1 || ball.y >= SCRENDY - 1)
        ball.dirY *= -1;

    // Colisão com raquetes
    if (ball.x == leftPaddle.x + 1 &&
        ball.y >= leftPaddle.y && ball.y < leftPaddle.y + leftPaddle.height)
        ball.dirX = 1;

    if (ball.x == rightPaddle.x - 1 &&
        ball.y >= rightPaddle.y && ball.y < rightPaddle.y + rightPaddle.height)
        ball.dirX = -1;

    // Teleporte via portal
    if (ball.x == portalIn.x && ball.y == portalIn.y) {
        ball.x = portalOut.x;
        ball.y = portalOut.y;
    }

    // Pontuação
    if (ball.x <= SCRSTARTX) {
        scoreRight++;
        initGame();
    }

    if (ball.x >= SCRENDX) {
        scoreLeft++;
        initGame();
    }
}

// === Controles ===
void updatePaddles(int ch) {
    // Jogador 1 - 'w' e 's'
    if (ch == 'w' && leftPaddle.y > SCRSTARTY + 1)
        leftPaddle.y--;
    if (ch == 's' && leftPaddle.y + PADDLE_HEIGHT < SCRENDY)
        leftPaddle.y++;

    // Jogador 2 - setas ↑(65) e ↓(66)
    if (ch == 65 && rightPaddle.y > SCRSTARTY + 1)
        rightPaddle.y--;
    if (ch == 66 && rightPaddle.y + PADDLE_HEIGHT < SCRENDY)
        rightPaddle.y++;
}

// === Função principal ===
int main() {
    int ch = 0;

    srand(time(NULL));
    screenInit(1);         // desenha borda
    keyboardInit();
    timerInit(50);
    initGame();

    while (ch != 10) { // ENTER finaliza
        screenClear();

        if (keyhit()) {
            ch = readch();
            updatePaddles(ch);
        }

        if (timerTimeOver()) {
            updateBall();
        }

        drawPaddle(leftPaddle);
        drawPaddle(rightPaddle);
        drawBall();
        drawPortals();
        drawScore();

        screenUpdate();
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
