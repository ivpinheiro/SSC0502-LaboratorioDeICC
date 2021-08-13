//Criar uma função que receba um número real (E) e um número de iterações (n) e retorne a raiz quadrada (R) do número real através de Newton:
//R1 = E/2
//Rn+1 = (Rn + (E/Rn))/2
//Ex: para E=16 e n=4 -> R=4,0012

#include<stdio.h>

int main(){
float e,n,r;
scanf("%f %f",&e,&n);
r=e/2;
for(int a=1;a<n;a++){
  r=((r+(e/r))/2);
}
printf("%f",r);
}
