#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int next_int(char ** s) {
  const char * q = *s;
  char * end = q+strlen(q);
  while(!isdigit(q[0]) && q < end)
    q++;
  const char * p = q;
  while(isdigit(p[0]))
    p++;
  char tmp[p-q+1];
  strncpy(tmp, q, p-q);
  tmp[p-q] = '\0';
  *s = p;
  return atoi(tmp);
}

int eval(char * q) {
  int val=0, len=strlen(q);
  char * t = q;
  while(1) {
    if(isdigit(t[0])) {
      val = next_int(&t);
    } else if (t[0]=='+') {
      val += next_int(&t);
    } else if (t[0]=='-') {
      val -= next_int(&t);
    } else if (t[0]=='*') {
      val *= next_int(&t);
    } else if (t[0]=='/') {
      val /= next_int(&t);
    } else if (t[0]=='\0') {
      break;
    } else {
      ++t;
    }
  }
  return val;
}


char * solve(char * q) {

  char c = 0;
  int i = 0, j = 0, len = strlen(q);
  for (i=0; i<len; ++i) {
    if (isalpha(q[i])) {
      c = q[i];
      break;
    }
  }
  if (c == 0) {
    const char * end = q+len;
    const char * eq = strstr(q, "==");
    char op1[eq-q+1], op2[end-eq-1];
    strncpy(op1, q, eq-q);
    strncpy(op2, eq+2, end-eq-2);
    op1[eq-q] = '\0';
    op2[end-eq-2] = '\0';

    int eval1 = eval(op1), eval2 = eval(op2);
    if(eval1 == eval2) { // solved!
      char * r = (char*)malloc(len*sizeof(char));
      strcpy(r, q);
      return r;
    } else {
      return 0;
    }
  } else {
    char dset[10] = {0,0,0,0,0,0,0,0,0,0};
    for (i=0; i<len; ++i)
      if (isdigit(q[i]))
        dset[q[i]-'0'] = 1;
    for (i=0; i<10; ++i) {
      if (dset[i] == 0) {
        char * n = (char*)malloc(len*sizeof(char));
        for (j=0; j<len; ++j)
          n[j] = (q[j] == c) ? i + '0' : q[j];
        char * r = solve(n);
        free(n);
        if (r) return r;
      }
    }
  }
  return 0;
}

int main() {
  char * query = "SEND + MORE == MONEY";
  char * result = solve(query);
  printf("%s\n",query);
  if(result) puts(result);
  else puts("No solution found.");
  return 0;

}
