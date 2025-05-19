# Pong PIF

Jogo desenvolvido para a cadeira de PIF da CESAR School

## 1. Membros da Equipe

- Janderson
- Maria Aparecida
- Pedro Henrique
- Rhaldney

## 2. Disciplina

Programação Imperativa e Funcional – 2025.1

## 3. Instituição de Ensino

CESAR School

---

## 4. Nome do Jogo

**Pong PIF**

---

## 5. Descrição do Jogo

**Pong PIF** é uma versão clássica jogo Pong, feita em linguagem C para terminal. O jogo terá dois jodadores, o objetivo é simples: rebater a bola e marcar pontos até vencer a partida. Adicionamos um portal que telegransporta a bolinha aleatoriamente.

### 🎮 Mecânicas de Jogo

- _Multiplayer local_: dois jogadores se enfrentam usando o teclado.
- _Controles intuitivos_: teclas W/S para o jogador 1 e setas ↑/↓ para o jogador 2.
- _Sistema de pontuação_: vence quem alcançar o número máximo de pontos antes do oponente.

### 🧠 Estrutura Interna

- A interface do jogo é baseada em ASCII.
- O jogo é estruturado em funções modulares, gameplay, movimentação e telas de vitória.
- A movimentação da bola e colisão com as barras são gerenciadas com lógica condicional.
- Utiliza a biblioteca `CLI-lib` para controle do cursor no terminal Windows.

### 🕹 Interação

- Jogo controlado totalmente via teclado.
- Exibição no terminal em tempo real com animação da bola e das barras.

---

## 6. Como Compilar e Executar o Jogo

### ✅ Pré-requisitos

- Compilador gcc instalado
- Sistema Windows (compatível com `windows.h`)
- Terminal compatível com a CLI-lib

### 📁 Estrutura de Diretórios

```
![image](https://github.com/user-attachments/assets/199d3b4f-4829-4dae-9663-dfa5eaf4fbaa)
```

### 🔧 Compilação Manual

```bash
gcc -Isrc -Iinclude -Icli-lib src/main.c src/jogo.c cli-lib/cli.c -o build/jogo.exe
```

### ▶ Execução

```bash
./build/jogo.exe
```

Alternativa com Makefile:

```bash
make
./build/jogo.exe
```

---

## 7. Pontuação

- No modo multiplayer, o primeiro jogador a marcar **4 pontos** vence.
- No modo contra a máquina, o jogador vence ao marcar **2 pontos**.
- O computador vence se o jogador deixar a bola passar **2 vezes**.

---

## 8. Tecnologias e Conceitos Utilizados

- Linguagem C (C99)
- Estruturas de decisão e repetição (`if`, `switch`, `while`)
- `structs`, ponteiros e funções modulares
- Controle de cursor com `gotoxy()` e biblioteca `CLI-lib`
- Lógica de colisão e animação no terminal
- Organização em múltiplos arquivos `.c` e `.h`

---

## 9. Implementações adicionais

- Elementos de terror:
  A bola seria uma caveirinha
