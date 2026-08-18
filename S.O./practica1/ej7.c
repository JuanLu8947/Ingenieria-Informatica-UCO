#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void sig_alarm(){
    printf("...RING...\n");
}

unsigned int funcionManejadora(unsigned int seconds){
    alarm(seconds);
    pause();
}

int main(){
    signal(SIGALRM, sig_alarm);
    printf("La alarma sonará dentro de 5 segundos\n");
    funcionManejadora(5);
    printf("La alarma sonará dentro de 3 segundos\n");
    funcionManejadora(3);
    printf("La alarma sonará dentro de 1 segundos\n");
    funcionManejadora(1);

    printf("La alarma sonará indefinidamente\n");
    int i=0;
    while(1){
        alarm(1);
        sleep(1);
        i++;
        if(i>=4){
            int pid;
            sleep(1);
            printf("Introduzca el pid del proceso a matar: ");
            scanf("%d", &pid);
            kill(pid, SIGKILL);
            printf("Error en el pid\n");
        }
    }
    exit(EXIT_SUCCESS);
}

//30 tipo test, 10 cada tema