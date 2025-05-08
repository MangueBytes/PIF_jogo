# PIF_jogo
Jogo desenvolvido para a cadeira de PIF da CESAR School
# Fuga da Torre

## 1. Membros da Equipe
- Janderson
- Pedro Henrique
- Rhaldney


## 2. Disciplina
Programação Imperativa e Funcional – 2025.1

## 3. Instituição de Ensino
CESAR School

---

## 4. Nome do Jogo
*Fuga da Torre* (Escape Tower)

---

## 5. Descrição do Jogo

*Fuga da Torre* é um jogo de aventura e quebra-cabeça baseado em texto. O jogador está preso em uma torre mágica e precisa escapar passando por diferentes andares, enfrentando desafios variados como charadas, escolhas estratégicas e combates simples.

### 🎮 Mecânicas de Jogo

- *Charadas*: o jogador precisa responder corretamente para abrir portas mágicas.
- *Escolhas*: cada decisão leva a um caminho diferente com consequências únicas.
- *Combates simples*: o jogador enfrenta criaturas com base em lógica e sorte.

### 🧠 Estrutura Interna

- As salas e itens são representados usando structs.
- O labirinto é gerado dinamicamente com uso de ponteiros e alocação dinâmica.
- A pontuação é baseada em tempo de conclusão e nas escolhas feitas.

### 🕹 Interação

- Entrada via teclado com menus, perguntas e comandos simples.
- Saída formatada com a biblioteca [CLI-lib](https://github.com/tgfb/cli-lib) para uma melhor experiência no terminal.

---

## 6. Como Compilar e Executar o Jogo

### ✅ Pré-requisitos

- Compilador gcc instalado
- Sistema Linux/macOS ou terminal compatível (no Windows, use WSL ou Git Bash)
- Estrutura de pastas corretamente organizada (veja abaixo)

### 📁 Estrutura de Diretórios

![image](https://github.com/user-attachments/assets/199d3b4f-4829-4dae-9663-dfa5eaf4fbaa)

### 🔧 Compilação Manual

No terminal, execute o seguinte comando:

bash
gcc -Isrc -Iinclude -Icli-lib src/main.c 
src/jogo.c cli-lib/cli.c -o build/
jogo.exe

Execução:
./build?jogo.exe

Alternativa com Makefile: 
make
./build/jogo.exe

## 7. Pontuação
Acertos em desafios geram pontos.

Decisões estratégicas afetam o desfecho e pontuação.

Tempo total de fuga influencia na pontuação final.

## 8. Tecnologias e Conceitos Utilizados
Linguagem C (C99)

structs e ponteiros

Alocação dinâmica de memória

Estruturas de decisão e repetição (if, switch, for, while)

Modularização com arquivos .h e .c

Interação em terminal com CLI-lib
