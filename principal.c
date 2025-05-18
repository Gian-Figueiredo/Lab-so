#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int n;
    printf("Insira o numero de execucoes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid_t pid; 
        pid = fork();

        if (pid == 0) {
            execl("./helloworld", "helloworld", NULL);
            perror("execl falhou");
            exit(1);
        }
        
        if (pid > 0) {
            printf("Execucao do pai\n");
        }

        if (pid < 0) {
            perror("fork falhou");
        }
    }

    return 0;
}