#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

#define MAX 300

/* Essa função retorna o maior valor para a matriz numerica 
  caso não haja linha em comum na sequencia anterior */

int max(int a, int b)
{
  if (a > b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

/* Aloca dinamicamente o tamanho da matriz numerica de LCS a 
  partir da sequencia em comum entre os arquivos analisados,
  recebendo como parametros o número de linhas de cada arquivo.*/

int **aloc_int_lcs(int num_ln1, int num_ln2)
{
  int **mat_aloc;
  mat_aloc = (int **)calloc(num_ln1, sizeof(int *));
  for (int i = 0; i < num_ln1; i++)
  {
    mat_aloc[i] = (int *)calloc(num_ln2, sizeof(int));
  }
  if (mat_aloc == NULL)
  {
    fprintf(stderr,"Houve um erro\n");
  }

  return mat_aloc;
}

/* A função FREE_ALOC_CHAR vai liberar todo espaço armazenado pela matriz gerada
  a partir do LCS, recebendo como parametros a matriz gerada e sua 
  quantidade de linhas */

void free_aloc_char(char **free_char, int tam_char)
{
  for (int i = 0; i < tam_char; i++)
  {
    free(free_char[i]);
  }
  free(free_char);
}

/* A função FREE_ALOC_INT vai liberar todo espaço armazenado pela matriz numerica
  que é usada para atribuir a maior sequencia em comum, recebendo como parametros 
  a matriz numerica e sua quantidade de linhas */

void free_aloc_int(int **free_int, int tam_int)
{
  for (int i = 0; i < tam_int; i++)
  {
    free(free_int[i]);
  }
  free(free_int);
}

/* Essa função recebe como parametros o arquivo analisado, numero de linhas já computado
  e uma variavel CHAR** ARCHIVE na qual será copiada cada linha do arquivo para uma 
  posição dessa matriz */

void open_archive(FILE *arc, int *size_arc, char **archive)
{
  if (arc == NULL)
  {
    fprintf(stderr, "!!!!ERROR!!!!\n");
    exit(EXIT_FAILURE);
  }
  setbuf(stdin, NULL);
  char aux_arc[MAX];
  int aux4;
  int ln = 0;
  while (fgets(aux_arc, MAX, arc))
  {
    aux4 = strlen(aux_arc);
    archive[ln] = (char *)calloc(aux4 + 1, sizeof(char));
    strcpy(archive[ln], aux_arc);
    ln++;
  }
  *size_arc = ln;
}

/* Recebe como parametros uma variavel auxiliar e o arquivo, e tem a função
  de computar o número de linhas de cada arquivo para que ele possa ser alocado
  dinamicamente e passado para outras funções como a OPEN_ARCHIVE */

void cont_ln(FILE *arquivo, int *aux5)
{
  int ln = 0;
  if (arquivo == NULL)
  {
    fprintf(stderr, "!!!!ERROR!!!!\n");
    exit(EXIT_FAILURE);
  }
  char ln_arc[MAX];

  while (fgets(ln_arc, MAX, arquivo))
  {
    ln++;
  }
  rewind(arquivo);
  *aux5 = ln;
}

/* Função que gera a matriz numerica base para criar a maior subsequencia em comum,
  ela recebe de parametros os arquivos já formatados em uma posição do vetor em ARC_1 e ARC_2
  além do numero de linhas de cada arquivo e uma variavel auxiliar que vai receber o valor final
  da quantidade de subsequencias em comum dos arquivos. */

int **lcs_number(char **arc_1, char **arc_2, int tam_ln_1, int tam_ln_2, int *ind_final)
{
  int **mat_int = aloc_int_lcs(tam_ln_1 + 1, tam_ln_2 + 1);
  for (int i = 0; i < tam_ln_1 + 1; i++)
  {
    for (int j = 0; j < tam_ln_2 + 1; j++)
    {
      if (i == 0 || j == 0)
      {
        mat_int[i][j] = 0;
      }
      else if (strcmp(arc_1[i - 1], arc_2[j - 1]) == 0)
      {
        mat_int[i][j] = mat_int[i - 1][j - 1] + 1;
      }
      else
      {
        mat_int[i][j] = max(mat_int[i - 1][j], mat_int[i][j - 1]);
      }
    }
  }
  *ind_final = mat_int[tam_ln_1][tam_ln_2];

  return mat_int;
}

/* A partir da matriz numerica, utilizamos a LCS_FORMAT para formatar todas as linhas em comum
  a partir do valor de cada posição definido na matriz numerica, ao final disso tem-se a matriz
  de lcs onde cada linha dessa matriz é uma linha de código comum em ambos os arquivos em sua 
  respectiva posição de modo que não comprometa o funcionamento de modo que respeite a ordem de 
  precedência da sua posição */

char **lcs_format(int **mat_int, int ln_1, int ln_2, char **arc_1, char **arc_2, int aux7)
{
  char **lcs;
  int i = ln_1, j = ln_2, index = aux7, aux8;

  lcs = (char **)calloc(ln_1, sizeof(char *));
  while (i > 0 && j > 0)
  {
    if (strcmp(arc_1[i - 1], arc_2[j - 1]) == 0)
    {
      aux8 = strlen(arc_1[i - 1]);
      lcs[index - 1] = (char *)calloc(aux8 + 1, sizeof(char));
      strcpy(lcs[index - 1], arc_1[i - 1]);
      i--;
      j--;
      index--;
    }
    else if (mat_int[i - 1][j] > mat_int[i][j - 1])
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