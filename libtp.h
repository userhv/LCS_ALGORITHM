#ifndef LCS_LIB
#define LCS_LIB
    int max(int , int ); 
    int** aloc_int_lcs(int , int );
    void free_aloc(char**, int );
    void free_aloc_int(int**, int );
    void abrirarquivo(FILE*, int*, char**);
    void contlinha(FILE*, int*);
    int** LCS(char**, char**, int, int, int*);
    char** lcsformatado(int**, int, int , char**, char**,int);
#endif