//Ler uma matriz de 5x5 inteiros e imprimir o menor e o maior valor.

#include <stdio.h>

int main(){
int A[5][5],i,j;

for(i=0;i<5;i++){
 for(j=0;j<5;j++){
  scanf("%d",&A[i][j]);
 }
}

int maior=A[0][0],menor=A[0][0];

for(i=0;i<5;i++){
 for(j=0;j<5;j++){
  if(A[i][j]>maior)
   maior = A[i][j];
  if(A[i][j]<menor)
   menor = A[i][j];
 }
}

printf("%d %d",menor,maior);
}
