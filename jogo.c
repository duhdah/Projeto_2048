// Compilar no windows: 
// gcc -shared -o jogo.dll -fPIC jogo.c 
// Compilar no linux:
// gcc -fPIC -shared -o libjogo.so jogo.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* Iniciar_Jogo();
int Mover(int direcao, int *matriz, int *score);
int Fim_de_Jogo(int *matriz, int *score);
void Mover_Cima(int *matriz, int *score);
void Mover_Baixo(int *matriz, int *score);
void Mover_Esquerda(int *matriz, int *score);
void Mover_Direita(int *matriz, int *score);
void Mover_Simulado(int direcao, int *matriz, int *score);
void Atualizar_Score(int *score, int valor);

int matriz[4][4];

/** ==========================
 *  Iniciar_Jogo
 *  ==========================
 *  Prepara o tabuleiro para um novo jogo.
 *  Zera toda a matriz e insere duas peças de valor 2 em posições aleatórias.
 *  Retorna um ponteiro para o primeiro elemento da matriz do jogo.
 */

int* Iniciar_Jogo() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz[i][j] = 0;
        }
    }
    int dois_iniciais = 0;
    srand(time(NULL));
    while (dois_iniciais < 2){
        int r1 = rand() % 4, r2 = rand() % 4;
        if (matriz[r1][r2] == 0){
            matriz[r1][r2] = 2;
            dois_iniciais++;
        }
    }
    return &matriz[0][0];
}

/*  ==========================
    Mover
    ==========================
    Move os blocos na direção especificada.
    Chama a função de movimento correspondente e atualiza a pontuação.
    Retorna 1 se o movimento for válido e 0 se o jogo acabar.
 */
int Mover(int direcao, int *matriz, int *score) {
    switch (direcao) {
        case 0: Mover_Cima(matriz, score); break;
        case 1: Mover_Baixo(matriz, score); break;
        case 2: Mover_Esquerda(matriz, score); break;
        case 3: Mover_Direita(matriz, score); break;
        default: return 1;
    }
    int ocupados = 0;
    for (int c = 0; c < 4; c++) {
        for (int l = 0; l < 4; l++) {
            if (matriz[l*4 + c] != 0) {
                ocupados++;
            }
        }
    }
    int novoNum = 0;
    if(ocupados < 16) {
        srand(time(NULL));
        while (novoNum == 0){
            int r1 = rand() % 16;
            if (matriz[r1] == 0){
                int valor = (rand() % 10 < 9) ? 2 : 4; 
                matriz[r1] = valor;
                novoNum = 1;
            }
        }
    }
    if (Fim_de_Jogo(matriz, score)) {
        return 0;
    }
    return 1;
}

/*  ==========================
    Mover_Cima
    ==========================
    Move todos os blocos para cima.
    Combina os blocos quando possível.
*/
void Mover_Cima(int *matriz, int *score) {
    for (int c = 0; c < 4; c++) {
        // empurra os blocos para cima
        for (int l = 1; l < 4; l++) {
            if (matriz[l*4 + c] != 0) {
                int k = l;
                while (k > 0 && matriz[(k-1)*4 + c] == 0) {
                    matriz[(k-1)*4 + c] = matriz[k*4 + c];
                    matriz[k*4 + c] = 0;
                    k--;
                }
            }
        }
        // combina os blocos
        for (int l = 0; l < 3; l++) {
            if (matriz[l*4 + c] != 0 && matriz[l*4 + c] == matriz[(l+1)*4 + c]) {
                Atualizar_Score(score, matriz[l*4 + c]);
                matriz[l*4 + c] *= 2;
                matriz[(l+1)*4 + c] = 0;
            }
        }
        // empurra novamente
        for (int l = 1; l < 4; l++) {
            if (matriz[l*4 + c] != 0) {
                int k = l;
                while (k > 0 && matriz[(k-1)*4 + c] == 0) {
                    matriz[(k-1)*4 + c] = matriz[k*4 + c];
                    matriz[k*4 + c] = 0;
                    k--;
                }
            }
        }
    }
}

/*  ==========================
    Mover_Baixo
    ==========================
    Move todos os blocos para baixo.
    Combina os blocos quando possível.
*/
void Mover_Baixo(int *matriz, int *score) {
    for (int c = 0; c < 4; c++) {
        // empurra os blocos para baixo
        for (int l = 2; l >= 0; l--) {
            if (matriz[l*4 + c] != 0) {
                int k = l;
                while (k < 3 && matriz[(k+1)*4 + c] == 0) {
                    matriz[(k+1)*4 + c] = matriz[k*4 + c];
                    matriz[k*4 + c] = 0;
                    k++;
                }
            }
        }
        // combina os blocos
        for (int l = 3; l > 0; l--) {
            if (matriz[l*4 + c] != 0 && matriz[l*4 + c] == matriz[(l-1)*4 + c]) {
                Atualizar_Score(score, matriz[l*4 + c]);
                matriz[l*4 + c] *= 2;
                matriz[(l-1)*4 + c] = 0;
            }
        }
        // empurra novamente
        for (int l = 2; l >= 0; l--) {
            if (matriz[l*4 + c] != 0) {
                int k = l;
                while (k < 3 && matriz[(k+1)*4 + c] == 0) {
                    matriz[(k+1)*4 + c] = matriz[k*4 + c];
                    matriz[k*4 + c] = 0;
                    k++;
                }
            }
        }
    }
}

