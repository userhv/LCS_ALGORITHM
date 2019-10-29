#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char X[MAX],Y[MAX];
int i,j,m,n,c[MAX][MAX],b[MAX][MAX];
int LCSlenght(){
	m = strlen(X);
	n = strlen(Y);

	for(i=1; i<=m; i++){ 
		c[i][0] = 0;
	}
	for(j=0; j<=n; j++){ 
		c[0][j] = 0;
	}
	for(i=1; i<=m; i++)

	for(j=1; j<=n; j++){
		if(X[i-1] == Y[j-1]){
			c[i][j] = c[i-1][j-1]+1;
			b[i][j] = 1;
      	}
		else if(c[i-1][j] >= c[i][j-1]){
			c[i][j] = c[i-1][j];
			b[i][j] = 2;
      	}
      	else{
    		c[i][j] = c[i][j-1];
    		b[i][j] = 3;
      	}
    }
  	return c[m][n];  	
}
void showLCS(int i, int j){
	
	if(i==0 || j==0)
   	return;
  	
  	if(b[i][j]==1){
    	showLCS(i-1,j-1);
    	printf("%c",X[i-1]);
  	}
  	else if(b[i][j]==2){
    	showLCS(i-1,j);
  	}
  	else{
    	showLCS(i,j-1);
  	}
}

int main()
{
  int num,i;
  printf("Digite quantas comparações deseja fazer (0 pra terminar): ");
  while(scanf("%d",&num)==1 && num>0)
  {
    for(i=0;i<num;i++)
    {
      printf("\nDigite a string 1: ");
      scanf("%s",X);
      printf("\nDigite a string 2: ");
      scanf("%s",Y);
      printf("Tamanho da LCS: %d ", LCSlenght());
      printf("\nResutado da LCS: ");
      showLCS(m,n);
      printf("\n");
    }
    printf("\nDigite quantas comparações deseja fazer (0 pra terminar): ");
  }
  return 0;
}