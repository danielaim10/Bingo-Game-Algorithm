#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// CITIREA CARDURILOR
void stocare(int carduri[10][5][5], int N) {
    int j, k, i;
    for (i = 0; i < N; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                scanf("%d", &carduri[i][j][k]);
            }
            carduri[i][2][2] = -carduri[i][2][2];
        }
    }
}
// INTERSCHIMBAREA COLOANELOR X SI Y
void SWAP(int carduri[][5][5], int N, int X, int Y) {
    int i, j, aux;
    for (i = 0; i < N; i++) {
        for (j = 0; j < 5; j++) {
            aux = carduri[i][j][X];
            carduri[i][j][X] = carduri[i][j][Y];
            carduri[i][j][Y] = aux;
        }
    }
}

// MUTAREA CICLICA IN JOS A NUMERELOR DE PE COLOANA X CU Y POZITII
void SHIFT(int carduri[][5][5], int N, int colX, int Ynrpoz) {
    int aux, i, j, q;
    for (i = 0; i < N; i++) {
        for (q = 0; q < Ynrpoz; q++) {
            aux = carduri[i][4][colX];

            for (j = 4; j > 0; j--) {
                carduri[i][j][colX] = carduri[i][j - 1][colX];
            }
            carduri[i][0][colX] = aux;
        }
    }
}

int absolut(int n) {
    if (n < 0)
        return -n;
    else
        return n;
}
// ORDONARE CRESCATOARE A NUMERELOR DE PE COLOANA X
void ASC(int carduri[][5][5], int N, int colX) {
    int i, j, k, aux = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < 5; j++) {
            for ( k = 0; k < 4 - j; k++){
                if (absolut(carduri[i][k][colX]) >
                    absolut(carduri[i][k + 1][colX])) {
                    aux = carduri[i][k][colX];
                    carduri[i][k][colX] = carduri[i][k + 1][colX];
                    carduri[i][k + 1][colX] = aux;
                }
            }
        }
    }
}

// ORDOARE DESCRESCATOARE A NUMERELOR DE PE COLOANA Y
void DSC(int carduri[][5][5], int N, int colY) {
    int i, j, q, aux = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < 4; j++) {
            for (q = j + 1; q < 5; q++)
                if (absolut(carduri[i][j][colY]) <
                    absolut(carduri[i][q][colY])) {
                    aux = carduri[i][j][colY];
                    carduri[i][j][colY] = carduri[i][q][colY];
                    carduri[i][q][colY] = aux;
                }
        }
    }
}

// COLORARE VALOAREA INDICATA
// COLORAREA REPREZINTA SCHIMBAREA SEMNULUI VALORII INDICATE
// PENTRU CA IN AFISARE SA SE AFISEZE VALORILE CARE AU SEMN NEGATIV CU SIMBOLUL
// # ASTFEL NESCHIMBAND VALOAREA( IN URMATOARELE FUNCTII IN CARE AM NEVOIE DE
// VALOARE FOLOSINDU-SE VALOAREA SA ABSOLUTA)
void COLOR(int carduri[][5][5], int N, int input) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (carduri[i][j][k] == input) {
                    carduri[i][j][k] = -carduri[i][j][k];
                }
            }
        }
    }
}

// FORTAREA JUCATORULUI I SA ISI AFISEZE CARDUL
void SHOW(int carduri[][5][5], int i) {
    int j, k;
    for (j = 0; j < 5; j++) {
        for (k = 0; k < 5; k++) {
            if (carduri[i][j][k] < 0) {
                printf("# ");
            } else {
                printf("%d ", carduri[i][j][k]);
            }
        }
        printf("\n");
    }
}
// AFISAREA UNUI CARD
void afisare(int carduri[][5][5], int N) {
    int j, k;
    for (j = 0; j < 5; j++) {
        for (k = 0; k < 5; k++) {
            if (carduri[N][j][k] < 0) {
                printf("# ");
            } else {
                printf("%d ", carduri[N][j][k]);
            }
        }
        printf("\n");
    }
}

int Verificare(int carduri[][5][5], int N) {
    int i, j, k, ng, max = 0, indice;
    for (i = 0; i < N; i++) {
        int dp = 0, ds = 0, scor = 0;
        // VERIFICARE ELEMENTE DIAGONALA PRINCIPALA
        for (j = 0; j < 5; j++) {
            if (carduri[i][j][j] <= 0) dp++;
        }
        if (dp == 5) scor++;
        // VERIFICARE DIAGONALA SECUNDARA
        for (j = 0; j < 5; j++) {
            if (carduri[i][j][4 - j] <= 0) ds++;
        }
        if (ds == 5) scor++;
        // VERIFICARE LINII
        for (j = 0; j < 5; j++) {
            ng = 1;
            for (k = 0; k < 5; k++)
                if (carduri[i][j][k] >= 0) {
                    ng = 0;
                    break;
                }
            if (ng == 1) scor++;
        }
        // VERIFICARE COLOANE
        for (j = 0; j < 5; j++) {
            ng = 1;
            for (k = 0; k < 5; k++)
                if (carduri[i][k][j] >= 0) {
                    ng = 0;
                    break;
                }
            if (ng == 1) scor++;
        }
        // DETERMINAM CARE CARD ARE CEL MAI MARE SCOR SI AFISAREA ACESTUIA IN
        // CONTINUARE
        if (scor > max) {
            max = scor;
            indice = i;
        }
    }
    if (max != 0) {
        printf("%d\n", indice);
        afisare(carduri, indice);
        printf("%d\n", max * 10);
        return 1;
    } else
        return 0;
}

// TRANSFORMAREA INTR-O VARIABILA DE TIP INT A VALORII BILEI CARE ESTE DE TIP
// CHAR

int numar(char bila[]) {
    int r = 0, i = 0;
    while (bila[i] != '\0') {
        r = r * 10 + (bila[i] - '0');
        i++;
    }
    return r;
}

// CITIREA BILELOR SI APLICAREA FUNCTIILOR CORESPUNZATOARE

void citirebila(int carduri[][5][5], int N, char bila[], int M) {
    int j, input, var = 0;
    for (j = 0; j < M && var == 0; j++) {
        scanf("%s", bila);
        char aux[100];
        strcpy(aux, bila);
        char *p = strtok(aux, "-");
        if ('B' == bila[0] || 'I' == bila[0] || 'N' == bila[0] ||
            'G' == bila[0] || 'O' == bila[0]) {
            input = numar(bila + 2);
            COLOR(carduri, N, input);
        }
        if (strcmp("ASC", p) == 0) ASC(carduri, N, bila[4] - '0');
        if (strcmp("DSC", p) == 0) DSC(carduri, N, bila[4] - '0');
        if (strcmp("SHOW", p) == 0) SHOW(carduri, numar(bila + 5));
        if (strcmp("SHIFT", p) == 0)
            SHIFT(carduri, N, bila[6] - '0', numar(bila + 8));
        if (strcmp("SWAP", p) == 0)
            SWAP(carduri, N, bila[5] - '0', bila[7] - '0');
        var = Verificare(carduri, N);
    }
    if (var == 0) printf("NO WINNER\n");
}

int main() {
    int N, M, carduri[200][5][5];
    char bila[100];
    scanf("%d", &N);
    stocare(carduri, N);
    scanf("%d", &M);
    citirebila(carduri, N, bila, M);

    return 0;
}
