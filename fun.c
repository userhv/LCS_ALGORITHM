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