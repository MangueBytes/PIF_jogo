/**
 * timer.c
 * Created on Aug 23rd, 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

// Variáveis estáticas para controle do tempo
static struct timeval timer, now;
static int delay = -1;

// Inicializa o timer com intervalo em milissegundos
void timerInit(int valueMilliSec) {
    delay = valueMilliSec;
    gettimeofday(&timer, NULL);
}

// Finaliza o uso do timer
void timerDestroy() {
    delay = -1;
}

// Atualiza o tempo base e o novo intervalo
void timerUpdateTimer(int valueMilliSec) {
    delay = valueMilliSec;
    gettimeofday(&timer, NULL);
}

// Retorna diferença de tempo (em ms) desde a última atualização
int getTimeDiff() {
    gettimeofday(&now, NULL);
    long diff = (((now.tv_sec - timer.tv_sec) * 1000000L) + (now.tv_usec - timer.tv_usec)) / 1000;
    return (int) diff;
}

// Verifica se o tempo definido expirou
int timerTimeOver() {
    if (getTimeDiff() > delay) {
        gettimeofday(&timer, NULL);  // Reinicia o timer
        return 1;
    }
    return 0;
}

// Imprime o tempo decorrido desde a última marcação
void timerPrint() {
    printf("Timer: %d ms", getTimeDiff());
}