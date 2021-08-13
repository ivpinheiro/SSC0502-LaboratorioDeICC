#include <stdio.h>
#include <string.h>

int encontrapalavra(char A[1000], char B[1000]);

int main(){
    FILE *arq;
    int contador=0, aux=0;
    char learq[1000], lep[1000], diferenciacao[1000];
    setbuf(stdin, 0);
    fgets(lep, 999, stdin);
    lep[strcspn(lep, "\n")] = 0;
    if((arq=fopen("arquivo2.txt", "r+"))==NULL){
        printf("\nErro ao abrir o arquivo.\n");
    }
    fseek(arq, 0, SEEK_SET);
    while (1){
        fgets(learq, 999, arq);
        if(feof(arq)){
           break;
        }
        learq[strcspn(learq, "\n")] = 0;
        strcpy(diferenciacao, " ");
        strcat(diferenciacao, learq);
        strcat(diferenciacao, " &%");
        aux = encontrapalavra(diferenciacao, lep);
        contador = contador + aux;
    }
    printf("%i", contador);
    fclose(arq);
}

int encontrapalavra(char A[1000], char B[1000]){
    int x=0, y=0, tam=0, aux=0, contador=0;
    tam=strlen(B);
    while(A[x]!='&' && A[x+1]!='%'){
        while(A[x]==B[y]){
            aux++;
            if(aux==tam){
                contador++;
                break;
            }
            y++;
            x++;
        }
        aux=0;
        y=0;
        x++;
    }
    return contador;
    return 0;
}
