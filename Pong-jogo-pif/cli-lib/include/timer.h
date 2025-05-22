/**
 * timer.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#ifndef __TIMER_H__
#define __TIMER_H__

/**
 * Inicializa o temporizador com o intervalo desejado (em milissegundos).
 * @param valueMilliSec Intervalo do temporizador em milissegundos.
*/
void timerInit(int valueMilliSec);

/**
 * Finaliza o temporizador e libera recursos (se necessário).
*/
void timerDestroy();

/**
 * Atualiza o tempo base do temporizador para um novo intervalo.
 * @param valueMilliSec Novo valor de intervalo em milissegundos.
*/
void timerUpdateTimer(int valueMilliSec);

/**
 * Retorna 1 se o tempo do intervalo foi atingido, 0 caso contrário.
 * Ideal para ser chamado no loop principal do jogo.
*/
int timerTimeOver();

/**
 * (Opcional) Imprime o tempo atual ou restante, útil para debug.
*/
void timerPrint();

#endif /* __TIMER_H__ */
