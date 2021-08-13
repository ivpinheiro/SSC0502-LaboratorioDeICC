//Calcule o máximo divisor comum (m.d.c.) e o mínimo múltiplo comum (m.m.c.) de 3 números inteiros fornecidos pelo usuário.

Formato da saída: printf("%d %d", mmc, mdc);
#include<stdio.h>

int MDC(int a,int b,int c){
int d=2,e=1;
while(a>d||b>d||c>d){
 while(a%d==0&&b%d==0&&c%d==0){
  e=e*d;
  a=a/d;
  b=b/d;
  c=c/d;
 }
 d=d+1;
}
return(e);
}

int MMC(int a,int b,int c){
int d=2,e=1;
while(a>1||b>1||c>1){
 while(a%d==0||b%d==0||c%d==0){
  e=e*d;
  if(a%d==0)
  a=a/d;
  if(b%d==0)
  b=b/d;
  if(c%d==0)
  c=c/d;
 }
 d=d+1;
}
return(e);
}

int main(void){
int a,b,c,d,e;
scanf("%d",&a);
scanf("%d",&b);
scanf("%d",&c);
d=MDC(a,b,c);
e=MMC(a,b,c);
printf("%d %d",e,d);
return 0;
}
