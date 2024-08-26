#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 256

int main() {
    int *i = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int tuberia_em_re[2];
    int tuberia_re_em[2];
    int pid;
    char mensaje[MAX];

    if(pipe(tuberia_em_re) == -1 || pipe(tuberia_re_em) == -1) {
        perror("pipe");
        exit(-1);
    }

    /* Creación del proceso hijo */
    if((pid = fork()) == -1) {
        perror("fork");
        exit(-1);
    } else if(pid == 0) {
        /* Código del proceso hijo (receptor) */
        close(tuberia_em_re[1]);
        close(tuberia_re_em[0]);

        while(read(tuberia_em_re[0], mensaje, MAX) > 0 && strcmp(mensaje, "FIN\n") != 0) {
            printf("Proceso receptor. Mensaje: %s\n", mensaje);
            (*i)--;
            printf("Hijo con i= %d\n", (*i));

            sleep(1); // Pausa de 1 segundo en el hijo

            strcpy(mensaje, "FALSO");
            write(tuberia_re_em[1], mensaje, strlen(mensaje) + 1);
        }
        close(tuberia_em_re[0]);
        close(tuberia_re_em[1]);
        exit(0);
    } else {
        /* Código del proceso padre (emisor) */
        close(tuberia_em_re[0]);
        close(tuberia_re_em[1]);

        int j = 3;
        int flag = 1;
        while(1) {
            printf("Proceso emisor. Mensaje: ");
            fflush(stdout);

            if (j < 100) {
                sprintf(mensaje, "%d\n", j);
            } else {
                sprintf(mensaje, "FIN\n");
                flag = 0;
            }
            j++;
            (*i) += 3;
            printf("El padre sumó 3 y por tanto i= %d\n", (*i));

            sleep(1); // Pausa de 1 segundo en el padre

            if(write(tuberia_em_re[1], mensaje, strlen(mensaje) + 1) <= 0) break;
            if(!flag) break;

            /* Esperar mensaje del receptor */
            do {
                int r = read(tuberia_re_em[0], mensaje, MAX);
                if(r <= 0) flag = 0;
            } while(strcmp(mensaje, "FALSO") != 0 && flag);
        }
        close(tuberia_em_re[1]);
        close(tuberia_re_em[0]);
        exit(0);
    }

    return 0;
}
