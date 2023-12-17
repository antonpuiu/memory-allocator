#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* n;
int N, count = 0;

void INITIALIZE()
{
    n = (char*)calloc(N, sizeof(char));
}

void FINALIZE()
{
    free(n);
}

void DUMP()
{
    int i = 0;

    printf("%08X\t", 0);

    while (i < N) {
        if ((i % 16 == 0) && (i != 0)) {
            printf("\n");
            printf("%08X\t", i);
        }

        if ((i + 1) % 8 != 0)
            printf("%02X ", (int)(n[i]) & 0xff);
        else
            printf("%02X  ", (int)(n[i]) & 0xff);
        i++;
    }

    printf("\n");
    printf("%08X \n", N);
}

int ALLOC(int x)
{
    int k = 0;

    if ((*(int*)(&n[k]) == 0) && (N - k - *(int*)(&n[k + 8]) > 12 + x)) {
        *(int*)(&n[k]) = 4;
        *(int*)(&n[k + 4]) = 0;
        *(int*)(&n[k + 8]) = 0;
        *(int*)(&n[k + 12]) = x + 12;
        printf("16\n");
        return 0;
    }

    if ((*(int*)(&n[k]) != 0) && (*(int*)(&n[k]) - 16 - x >= 0)) {
        *(int*)(&n[k + 4]) = n[k];
        *(int*)(&n[k + *(int*)(&n[k]) + 4]) = 4;
        *(int*)(&n[k + 8]) = 0;
        *(int*)(&n[k + 12]) = 12 + x;
        *(int*)(&n[k]) = 4;
        printf("16\n");
        return 0;
    }

    k = *(int*)(&n[k]);

    if ((*(int*)(&n[k]) == 0) && (N - k - *(int*)(&n[k + 8]) > 12 + x)) {
        *(int*)(&n[k + *(int*)(&n[k + 8])]) = 0;
        *(int*)(&n[k + *(int*)(&n[k + 8]) + 4]) = k;
        *(int*)(&n[k + *(int*)(&n[k + 8]) + 8]) = x + 12;
        *(int*)(&n[k]) = k + *(int*)(&n[k + 8]);
        printf("%d\n", k + *(int*)(&n[k + 8]) + 12);
        return 0;
    }

    if (*(int*)(&n[k]) - *(int*)(&n[k + 8]) - k - 12 - x >= 0) {
        *(int*)(&n[k + *(int*)(&n[k + 8])]) = *(int*)(&n[k]);
        *(int*)(&n[k + *(int*)(&n[k + 8]) + 4]) = k;
        *(int*)(&n[k + *(int*)(&n[k + 8]) + 8]) = x + 12;
        *(int*)(&n[*(int*)(&n[k]) + 4]) = k + *(int*)(&n[k + 8]);
        *(int*)(&n[k]) = k + *(int*)(&n[k + 8]);
        printf("%d\n", k + *(int*)(&n[k + 8]) + 12);
        return 0;
    }
    k = *(int*)(&n[k]);

    while (k != 0) {
        if ((*(int*)(&n[k]) == 0) && (N - k - *(int*)(&n[k + 8]) > 12 + x)) {
            *(int*)(&n[k + *(int*)(&n[k + 8])]) = 0;
            *(int*)(&n[k + *(int*)(&n[k + 8]) + 4]) = k;
            *(int*)(&n[k + *(int*)(&n[k + 8]) + 8]) = x + 12;
            *(int*)(&n[k]) = k + *(int*)(&n[k + 8]);
            printf("%d\n", k + *(int*)(&n[k + 8]) + 12);
            return 0;
        }

        if (*(int*)(&n[k]) - *(int*)(&n[k + 8]) - k - 12 - x >= 0) {
            *(int*)(&n[k + *(int*)(&n[k + 8])]) = *(int*)(&n[k]);
            *(int*)(&n[k + *(int*)(&n[k + 8]) + 4]) = k;
            *(int*)(&n[k + *(int*)(&n[k + 8]) + 8]) = x + 12;
            *(int*)(&n[*(int*)(&n[k]) + 4]) = k + *(int*)(&n[k + 8]);
            *(int*)(&n[k]) = k + *(int*)(&n[k + 8]);
            printf("%d\n", k + *(int*)(&n[k + 8]) + 12);
            return 0;
        }

        k = *(int*)(&n[k]);
    }

    printf("0\n");
    return 0;
}
void FREE(int pozition)
{
    *(int*)(&n[*(int*)(&n[pozition - 8])]) = *(int*)(&n[pozition - 12]);

    if (*(int*)(&n[pozition - 12]) != 0) {
        *(int*)(&n[*(int*)(&n[pozition - 12]) + 4]) = *(int*)(&n[pozition - 8]);
    }
}

void FILL(int pozition, int nr, int val)
{
    if (nr) {
        do {
            n[pozition] = val;
            pozition++;
            nr--;
        } while (nr);
    }
}

