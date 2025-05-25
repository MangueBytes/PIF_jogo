// main.c

#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <time.h>

// Posição da bola
int ballX = 40, ballY = 12;
int lastBallX = 40, lastBallY = 12;
int ballIncX = 1, ballIncY = 1;


// Raquetes
int leftPaddleY = 10;
int rightPaddleY = 10;
const int paddleHeight = 3;

// Pontuação
int scoreLeft = 0, scoreRight = 0;

// Portal
int portalY = 6;
int portalHeight = 2;
int portalDir = 1; // 1 = desce, -1 = sobe

int portalActive = 0; // 0 = oculto, 1 = visível
long portalTimer = 0; // contar segundos do ciclo

void drawBall() {
    screenGotoxy(ballX, ballY);
    printf("o");
}

void drawPaddles() {
    for (int i = 0; i < paddleHeight; i++) {
        screenGotoxy(3, leftPaddleY + i);
        printf("|");
        screenGotoxy(76, rightPaddleY + i);
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
    if (lastBallX > MINX && lastBallX < MAXX - 1 && lastBallY > MINY && lastBallY < MAXY)
    {
        screenGotoxy(lastBallX, lastBallY);
        printf(" ");
    }
}

void drawScore() {
    screenGotoxy(39, 1);
    printf("%d - %d", scoreLeft, scoreRight);
}

void drawCenterLine() {
    for (int i = 2; i < MAXY - 1; i += 2) {
        screenGotoxy(40, i);
        printf(".");
    }
}

void updateBall() {
    // Atualiza posição anterior
    lastBallX = ballX;
    lastBallY = ballY;

    // Move a bola
    ballX += ballIncX;
    ballY += ballIncY;

    // Colisão com o portal (coluna 40)
    if (portalActive && ballX == 40 &&
        ballY >= portalY && ballY <= portalY + portalHeight) {
        ballIncY *= -1;             // inverte direção vertical
        timerUpdateTimer(40);      // acelera a bola levemente
    }

    // Colisão com topo/base
    if (ballY <= 2 || ballY >= MAXY - 1)
        ballIncY *= -1;

    // Colisão com raquete esquerda
    if (ballX >= 3 && ballX <= 4 &&
        ballY >= leftPaddleY && ballY <= leftPaddleY + paddleHeight) {
        ballIncX = 1;
        if (ballY == leftPaddleY)
            ballIncY = -1;
        else if (ballY == leftPaddleY + paddleHeight)
            ballIncY = 1;
    }

    // Colisão com raquete direita
    if (ballX >= 75 && ballX <= 76 &&
        ballY >= rightPaddleY && ballY <= rightPaddleY + paddleHeight) {
        ballIncX = -1;
        if (ballY == rightPaddleY)
            ballIncY = -1;
        else if (ballY == rightPaddleY + paddleHeight)
            ballIncY = 1;
    }

    // Gol para direita (jogador da esquerda perdeu)
    if (ballX <= 1) {
        scoreRight++;
        ballX = 40;
        ballY = 12;
        ballIncX = -1; // volta pra esquerda
        ballIncY = (rand() % 2 == 0) ? -1 : 1;
    }

    // Gol para esquerda (jogador da direita perdeu)
    if (ballX >= MAXX - 1) {
        scoreLeft++;
        ballX = 40;
        ballY = 12;
        ballIncX = 1; // volta pra direita
        ballIncY = (rand() % 2 == 0) ? -1 : 1;
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
    for (int i = 0; i < portalHeight; i++) {
        screenGotoxy(40, portalY + i);
        printf("@");
    }
    screenSetColor(RED, BLACK); // <- volta à cor padrão do jogo
}

void clearPortal() {
    for (int i = 0; i < portalHeight; i++) {
        screenGotoxy(40, portalY + i);
        printf(" ");
    }
}

void updatePortal() {
    if (portalActive) {
        portalY += portalDir;
        if (portalY <= 2 || portalY + portalHeight >= MAXY - 1)
            portalDir *= -1;
    }
}

int main() {
    
    srand(time(NULL)); // inicializa aleatoriedade
    int ch = 0;

    screenInit(1);
    screenSetColor(RED, BLACK);
    keyboardInit();
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
        if (ch == 'w' && leftPaddleY > 2) leftPaddleY--;
        if (ch == 's' && leftPaddleY + paddleHeight < MAXY - 1) leftPaddleY++;

        // Controles do jogador da direita (setas ↑/↓)
        if (ch == 27 && keyhit() && readch() == 91) {
            int arrow = readch();
            if (arrow == 65 && rightPaddleY > 2) rightPaddleY--;       // seta ↑
            else if (arrow == 66 && rightPaddleY + paddleHeight < MAXY - 1) rightPaddleY++; // seta ↓
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

        if (portalActive) {
            clearPortal();
            updatePortal();
            drawPortal();
        }

        screenUpdate();

        // Atualização do tempo
        totalTimer++;
        portalTimer++;

        // Controle do ciclo do portal
        if (!portalActive && portalTimer >= 60 * 20) {
            portalActive = 1;
            portalTimer = 0;
        }

        if (portalActive && portalTimer >= 25 * 20) {
            portalActive = 0;
            portalTimer = 0;
            clearPortal();
        }
    }
}

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
