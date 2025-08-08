/* batalha.c
   Desafio Batalha Naval - Novato / Aventureiro / Mestre
   Autor: (Seu nome)
   Compile: gcc -o batalha batalha.c
   Execute: ./batalha
*/

#include <stdio.h>
#include <string.h>

#define NOVATO_SIZE 5
#define AVAN_SIZE 10

/* ---------- Funções utilitárias ---------- */

void limpar_tabuleiro_int(int rows, int cols, int tab[rows][cols]) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            tab[i][j] = 0;
}

void imprimir_tabuleiro_int(int rows, int cols, int tab[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

/* ---------- Nível Novato (5x5) ---------- */

void nivel_novato() {
    int tab[NOVATO_SIZE][NOVATO_SIZE];
    limpar_tabuleiro_int(NOVATO_SIZE, NOVATO_SIZE, tab);

    printf("=== NIVEL NOVATO (Tabuleiro 5x5) ===\n");

    // Navio vertical: coluna 1, linhas 0..2 (tamanho 3)
    printf("Posicionando navio vertical (valor 3):\n");
    for (int i = 0; i <= 2; ++i) {
        tab[i][1] = 3;
        printf("  Parte do navio vertical: (%d, %d)\n", i, 1);
    }

    // Navio horizontal: linha 4, colunas 2..4 (tamanho 3)
    printf("Posicionando navio horizontal (valor 3):\n");
    for (int j = 2; j <= 4; ++j) {
        tab[4][j] = 3;
        printf("  Parte do navio horizontal: (%d, %d)\n", 4, j);
    }

    printf("\nTabuleiro (0=vazio, 3=navio):\n");
    imprimir_tabuleiro_int(NOVATO_SIZE, NOVATO_SIZE, tab);

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

/* ---------- Nível Aventureiro (10x10) ---------- */

void posicionar_navio_vertical(int rows, int cols, int tab[rows][cols], int start_row, int col, int size) {
    for (int i = 0; i < size; ++i) {
        int r = start_row + i;
        if (r >= 0 && r < rows && col >= 0 && col < cols)
            tab[r][col] = 3;
    }
}

void posicionar_navio_horizontal(int rows, int cols, int tab[rows][cols], int row, int start_col, int size) {
    for (int j = 0; j < size; ++j) {
        int c = start_col + j;
        if (row >= 0 && row < rows && c >= 0 && c < cols)
            tab[row][c] = 3;
    }
}

void posicionar_navio_diagonal_desc(int rows, int cols, int tab[rows][cols], int start_row, int start_col, int size) {
    // diagonal descendente (soma índices)
    for (int k = 0; k < size; ++k) {
        int r = start_row + k;
        int c = start_col + k;
        if (r >= 0 && r < rows && c >= 0 && c < cols)
            tab[r][c] = 3;
    }
}

void posicionar_navio_diagonal_asc(int rows, int cols, int tab[rows][cols], int start_row, int start_col, int size) {
    // diagonal ascendente (linha diminui, coluna aumenta)
    for (int k = 0; k < size; ++k) {
        int r = start_row - k;
        int c = start_col + k;
        if (r >= 0 && r < rows && c >= 0 && c < cols)
            tab[r][c] = 3;
    }
}

void nivel_aventureiro() {
    int tab[AVAN_SIZE][AVAN_SIZE];
    limpar_tabuleiro_int(AVAN_SIZE, AVAN_SIZE, tab);

    printf("=== NIVEL AVENTUREIRO (Tabuleiro 10x10) ===\n");

    // Navio vertical de tamanho 4 em (1,2) -> (4,2)
    posicionar_navio_vertical(AVAN_SIZE, AVAN_SIZE, tab, 1, 2, 4);
    printf("Navio vertical (tamanho 4) em coluna 2, linhas 1..4\n");

    // Navio horizontal de tamanho 3 em (9,5) -> (9,7)
    posicionar_navio_horizontal(AVAN_SIZE, AVAN_SIZE, tab, 9, 5, 3);
    printf("Navio horizontal (tamanho 3) em linha 9, colunas 5..7\n");

    // Navio diagonal descendente (tamanho 4) começando em (0,0)
    posicionar_navio_diagonal_desc(AVAN_SIZE, AVAN_SIZE, tab, 0, 0, 4);
    printf("Navio diagonal descendente (tamanho 4) começando em (0,0)\n");

    // Navio diagonal ascendente (tamanho 3) começando em (6,1) -> (6,1),(5,2),(4,3)
    posicionar_navio_diagonal_asc(AVAN_SIZE, AVAN_SIZE, tab, 6, 1, 3);
    printf("Navio diagonal ascendente (tamanho 3) começando em (6,1)\n");

    printf("\nTabuleiro (0=vazio, 3=navio):\n");
    imprimir_tabuleiro_int(AVAN_SIZE, AVAN_SIZE, tab);

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

/* ---------- Nível Mestre - Habilidades com matrizes (10x10) ---------- */

/*
  Usaremos máscaras 5x5 para as habilidades com centro no (2,2) da máscara.
  Valores: 0 = não afeta, 1 = área atingida.
*/

void aplicar_mascara(int rows, int cols, int tab[rows][cols], int center_r, int center_c, int mask_rows, int mask_cols, int mask[mask_rows][mask_cols]) {
    int r0 = center_r - mask_rows/2;
    int c0 = center_c - mask_cols/2;

    for (int i = 0; i < mask_rows; ++i) {
        for (int j = 0; j < mask_cols; ++j) {
            int r = r0 + i;
            int c = c0 + j;
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                if (mask[i][j] == 1) {
                    // Marcamos uma área atingida com 1 (se já houver navio 3, podemos manter 3)
                    if (tab[r][c] == 0) tab[r][c] = 1;
                    else if (tab[r][c] == 3) tab[r][c] = 4; // 4 = navio atingido (opcional)
                }
            }
        }
    }
}

void nivel_mestre() {
    int tab[AVAN_SIZE][AVAN_SIZE];
    limpar_tabuleiro_int(AVAN_SIZE, AVAN_SIZE, tab);

    printf("=== NIVEL MESTRE (Tabuleiro 10x10 + habilidades) ===\n");

    // Primeiro, posicionamos uns navios (como no aventureiro) para testar interações
    posicionar_navio_horizontal(AVAN_SIZE, AVAN_SIZE, tab, 2, 2, 4); // linha 2, col 2..5
    posicionar_navio_vertical(AVAN_SIZE, AVAN_SIZE, tab, 5, 7, 3);   // col 7, linhas 5..7

    printf("Navios posicionados (visual para teste):\n");
    imprimir_tabuleiro_int(AVAN_SIZE, AVAN_SIZE, tab);
    printf("\n");

    // Definimos máscaras 5x5 (centro índice [2][2])
    int mask_cone[5][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int mask_octa[5][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    int mask_cruz[5][5] = {
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    // Menu simples para usuário testar aplicação das habilidades
    int opcao = 0;
    while (1) {
        printf("Escolha habilidade para aplicar (0 = sair):\n");
        printf(" 1 - Cone\n 2 - Octaedro\n 3 - Cruz\n 4 - Aplicar as 3 (teste)\n 0 - Voltar ao menu principal\n");
        printf("Opção: ");
        if (scanf("%d", &opcao) != 1) {
            // limpa entrada
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            opcao = -1;
            continue;
        }
        if (opcao == 0) {
            // limpar buffer do Enter
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            break;
        }

        int r, c;
        printf("Digite a posição central onde aplicar (linha coluna) 0..9  (ex: 4 5): ");
        if (scanf("%d %d", &r, &c) != 2) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Entrada inválida. Tente de novo.\n");
            continue;
        }

        // aplicar máscara escolhida
        if (opcao == 1) {
            aplicar_mascara(AVAN_SIZE, AVAN_SIZE, tab, r, c, 5, 5, mask_cone);
            printf("Aplicado CONE em (%d,%d).\n", r, c);
        } else if (opcao == 2) {
            aplicar_mascara(AVAN_SIZE, AVAN_SIZE, tab, r, c, 5, 5, mask_octa);
            printf("Aplicado OCTAEDRO em (%d,%d).\n", r, c);
        } else if (opcao == 3) {
            aplicar_mascara(AVAN_SIZE, AVAN_SIZE, tab, r, c, 5, 5, mask_cruz);
            printf("Aplicado CRUZ em (%d,%d).\n", r, c);
        } else if (opcao == 4) {
            aplicar_mascara(AVAN_SIZE, AVAN_SIZE, tab, r, c, 5, 5, mask_cone);
            aplicar_mascara(AVAN_SIZE, AVAN_SIZE, tab, r, c, 5, 5, mask_octa);
            aplicar_mascara(AVAN_SIZE, AVAN_SIZE, tab, r, c, 5, 5, mask_cruz);
            printf("Aplicadas as 3 máscaras em (%d,%d).\n", r, c);
        } else {
            printf("Opção inválida.\n");
        }

        // Mostrar tabuleiro após aplicação
        printf("\nTabuleiro (0=vazio, 1=atingido, 3=navio, 4=navio atingido):\n");
        imprimir_tabuleiro_int(AVAN_SIZE, AVAN_SIZE, tab);
        printf("\n");
        // limpar buffer do Enter
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

/* ---------- Menu principal ---------- */

int main() {
    int escolha = -1;
    while (1) {
        printf("\n=== BATALHA NAVAL - Desafio MateCheck ===\n");
        printf("Escolha o nível que deseja executar:\n");
        printf(" 1 - Novato (tabuleiro 5x5, 2 navios)\n");
        printf(" 2 - Aventureiro (tabuleiro 10x10, 4 navios)\n");
        printf(" 3 - Mestre (habilidades com máscaras)\n");
        printf(" 0 - Sair\n");
        printf("Opção: ");

        if (scanf("%d", &escolha) != 1) {
            // limpar entrada inválida
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            escolha = -1;
            continue;
        }

        // limpar newline pendente para getchar() depois
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}

        if (escolha == 1) {
            nivel_novato();
        } else if (escolha == 2) {
            nivel_aventureiro();
        } else if (escolha == 3) {
            nivel_mestre();
        } else if (escolha == 0) {
            printf("Saindo... boa sorte com seu trabalho na Estácio!\n");
            break;
        } else {
            printf("Opção inválida, tente novamente.\n");
        }
    }

    return 0;
}
