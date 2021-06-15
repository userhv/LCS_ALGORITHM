#ifndef LCS_LIB
#define LCS_LIB

struct itens
{
    int aux_ln1, aux_ln2, index;
};

int max(int, int);
int **aloc_int_lcs(int, int);
void free_aloc_char(char **, int);
void free_aloc_int(int **, int);
void open_archive(FILE *, int *, char **);
void cont_ln(FILE *, int *);
int **lcs_number(char **, char **, int, int, int *);
char **lcs_format(int **, int, int, char **, char **, int);
#endif