// main.c
#include "structs.h"
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <time.h>

#define SCORE_LIMIT 30

Ball ball = {40, 12, 40, 12, 1, 1};
Paddle leftPaddle = {10, 3};
Paddle rightPaddle = {10, 3};
Score score = {0, 0};
Portal portal = {6, 2, 1, 0, 0};

void drawBall() {
    screenGotoxy(ball.x, ball.y);
    printf("o");
}

void drawPaddles() {
    for (int i = 0; i < leftPaddle.height; i++) {
        screenGotoxy(3, leftPaddle.y + i);
        printf("|");
        screenGotoxy(76, rightPaddle.y + i);
        printf("|");
    }
}

void clearPaddles() {
    for (int i = 0; i < MAXY; i++) {
        screenGotoxy(3, i);
        printf(" ");
        screenGotoxy(76, i);
        printf(" ");
    }
}

void clearBall() {
    // Garante que não apague nas bordas do campo
    if (ball.lastX > MINX && ball.lastX < MAXX - 1 && ball.lastY > MINY && ball.lastY < MAXY)
    {
        screenGotoxy(ball.lastX, ball.lastY);
        printf(" ");
    }
}

void drawScore() {
    screenGotoxy(39, 1);
    printf("%d - %d", score.left, score.right);
}

void drawCenterLine() {
    for (int i = 2; i < MAXY - 1; i += 2) {
        screenGotoxy(40, i);
        printf(".");
    }
}

void updateBall() {
    // Atualiza posição anterior
    ball.lastX = ball.x;
    ball.lastY = ball.y;

    // Move a bola
    ball.x += ball.incX;
    ball.y += ball.incY;

    // Colisão com o portal (coluna 40)
    if (portal.active && ball.x == 40 &&
        ball.y >= portal.y && ball.y <= portal.y + leftPaddle.height) {
        ball.incY *= -1;             // inverte direção vertical
        timerUpdateTimer(40);      // acelera a bola levemente
    }

    // Colisão com topo/base
    if (ball.y <= 2 || ball.y >= MAXY - 1)
        ball.incY *= -1;

    // Colisão com raquete esquerda
    if (ball.x >= 3 && ball.x <= 4 &&
        ball.y >= leftPaddle.y && ball.y <= leftPaddle.y + leftPaddle.height) {
        ball.incX = 1;
        if (ball.y == leftPaddle.y)
            ball.incY = -1;
        else if (ball.y == leftPaddle.y + leftPaddle.height)
            ball.incY = 1;
    }

    // Colisão com raquete direita
    if (ball.x >= 75 && ball.x <= 76 &&
        ball.y >= rightPaddle.y && ball.y <= rightPaddle.y + leftPaddle.height) {
        ball.incX = -1;
        if (ball.y == rightPaddle.y)
            ball.incY = -1;
        else if (ball.y == rightPaddle.y + portal.height)
            ball.incY = 1;
    }

    // Gol para direita (jogador da esquerda perdeu)
    if (ball.x <= 1) {
        score.right++;
        ball.x = 40;
        ball.y = 12;
        ball.incX = -1; // volta pra esquerda
        ball.incY = (rand() % 2 == 0) ? -1 : 1;
    }

    // Gol para esquerda (jogador da direita perdeu)
    if (ball.x >= MAXX - 1) {
        score.left++;
        ball.x = 40;
        ball.y = 12;
        ball.incX = 1; // volta pra direita
        ball.incY = (rand() % 2 == 0) ? -1 : 1;
    }
}


void clearGameArea() {
    for (int i = 2; i < MAXY; i++) {
        for (int j = 4; j < 76; j++) {
            screenGotoxy(j, i);
            printf(" ");
        }
    }

}

void drawPortal() {
    screenSetColor(LIGHTRED, BLACK); // <- deixa o portal mais visível
    for (int i = 0; i < portal.height; i++) {
        screenGotoxy(40, portal.y + i);
        printf("@");
    }
    screenSetColor(RED, BLACK); // <- volta à cor padrão do jogo
}

