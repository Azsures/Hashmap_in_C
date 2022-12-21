#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int mat = 100022600;

typedef struct aluno{
  char Nome[21];
  int matricula;
  int nota;
  struct aluno *prox;
}aluno;

typedef struct NovaTabela{
  aluno *table[701];
  int fator;
}Tabela;

void inicializa_tab(Tabela *New){
  for(int i = 0; i < 702; i++)
   New->table[i] = NULL;
  New->fator = 0;
}

int hash1(char *string){
  int temp = 0;
  for (int i = 0; string[i] != '\0'; i++)
   temp += (int) string[i];
  temp = temp%701;
  return temp;
}

int hash2(char *string){
  int pos = 0, i;
  for(i = 0; string[i] != '\0'; i++)
      pos += (int) string[i]*i;
  return pos;
}

int hashduplo(char *string){
  int cod;
  cod = (hash1(string) * (hash2(string)/2));
  return cod%701;
}

int Insert_aux(Tabela **tabble, aluno estudante){
  int pos;
  aluno *temp, *perc;
  temp = (aluno *) malloc(sizeof(aluno));
  if(!temp) return -1;
  
  for(int i = 0; estudante.Nome[i] != '\0'; i++)
    temp->Nome[i] = estudante.Nome[i];
  temp->matricula = estudante.matricula;
  temp->nota = estudante.nota;
  temp->prox = NULL;
  pos = hashduplo(temp->Nome);
  if((*tabble)->table[pos] == NULL)
  {
    (*tabble)->table[pos] = temp;
    (*tabble)->fator++;
    return 1;
  }
  else
  {
    perc = (*tabble)->table[pos]->prox;
    if(perc == NULL)
    {
      (*tabble)->table[pos]->prox = temp;
      (*tabble)->fator++;
      return 1;
    }
    else
    {
      while(perc->prox != NULL)
        perc = perc->prox;
      perc->prox = temp;
      (*tabble)->fator++;
      return 1;
    }
  }
}

void aloca_aluno(char *nome, int mat, int nota, Tabela *Table){
  aluno temp;
  temp.nota = nota;
  for(int i = 0; i < 15; i++)
   temp.Nome[i] = nome[i];
  temp.matricula = mat;
  Insert_aux(&Table, temp);
}

int buscape(char *chave){
  int pos = hashduplo(chave);
  return pos;
}

int main() {
  Tabela NewTable;
  int opc = 0, pos;
  char string[25];
  inicializa_tab(&NewTable);
  while(opc != 3)
  {
    printf("=========================\n");
    printf("=========================\n");
    printf("Selecione uma opçao:\n");
    printf("1- Cadastrar aluno.\n");
    printf("2 - Verificar matrícula\n");
    printf("3 - Sair\n");
    printf("=========================\n");
    printf("=========================\n");
    scanf("%d", &opc);
    switch(opc)
    {
      case 1:
        printf("Digite o nome:\n");
        scanf("%s", string);
        aloca_aluno(string, mat++, 90, &NewTable);
        break;
      case 2:
        printf("Digite o nome:\n");
        scanf("%s", string);
        pos = buscape(string);
        if(NewTable.table[pos] == NULL){
          printf("Aluno não cadastrado\n");
          getchar();
          getchar();
          break;
        }
        getchar();
        printf("\n\nMatricula de %s: %d\n\n",NewTable.table[pos]->Nome, NewTable.table[pos]->matricula);
        printf("posicao na tabela: %d", pos);
        getchar();
        break;
      case 3:
        break;
    }
    if(opc == 0){
      printf("Use um número (1-3) para selecionar uma opção\n");
      break;
    }
    printf("\e[1;1H\e[2J");
  }
  printf("\n"); 
  printf("fator de carga: %d\n", NewTable.fator);
  return 0;
}
