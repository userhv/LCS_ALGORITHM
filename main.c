#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 300
#include "libtp.h"


int max(int a, int b); 
int max(int a, int b) 
{ 
    if (a>b){
        return a;
    }
    else {
        return b;
    }
} 

//--------- ALOCAR O TAMANHO DOS ARQUIVOS-----------//

int** aloc_int_lcs(int i, int j)
  {
    int** L;
    int aux1,aux2;
    L = (int**)calloc(i,sizeof(int*));
        for(int x = 0; x < i; x++)
      {
        L[x] = (int*)calloc(j,sizeof(int));
      }
    if (L == NULL)
      {
        printf("Houve um erro\n");
      }
  
  return L;
}



//--------------------  FREE ----------------------//
void free_aloc(char** aloc_char1, int tam_int1)
  {
    for(int aux3 = 0; aux3 < tam_int1; aux3++)
      {
        free(aloc_char1[aux3]);
      }
    free(aloc_char1);   
  }

void free_aloc_int(int** free_int, int tam_int)
  {
    for(int aux3 = 0; aux3 < tam_int; aux3++)
      {
        free(free_int[aux3]);
      }
    free(free_int);   
  }

//-------------- ABRIR ARQUIVO -------------------//
void abrirarquivo(FILE *arq, int* tamanho, char** arquivo)
  {
    if (arq == NULL)
      {
        printf("!!!!ERROR!!!!\n");
        exit;
      }
    setbuf(stdin, NULL);
    char ln_arc[MAX];
    int aux1;
    int ln = 0;
    while (fgets(ln_arc, MAX, arq))
      {
        aux1 = strlen(ln_arc);
        arquivo[ln] = (char*)calloc(aux1+1,sizeof(char));
        strcpy(arquivo[ln], ln_arc);
        ln++;    
      }
    *tamanho = ln;
 
  }


void contlinha(FILE *arquivo, int* aux1)
  {
    int ln = 0;
       if (arquivo == NULL)
      {
        printf("!!!!ERROR!!!!\n");
        exit;
      } 
        char ln_arc[MAX];
        
        
        while (fgets(ln_arc, MAX, arquivo))
      {
        ln++;    
      }
      rewind(arquivo);
      *aux1 = ln;

  }


//--------------- LCS NUMERICO -------------------//

int** LCS(char** vetor1, char** vetor2, int p, int k, int* ind_final)
  {
    int** L = aloc_int_lcs(p+1,k+1);
    for (int i=0; i< p+1; i++) 
      { 
        for (int j=0; j< k+1; j++) 
          { 
            if (i == 0 || j == 0)
              {
                L[i][j] = 0; 
              }
            else if (strcmp(vetor1[i-1],vetor2[j-1]) == 0)
              { 
                L[i][j] = L[i-1][j-1] + 1; 
              }
            else
              {
                L[i][j] = max(L[i-1][j], L[i][j-1]); 
              }   
            }
        }
        *ind_final = L[p][k];
    return L;
  }


//--------------- LCS FORMATADO -------------------//

  char** lcsformatado(int** L, int p, int k, char** vetor1, char** vetor2,int aux4)
    {
    int index = aux4; 
    char** lcs;
    int i = p; 
    int j = k; 
    int aux;

    lcs = (char**)calloc(p,sizeof(char*));
    while (i > 0 && j > 0)
    { 
      if (strcmp(vetor1[i-1],vetor2[j-1]) == 0)
        { 
          aux = strlen(vetor1[i-1]);
          lcs[index-1] = (char*)calloc(aux+1,sizeof(char));
          strcpy(lcs[index-1],vetor1[i-1]);
          i--; 
          j--; 
          index--;  
        }
      else if (L[i-1][j] > L[i][j-1])
        {
          i--; 
        }
      else
        {
          j--;
        } 
    }
    return lcs;
 }

//--------------- FUNÇÃO PRINCIPAL -------------------//

int main(int argc, char* argv[ ])
  {
    char** string1;
    char** string2;
    char** matriz_char;
    int** matriz_int;
    int aux1,aux2;
    int tamanho1 = 0, tamanho2 = 0, index = 0;
    int arc_1 , arc_2;

    FILE *arq1;
    FILE *arq2;
    arq1 = fopen(argv[1],"r");
    arq2 = fopen(argv[2],"r");
    contlinha(arq1, &arc_1);
    contlinha(arq2, &arc_2);

    string1 = (char**)calloc(arc_1,sizeof(char*));//corrigir pois esta estatico;
    abrirarquivo(arq1, &tamanho1,string1);
    string2 = (char**)calloc(arc_2,sizeof(char*));//corrigir pois esta estatico;
    abrirarquivo(arq2, &tamanho2,string2);
    matriz_int = LCS(string1,string2,tamanho1,tamanho2,&index);
    matriz_char = lcsformatado(matriz_int,tamanho1,tamanho2,string1,string2,index);
    
    for(int i=0; i < index; i++)
      {
        printf("%s",matriz_char[i]);
      }

    fclose(arq1);
    fclose(arq2);

    free_aloc(string1,tamanho1);
    free_aloc(string2,tamanho2);
    free_aloc_int(matriz_int,tamanho1);




  printf("\n");
  fprintf(stderr,"João me da dois pontos.\n");    


    return 0;
  }