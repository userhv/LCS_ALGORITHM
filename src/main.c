#include <stdio.h>
#include <stdlib.h>

#include "function.h"

/* Esse algoritmo utiliza Longest Common Subsequence (LCS) para obter um novo código a partir
  de dois códigos distintos */


//--------------- FUNÇÃO PRINCIPAL -------------------//

int main(int argc, char *argv[])
{
  char **string1, **string2, **matriz_char;
  int **matriz_int;
  struct itens ln;
  ln.aux_ln1 = 0, ln.aux_ln2 = 0, ln.index = 0;
  int ln_1, ln_2;

  FILE *arq1;
  FILE *arq2;
  arq1 = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");

  cont_ln(arq1, &ln_1);
  cont_ln(arq2, &ln_2);
  string1 = (char **)calloc(ln_1, sizeof(char *));                                          //aloca dinamicamente a quantidade de linhas do primeiro arquivo
  open_archive(arq1, &ln.aux_ln1, string1);                                                 //apos arquivos abertos, coleto novamente numero de linhas e conteudo do mesmo
  string2 = (char **)calloc(ln_2, sizeof(char *));                                          //aloca dinamicamente a quantidade de linhas do segundo arquivo
  open_archive(arq2, &ln.aux_ln2, string2);                                                 //apos arquivos abertos, coleto novamente numero de linhas e conteudo do mesmo
  matriz_int = lcs_number(string1, string2, ln.aux_ln1, ln.aux_ln2, &ln.index);             //cria a matriz numerica de lcs
  matriz_char = lcs_format(matriz_int, ln.aux_ln1, ln.aux_ln2, string1, string2, ln.index); //cria a matriz de char lcs

  for (int i = 0; i < ln.index; i++)
  {
    printf("%s", matriz_char[i]); //apos gerado a matriz de char lcs, imprimimos a resposta
  }

  fclose(arq1);
  fclose(arq2);

  free_aloc_char(string1, ln.aux_ln1);
  free_aloc_char(string2, ln.aux_ln2);
  free_aloc_char(matriz_char,ln.aux_ln1);
  free_aloc_int(matriz_int, ln.aux_ln1+1);

  return 0;
}