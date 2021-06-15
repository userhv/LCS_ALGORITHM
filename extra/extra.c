#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300

/* Esse algoritmo utiliza Longest Common Subsequence (LCS) para obter um novo código a partir de linhas diferentes e iguais
  de dois códigos distintos */

/* Essa função retorna o maior valor para a matriz numerica 
  caso não haja linha em comum na sequencia anterior */
struct itens
{
  int aux_ln1, aux_ln2, index;
};
struct itens ln;

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
  for (int aux1 = 0; aux1 < num_ln1; aux1++)
  {
    mat_aloc[aux1] = (int *)calloc(num_ln2, sizeof(int));
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
  for (int aux2 = 0; aux2 < tam_char; aux2++)
  {
    free(free_char[aux2]);
  }
  free(free_char);
}

/* A função FREE_ALOC_INT vai liberar todo espaço armazenado pela matriz numerica
  que é usada para atribuir a maior sequencia em comum, recebendo como parametros 
  a matriz numerica e sua quantidade de linhas */

void free_aloc_int(int **free_int, int tam_int)
{
  for (int aux3 = 0; aux3 < tam_int; aux3++)
  {
    free(free_int[aux3]);
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
    fprintf(stderr,"!!!!ERROR!!!!\n");
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
    fprintf(stderr,"!!!!ERROR!!!!\n");
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

/* Essa função NÃO É UM LCS legitmo, ele vai coletar todas as linhas diferentes e iguais seguindo o padrão LCS
  e organizar em um novo algoritmo respeitando a ordem LCS porém dando a opção de utilizar a linha de comando da 
  primeira ou da segunda função passada no parâmetro */
void newLcsFormat(int **mat_int, int ln_1, int ln_2, char **arc_1, char **arc_2, int aux7, char **lcs, char **lcsDif_1, char **lcsDif_2)
{
  int index = aux7;
  int i = ln_1;
  int j = ln_2;
  int aux8;
  char stAuxiliar[1][4] = {"vg"};

  for (int i = 0; i < ln_1; i++)
  {
    lcsDif_1[i] = (char *)calloc(3, sizeof(char));
    strcpy(lcsDif_1[i], stAuxiliar[0]);
    lcsDif_2[i] = (char *)calloc(3, sizeof(char));
    strcpy(lcsDif_2[i], stAuxiliar[0]);
  }

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

      aux8 = strlen(arc_1[i - 1]);
      lcsDif_1[i - 1] = (char *)calloc(aux8 + 1, sizeof(char));
      strcpy(lcsDif_1[i - 1], arc_1[i - 1]);
      i--;
    }
    else
    {
      aux8 = strlen(arc_2[j - 1]);
      lcsDif_2[i - 1] = (char *)calloc(aux8 + 1, sizeof(char));
      strcpy(lcsDif_2[i - 1], arc_2[j - 1]);
      j--;
    }
  }
}

//--------------- FUNÇÃO PRINCIPAL -------------------//

int main(int argc, char *argv[])
{
  char **string1, **string2, **matriz_char, **lcsDif_1, **lcsDif_2;
  int **matriz_int;
  ln.aux_ln1 = 0, ln.aux_ln2 = 0, ln.index = 0; //declaração do struct
  int ln_1, ln_2;

  FILE *arq1;
  FILE *arq2;
  arq1 = fopen(argv[1], "r");
  arq2 = fopen(argv[2], "r");

  cont_ln(arq1, &ln_1);
  cont_ln(arq2, &ln_2);

  string1 = (char **)calloc(ln_1, sizeof(char *));
  open_archive(arq1, &ln.aux_ln1, string1);
  string2 = (char **)calloc(ln_2, sizeof(char *));
  open_archive(arq2, &ln.aux_ln2, string2);
  matriz_int = lcs_number(string1, string2, ln.aux_ln1, ln.aux_ln2, &ln.index);
  matriz_char = (char **)calloc(ln.aux_ln1, sizeof(char *));
  lcsDif_1 = (char **)calloc(ln.aux_ln1 + 1, sizeof(char *));
  lcsDif_2 = (char **)calloc(ln.aux_ln1 + 1, sizeof(char *));
  newLcsFormat(matriz_int, ln.aux_ln1, ln.aux_ln2, string1, string2, ln.index, matriz_char, lcsDif_1, lcsDif_2);

  int tamanhoDif1 = 0, tamanhoDif2 = 0;

  fprintf(stderr, "%s", matriz_char[0]);
  fprintf(stderr, "%s", matriz_char[1]);

  for (int i = 2; i < ln.aux_ln1; i++)
  {
    if (i < ln.index)
    {
      fprintf(stderr, " %s", matriz_char[i]);
    }

    tamanhoDif1 = strlen(lcsDif_1[i]);
    tamanhoDif2 = strlen(lcsDif_2[i]);

    if (tamanhoDif1 != 2 && tamanhoDif2 != 2)
    {
      if (strcmp(lcsDif_1[i], lcsDif_2[i]) == 0)
      {
        fprintf(stderr, "if(func_id == 0){\n\t%s\n}else{\n\t%s}\n", lcsDif_1[i], lcsDif_2[i]);
      }
    }
    if (tamanhoDif1 != 2)
    {
      fprintf(stderr, "if(func_id == 0){\n\t%s}\n", lcsDif_1[i]);
    }
    if (tamanhoDif2 != 2)
    {
      fprintf(stderr, "if(func_id == 1){\n\t%s}\n", lcsDif_2[i]);
    }
  }
  fprintf(stderr, "%s", matriz_char[ln.index - 2]);
  fprintf(stderr, "%s", matriz_char[ln.index - 1]);

  fclose(arq1);
  fclose(arq2);

  free_aloc_char(string1, ln.aux_ln1);
  free_aloc_char(string2, ln.aux_ln2);
  free_aloc_int(matriz_int, ln.aux_ln1);
  free_aloc_char(lcsDif_1, ln.aux_ln1);
  free_aloc_char(lcsDif_2, ln.aux_ln1);
  free_aloc_char(matriz_char, ln.aux_ln1);

  return 0;
}