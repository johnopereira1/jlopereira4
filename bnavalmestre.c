#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 7

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para verificar se pode posicionar um navio (sem sobreposição)
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int dx, int dy) {
    for (int i = 0; i < 3; i++) {
        int l = linha + i * dx;
        int c = coluna + i * dy;
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) return 0;
        if (tabuleiro[l][c] != 0) return 0;
    }
    return 1;
}

// Função para posicionar navio
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int dx, int dy) {
    for (int i = 0; i < 3; i++) {
        int l = linha + i * dx;
        int c = coluna + i * dy;
        tabuleiro[l][c] = 3;
    }
}

// Função para criar matriz em formato de cone
void criarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE / 2) - i && j <= (TAMANHO_HABILIDADE / 2) + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para criar matriz em formato de cruz
void criarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para criar matriz em formato de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para aplicar habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_linha, int origem_coluna) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int lin = origem_linha - TAMANHO_HABILIDADE/2 + i;
            int col = origem_coluna - TAMANHO_HABILIDADE/2 + j;

            if (lin >= 0 && lin < TAMANHO_TABULEIRO && col >= 0 && col < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[lin][col] == 0) {
                    tabuleiro[lin][col] = 5;
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro com símbolos
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");  // Água
            else if (tabuleiro[i][j] == 3)
                printf("N ");  // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* ");  // Área de habilidade
            else
                printf("? ");  // Valor indefinido (segurança)
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posicionar dois navios na horizontal/vertical
    if (podePosicionar(tabuleiro, 0, 2, 0, 1))
        posicionarNavio(tabuleiro, 0, 2, 0, 1);  // Horizontal

    if (podePosicionar(tabuleiro, 1, 0, 1, 0))
        posicionarNavio(tabuleiro, 1, 0, 1, 0);  // Vertical

    // Posicionar dois navios na diagonal
    if (podePosicionar(tabuleiro, 2, 2, 1, 1))
        posicionarNavio(tabuleiro, 2, 2, 1, 1);  // Diagonal principal

    if (podePosicionar(tabuleiro, 4, 4, 1, -1))
        posicionarNavio(tabuleiro, 4, 4, 1, -1); // Diagonal secundária

    // Criar matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 1);
    aplicarHabilidade(tabuleiro, cruz, 4, 4);
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);

    // Exibir tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