/*  ==========================
    Mover_Esquerda
    ==========================
    Move todos os blocos para esquerda.
    Combina os blocos quando possível.
*/
void Mover_Esquerda(int *matriz, int *score) {
    for (int l = 0; l < 4; l++) {
        // empurra os blocos para a esquerda
        for (int c = 1; c < 4; c++) {
            if (matriz[l*4 + c] != 0) {
                int k = c;
                while (k > 0 && matriz[l*4 + k - 1] == 0) {
                    matriz[l*4 + k - 1] = matriz[l*4 + k];
                    matriz[l*4 + k] = 0;
                    k--;
                }
            }
        }
        // combina os blocos
        for (int c = 0; c < 3; c++) {
            if (matriz[l*4 + c] != 0 && matriz[l*4 + c] == matriz[l*4 + c + 1]) {
                Atualizar_Score(score, matriz[l*4 + c]);
                matriz[l*4 + c] *= 2;
                matriz[l*4 + c + 1] = 0;
            }
        }
        // empurra novamente
        for (int c = 1; c < 4; c++) {
            if (matriz[l*4 + c] != 0) {
                int k = c;
                while (k > 0 && matriz[l*4 + k - 1] == 0) {
                    matriz[l*4 + k - 1] = matriz[l*4 + k];
                    matriz[l*4 + k] = 0;
                    k--;
                }
            }
        }
    }
}

/*  ==========================
    Mover_Direita
    ==========================
    Move todos os blocos para direita.
    Combina os blocos quando possível.
*/
void Mover_Direita(int *matriz, int *score) {
    for (int l = 0; l < 4; l++) {
        // empurra os blocos para a direita
        for (int c = 2; c >= 0; c--) {
            if (matriz[l*4 + c] != 0) {
                int k = c;
                while (k < 3 && matriz[l*4 + k + 1] == 0) {
                    matriz[l*4 + k + 1] = matriz[l*4 + k];
                    matriz[l*4 + k] = 0;
                    k++;
                }
            }
        }
        // combina os blocos
        for (int c = 3; c > 0; c--) {
            if (matriz[l*4 + c] != 0 && matriz[l*4 + c] == matriz[l*4 + c - 1]) {
                Atualizar_Score(score, matriz[l*4 + c]);
                matriz[l*4 + c] *= 2;
                matriz[l*4 + c - 1] = 0;
            }
        }
        // empurra novamente
        for (int c = 2; c >= 0; c--) {
            if (matriz[l*4 + c] != 0) {
                int k = c;
                while (k < 3 && matriz[l*4 + k + 1] == 0) {
                    matriz[l*4 + k + 1] = matriz[l*4 + k];
                    matriz[l*4 + k] = 0;
                    k++;
                }
            }
        }
    }
}


/*  ==========================
    Matrizes_Iguais
    ==========================
    Função usada na função Fim_de_Jogo para conferir se as matrizes são iguais
    Se forem iguais para todos movimentos, é fim de jogo.
    Retorna 0 se as matrizes forem diferentes e 1 se forem iguais.
*/
int Matrizes_Iguais(int *a, int *b) {
    for (int i = 0; i < 16; i++) {
        if (a[i] != b[i]) {
            return 0; 
        }
    }
    return 1;
}

/*  ==========================
    Matrizes_Iguais
    ==========================
    Função usada na função Fim_de_Jogo para conferir se as matrizes são iguais
    Se forem iguais para todos movimentos, é fim de jogo.
    Retorna 0 se as matrizes forem diferentes e 1 se forem iguais.
*/
int Fim_de_Jogo(int *matriz, int *score) {
    int copia[16];
    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < 16; i++) copia[i] = matriz[i];
        Mover_Simulado(dir, copia, score);
        if (!Matrizes_Iguais(matriz, copia)) {
            return 0; 
        }
    }
    return 1; 
}

/*  ==========================
    Mover_Simulado
    ==========================
    Função que simula o movimento dos blocos na matriz
    Recebe como parâmetro uma cópia da matriz original para evitar modificá-la.
*/
void Mover_Simulado(int direcao, int *matriz, int *score) {
    switch (direcao) {
        case 0: Mover_Cima(matriz, score); break;
        case 1: Mover_Baixo(matriz, score); break;
        case 2: Mover_Esquerda(matriz, score); break;
        case 3: Mover_Direita(matriz, score); break;
        default: break;
    }
}

/*  ==========================
    Atualizar_Score
    ==========================
    Função que atualiza o score com base no valor das células que foram somadas.
    Recebe como parâmetro o ponteiro para o score e o valor da célula.
*/

void Atualizar_Score(int *score, int valor) {
    if (valor == 2) {
       *score += 10; 
    }else if  (valor == 4) {
       *score += 20;
    }else if (valor == 8) {
       *score += 40;
    }else if (valor == 16) {
       *score += 80;
    }else if (valor == 32) {
       *score += 160;
    }else if (valor == 64) {
       *score += 320;
    }else if (valor == 128) {
       *score += 640;
    }else if (valor == 256) {
       *score += 1280;
    }else if (valor == 512) {
       *score += 2560;
    }else if (valor == 1024) {
       *score += 5120;
    }else if (valor == 2048) {
       *score += 10240;
    }
    else if (valor == 4096) {
       *score += 20480;
    }else if (valor == 8192) {
       *score += 40960;
    }
    else if (valor == 16384) {
       *score += 81920;
    }else if (valor == 32768) {
       *score += 1000000;
    }
}