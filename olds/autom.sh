#!/bin/bash
#Oriens
#Shell commands to create .c file automatically

#create .c file
touch  new.c

#edit the file
nexl='\\n'
echo -e "#include <stdio.h>
#define INF Ox3f3f3f3f
int main(){
\tprintf(\"Hello$nexl\");
\treturn 0;
}"> new.c

#open the file with vim
vim new.c