void SHOW(char* INFO)
{
    int number1, number2, number3;
    number1 = number2 = number3 = 0;
    int aux1, aux2, aux3, aux4, aux5, aux6;
    aux1 = aux2 = aux3 = aux4 = aux5 = aux6 = 0;
    int save1, save2;
    save1 = save2 = 0;
    int k = 0;

    if (strchr(INFO, 'E') != 0) {
        if (*(int*)(&n[0]) == 0) {
            number1 = 1;
            number2 = N - 4;
        } else {
            if ((*(int*)(&n[0]) - 4) != 0) {
                ++number1;
                number2 = *(int*)(&n[0]) - 4;
            }

            aux1 = *(int*)(&n[*(int*)(&n[0]) + 8]);
            aux2 = *(int*)(&n[*(int*)(&n[0]) + 4]);
            aux3 = *(int*)(&n[*(int*)(&n[0])]);
            aux4 = *(int*)(&n[aux3]);
            aux5 = *(int*)(&n[aux3 + 4]);
            aux6 = *(int*)(&n[aux3 + 8]);
            while (1) {
                if ((aux3 - aux5 - aux1) != 0 && aux3 != 0) {
                    ++number1;
                    number2 = number2 + aux3 - aux5 - aux1;
                }
                if (aux3 == 0) {
                    if ((N - *(int*)(&n[aux2]) - aux1) != 0) {
                        ++number1;
                        number2 = number2 + N - *(int*)(&n[aux2]) - aux1;
                    }
                    break;
                }
                save1 = aux3;
                save2 = aux4;

                aux1 = *(int*)(&n[save1 + 8]);
                aux2 = *(int*)(&n[save1 + 4]);
                aux3 = *(int*)(&n[save1]);
                aux4 = *(int*)(&n[save2]);
                aux5 = *(int*)(&n[save2 + 4]);
                aux6 = *(int*)(&n[save2 + 8]);
            }
        }
        if (strchr(INFO, 'F') != 0)
            printf("%d blocks (%d bytes) free\n", number1, number2);
    }

    if (strchr(INFO, 'G') != 0) {
        if (count != 0)
            number3 = N - number2 - (4 + 12 * count);
        else
            number3 = 0;

        printf("%d blocks (%d bytes) used\n", count, number3);
        printf("%d%% efficiency\n", (int)((float)number3 / (number3 + count * 12 + 4) * 100));
        printf("%d%% fragmentation\n", (int)((float)(number1 - 1) / count * 100));
    }

    if (strchr(INFO, 'T') != 0) {
        if (*(int*)(&n[k]) == 0) {
            printf("OCCUPIED 4 bytes\n");
            printf("FREE %d bytes\n", N - 4);
            return;
        }
        if (*(int*)(&n[k]) != 0) {
            printf("OCCUPIED 4 bytes\n");
            if (*(int*)(&n[k]) - 4 > 0)
                printf("FREE %d bytes\n", *(int*)(&n[k]) - 4);
        }

        k = *(int*)(&n[k]);

        do {
            if (*(int*)(&n[k]) == 0) {
                printf("OCCUPIED %d bytes\n", *(int*)(&n[k + 8]));
                printf("FREE %d bytes\n", N - k - *(int*)(&n[k + 8]));
                return;
            }
            if (*(int*)(&n[k]) != 0) {
                printf("OCCUPIED %d bytes\n", *(int*)(&n[k + 8]));
                if (*(int*)(&n[k]) - k - *(int*)(&n[k + 8]) > 0)
                    printf("FREE %d bytes\n", *(int*)(&n[k]) - k - *(int*)(&n[k + 8]));
            }

            k = *(int*)(&n[k]);

        } while (k != 0);
    }
}

int main()
{
    char array[20];
    char* segment[20];
    int size, pozition, val;
    //interpretarea comenzilor citite
    while (true) {
        fgets(array, 20, stdin);
        segment[0] = strtok(array, " \0\n");

        //interpretare pt comanda INITIALIZE
        if (strstr(segment[0], "INITIALIZE")) {
            segment[1] = strtok(NULL, " ");
            N = atoi(segment[1]);
            INITIALIZE();
        }

        if (strstr(segment[0], "FINAL")) {
            FINALIZE();
            break;
        }

        if (strstr(segment[0], "DUMP")) {
            DUMP();
        }

        if (strstr(segment[0], "ALLOC")) {
            segment[1] = strtok(NULL, " ");
            size = atoi(segment[1]);
            ALLOC(size);
            if (size != 0)
                count++;
        }

        if (strstr(segment[0], "FREE")) {
            segment[1] = strtok(NULL, " ");
            pozition = atoi(segment[1]);
            FREE(pozition);
            count--;
        }

        if (strstr(segment[0], "FILL")) {
            segment[1] = strtok(NULL, " ");
            pozition = atoi(segment[1]);
            segment[1] = strtok(NULL, " ");
            size = atoi(segment[1]);
            segment[1] = strtok(NULL, " ");
            val = atoi(segment[1]);
            FILL(pozition, size, val);
        }

        if (strstr(segment[0], "SHOW")) {
            segment[1] = strtok(NULL, " ");
            SHOW(segment[1]);
        }
    }

    return 0;
}
