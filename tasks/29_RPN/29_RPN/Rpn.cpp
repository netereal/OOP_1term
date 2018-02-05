#include "Rpn.h"

const int nmax = 108;

bool is_op(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int priority(char op) {

	if (op == -'-' || op == -'+')
		return 4;
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/' || op == '%')
		return 2;
	return -1;
}

void rpn(double *st, int & top, char op) {
	if (op == 'c') {
		st[top - 1] = cos(st[top - 1]);
		return;
	}
	if (op == 's') {
		st[top - 1] = sin(st[top - 1]);
		return;
	}
	if (op == -'+') {
		st[top - 1];
		return;
	}
	if (op == -'-') {
		st[top - 1] = -st[top - 1];
		return;
	}
	top--;
	int r = st[top];
	int l = st[top - 1];
	switch (op) {
	case '+': st[top - 1] = (l + r); break;
	case '-': st[top - 1] = (l - r); break;
	case '*': st[top - 1] = (l * r); break;
	case '/': st[top - 1] = (l / r); break;
	case '%': st[top - 1] = (l % r); break;
	}
}
int getWeight(char ch) {
	switch (ch) {
	case '/':
	case '*': return 2;
	case '+':
	case '-': return 1;
	default: return 0;
	}
}

void infix2postfix(char infix[], char postfix[], int size) {
	stack<char> s;
	int weight;
	int i = 0;
	int k = 0;
	char ch;
	while (i < size) {
		ch = infix[i];
		if (ch == '(') {
			s.push(ch);
			i++;
			continue;
		}
		if (ch == ')') {
			while (!s.empty() && s.top() != '(') {
				postfix[k++] = s.top();
				s.pop();

			}
			if (!s.empty()) {
				s.pop();
			}
			i++;
			continue;
		}
		weight = getWeight(ch);
		if (weight == 0) {
			postfix[k++] = ch;

		}
		else {
			if (s.empty()) {
				s.push(ch);
			}
			else {
				while (!s.empty() && s.top() != '(' &&
					weight <= getWeight(s.top())) {
					postfix[k++] = s.top();
					s.pop();

				}
				s.push(ch);
			}
		}
		i++;
	}
	while (!s.empty()) {
		postfix[k++] = s.top();
		s.pop();
	}
	postfix[k] = 0; // null terminate the postfix expression 
}


void calc() {
	double st[nmax];
	char op[nmax];
	int tops = 0, topo = 0;

	char inf[nmax];
	char postf[nmax];

	cin.getline(inf, nmax);
	int size = strlen(inf);
	infix2postfix(inf, postf, size);
	cout << "\nInfix Expression : " << inf;
	cout << "\nPostfix Expression : " << postf;
	cout << endl;

	for (int i = 0, len = strlen(inf); i < len; ++i)
		if (!(isdigit(inf[i]) || inf[i] == '(' || inf[i] == ')' || inf[i] == '+' || inf[i] == '-' || (inf[i] == '/' && inf[i + 1] != '0') || inf[i] == '%' || inf[i] == '*'))
			if ((inf[i] == 's' && inf[i + 1] == 'i' && inf[i + 2] == 'n' && inf[i + 3] == '(')
				|| (inf[i] == 'c' && inf[i + 1] == 'o' && inf[i + 2] == 's' && inf[i + 3] == '('))
				i += 3;
			else {
				cout << "Wrong input.\n";
				return;
			}

			for (int i = 0, len = strlen(inf); i < len; ++i)
				if (inf[i] != ' ') {
					if (inf[i] == '(' || inf[i] == 's' || inf[i] == 'c') {
						op[topo++] = inf[i];
						if (inf[i] == 's' || inf[i] == 'c')
							i += 3;
					}
					else if (inf[i] == ')') {
						while (op[topo - 1] != '(' && op[topo - 1] != 's' && op[topo - 1] != 'c')
							rpn(st, tops, op[--topo]);
						if (op[topo - 1] == '(')
							--topo;
						else
							rpn(st, tops, op[--topo]);

					}
					else if (is_op(inf[i])) {
						char curop = inf[i];

						if (inf[i] == '+' || inf[i] == '-')
							if (i == 0 || inf[i - 1] == '(' || inf[i - 1] == 's' || inf[i - 1] == 'c') {
								st[tops++] = 0;
							}

						while (topo > 0 && priority(op[topo - 1]) >= priority(inf[i]))
							rpn(st, tops, op[--topo]);
						op[topo++] = (curop);
					}
					else {
						int k = inf[i] - '0';
						while (isdigit(inf[i + 1])) {
							++i;
							k = k * 10 + inf[i] - '0';
						}
						st[tops++] = k;
					}
				}
			while (topo > 0)
				rpn(st, tops, op[--topo]);
			cout << st[tops - 1] << '\n';
}