void clearPortal() {
    for (int i = 0; i < portal.height; i++) {
        screenGotoxy(40, portal.y + i);
        printf(" ");
    }
}

void updatePortal() {
    if (portal.active) {
        portal.y += portal.dir;
        if (portal.y <= 2 || portal.y + portal.height >= MAXY - 1)
            portal.dir *= -1;
    }
}

int main() {

    
    
    srand(time(NULL)); // inicializa aleatoriedade
    int ch = 0;

    screenInit(1);
    screenSetColor(RED, BLACK);
    keyboardInit();

    // Tela de boas-vindas
screenClear();
screenGotoxy(30, 10);
printf("=== BEM-VINDO AO PONG ===");
screenGotoxy(30, 13);
printf("Pressione ENTER para comecar...");
screenUpdate();

// Espera pelo ENTER
int key = 0;
while (key != 10) {
    if (keyhit()) key = readch();
}

    // Recria borda após ENTER
    screenInit(1);
    screenSetColor(RED, BLACK); // reaplica cor também
    timerInit(50);
    long totalTimer = 0; // contador geral de tempo

    drawScore();
    drawCenterLine();
    drawPaddles();
    drawBall();
    screenUpdate();

    while (ch != 10) { // Tecla Enter para sair 
    if (keyhit()) {
        ch = readch();

        // Controles do jogador da esquerda (w/s)
        if (ch == 'w' && leftPaddle.y > 2) leftPaddle.y--;
        if (ch == 's' && leftPaddle.y + leftPaddle.height < MAXY - 1) leftPaddle.y++;

        // Controles do jogador da direita (setas ↑/↓)
        if (ch == 27 && keyhit() && readch() == 91) {
            int arrow = readch();
            if (arrow == 65 && rightPaddle.y > 2) rightPaddle.y--;       // seta ↑
            else if (arrow == 66 && rightPaddle.y + leftPaddle.height < MAXY - 1) rightPaddle.y++; // seta ↓
        }
    }
    

    if (timerTimeOver()) {
        clearGameArea();
        clearPaddles();
        clearBall(); 
        updateBall(); 

        drawCenterLine();
        drawPaddles();
        drawBall();
        drawScore();

        if (portal.active) {
            clearPortal();
            updatePortal();
            drawPortal();
        }

        screenUpdate();

        // Atualização do tempo
        totalTimer++;
        portal.timer++;

        // Controle do ciclo do portal
        if (!portal.active && portal.timer >= 60 * 20) {
            portal.active = 1;
            portal.timer = 0;
        }

        if (portal.active && portal.timer >= 25 * 20) {
            portal.active = 0;
            portal.timer = 0;
            clearPortal();
        }

        // Verifica se alguém venceu
if (score.left >= SCORE_LIMIT || score.right >= SCORE_LIMIT) {
    screenClear();
    screenGotoxy(30, 10);

    if (score.left >= SCORE_LIMIT)
        printf("Jogador da ESQUERDA venceu!");
    else
        printf("Jogador da DIREITA venceu!");

    screenGotoxy(28, 13);
    printf("Pressione ENTER para jogar novamente...");
    screenUpdate();

    // Espera ENTER
    int key = 0;
    while (key != 10) {
        if (keyhit()) key = readch();
    }

    // Reinicia jogo (pontos, posições, velocidade, etc.)
    ball.x = 40;
    ball.y = 12;
    ball.incX = 1;
    ball.incY = 1;

    score.left = 0;
    score.right = 0;
    leftPaddle.y = 10;
    rightPaddle.y = 10;

    timerUpdateTimer(50);
    screenInit(1);
    screenSetColor(RED, BLACK);
    drawScore();
    drawCenterLine();
    drawPaddles();
    drawBall();
    screenUpdate();
}

    }
}

    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
