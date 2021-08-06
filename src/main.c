#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define one_code_size 2000
#define stack_size 10
#define list_size 500

#define car(list) strcpy(list, car_iter(list))
#define cdr(list) strcpy(list, cdr_iter(list))

char nil[] = "nil";

int S[stack_size];
char unsigned Sp=0;
char E[list_size];
char C[one_code_size];
char D[list_size];


char *cdr_iter(char *list)
{
  unsigned char depth=0;
  bool flag=0;
  if(index(list, '(') == NULL){ return list; }else{ list = index(list, '('); }
  while(list[0] != '\0'){
    //printf("depth:%d flag:%d %c\n", depth, flag, list[0]);
    switch (list[0]){
    case '(':
      if(depth==1 && flag==1){ (list-1)[0]='('; return list=list-1; }
      depth+=1;
      break;
    case ')': depth-=1; break;
    case ' ':
      if(depth==1 && flag==1){ (list-1)[0] = '('; return list=list-1; }
      break;
    default: if(list[0] != ' ' && list[0] != '(' && depth>=1){ flag=1; } break;
    }
    list+=1;
  }
  return list;
}

char *car_iter(char *list)
{
  unsigned char depth=0;
  unsigned int i=0;
  bool flag=0;
  if(index(list, '(') == NULL){ return list; }else{ list = index(list, '('); }
  while(list[i] != '\0'){
    //printf("depth:%d flag:%d %c\n", depth, flag, list[i]);
    switch (list[i]){
    case '(':
      if(depth==1 && flag==1){ list[0] = ' '; /* list[i-1]=')'; */ list[i] = '\0'; return list;}
      depth+=1;
      break;
    case ')': depth-=1; break;
    case ' ':
      if(depth==1 && flag==1){ list[0] = ' '; /* list[i-1] = ')'; */ list[i] = '\0'; return list;}
      break;
    default: if(list[i] != ' ' && list[i] != '(' && depth>=1){ flag=1; } break;
    }
    i+=1;
  }
  list[0] = ' '; *index(list, ')')=' '; return list;
}

char *cons(char *cons_list, char *car_list, char *cdr_list)
{
  char copy_list[list_size];
  strcpy(copy_list, cdr_list);
  strcpy(cons_list, "(");
  strcat(cons_list, car_list);
  strcat(cons_list, car(copy_list));
  strcat(cons_list, ")");
  return cons_list;
}

char *list(char *list)
{
  strcpy(1+list, list);
  *list = '(';
  strcat(list, ")");
  return list;
}

char *caar(char *list)
{
  car(list);
  car(list);
  return list;
}

char *cadr(char *list)
{
  cdr(list);
  car(list);
  return list;
}

char *cddr(char *list)
{
  return cdr(cdr(list));
}

int eval(char *list)
{

  char op[list_size];
  char val[list_size];
  strcpy(op, list);
  strcpy(val, list);
  car(op);
  cadr(val);

  strcpy(op, strtok(op, " "));
  strcpy(val, strtok(val, " "));

  printf("op: %s val: %s Sp: %d\n", op, val, Sp);

  if(!strcmp(op, "push"))
    {
      S[++Sp]+=atoi(val);
    }
  else if(!strcmp(op, "pop"))
    {
      for(unsigned char i=atoi(val); i>0; i--)
	printf("%d\n", S[Sp--]);
    }
  else if(!strcmp(op, "exch"))
    {
      S[Sp] ^= S[atoi(val)];
      S[atoi(val)] ^= S[Sp];
      S[Sp] ^= S[atoi(val)];
    }
  else if(!strcmp(op, "match"))
    {
     }
  else if(!strcmp(op, "add"))
    {
      S[Sp] = S[Sp] + S[atoi(val)];
    }
  else if(!strcmp(op, "sub"))
    {
    }
  else if(!strcmp(op, "mul"))
    {
    }
  else if(!strcmp(op, "dev"))
    {
    }
  else if(!strcmp(op, "sort"))
    {
    }
  else if(!strcmp(op, "elt"))
    {
    }
  else if(!strcmp(op, "convert"))
    {
    }
  else if(!strcmp(op, "call-with-current-continuation"))
    {
    }
  else
    {
      printf("Error");
      return -1;
    }
  
  return 0;
}

int main(void)
{
  eval("(push 10)");
  eval("(push 5)");
  eval("(exch 1)");
  eval("(add 1)");
  eval("(pop 1)");
  return 0;
}
