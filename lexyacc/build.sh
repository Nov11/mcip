#!/usr/bin/env bash

bison -d name.y
flex name.lex
gcc  name.tab.h name.tab.c lex.yy.c