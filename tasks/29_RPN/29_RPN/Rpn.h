#pragma once
#include <iostream> 
#include <cmath> 
#include <cstdlib> 
#include<cstring>
#include<stack>
using namespace std;

bool is_op(char c);
int priority(char op);
void rpn(double *st, int & top, char op);
void infix2postfix(char infix[], char postfix[], int size);
void calc();