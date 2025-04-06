#include <stdio.h>

// Tamanho fixo do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // 1. Declarar e inicializar o tabuleiro 10x10 com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Preenche todas as posições com 0 (água)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Criar os dois navios (valores 3 em arrays unidimensionais)
    int navio_horizontal[TAMANHO_NAVIO] = {3, 3, 3}; // Representa navio horizontal
    int navio_vertical[TAMANHO_NAVIO]   = {3, 3, 3}; // Representa navio vertical

    // 3. Definir as posições iniciais dos navios (linha, coluna)
    // OBS: Estas posições devem ser válidas e não podem se sobrepor
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    int linha_vertical = 5;
    int coluna_vertical = 7;

    // 4. Verificar se os navios cabem no tabuleiro e não se sobrepõem

    // Verificar navio horizontal
    if (coluna_horizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;

        // Verificar sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_horizontal][coluna_horizontal + i] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posicionar o navio horizontal
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_horizontal][coluna_horizontal + i] = navio_horizontal[i];
            }
        }
    }

    // Verificar navio vertical
    if (linha_vertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;

        // Verificar sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_vertical + i][coluna_vertical] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posicionar o navio vertical
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_vertical + i][coluna_vertical] = navio_vertical[i];
            }
        }
    }

    // ============ INÍCIO DAS NOVAS FUNCIONALIDADES (NAVIOS DIAGONAIS) ============

    // 5. Adicionando dois navios diagonais (valor 3)

    int navio_diagonal1[TAMANHO_NAVIO] = {3, 3, 3}; // Diagonal principal (↘)
    int navio_diagonal2[TAMANHO_NAVIO] = {3, 3, 3}; // Diagonal secundária (↙)

    // Coordenadas iniciais
    int linha_diag1 = 0;
    int coluna_diag1 = 0;

    int linha_diag2 = 3;
    int coluna_diag2 = 9;

    // Verificar se navio diagonal ↘ cabe e não se sobrepõe
    if (linha_diag1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna_diag1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_diag1 + i][coluna_diag1 + i] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_diag1 + i][coluna_diag1 + i] = navio_diagonal1[i];
            }
        }
    }

    // Verificar se navio diagonal ↙ cabe e não se sobrepõe
    if (linha_diag2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna_diag2 - (TAMANHO_NAVIO - 1) >= 0) {
        int sobreposicao = 0;

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_diag2 + i][coluna_diag2 - i] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_diag2 + i][coluna_diag2 - i] = navio_diagonal2[i];
            }
        }
    }

    // ============ FIM DAS NOVAS FUNCIONALIDADES ============

    // 6. Exibir o tabuleiro na tela
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
