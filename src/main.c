#include <stdio.h>

#define SYM_LEN 17	// 8 bits per symbol
#define EXP_LEN 512
#define STR_LEN 4096

typedef struct N {
	unsigned char s[SYM_LEN];
	struct N *e[16];
} N;

typedef N E[EXP_LEN];
E prog;

unsigned char token[EXP_LEN][SYM_LEN];
unsigned char buffer[STR_LEN] = "";


int  _strnul (char a[]) { return *a == '\0'; }
int  _strequ (char a[], char b[]) { while (*a || *b) if (*a++ != *b++) return 0; return 1; }
int  _strlen (char a[]) { int i; for (; a[i]; i++); return i; }
void _strcpy (char a[], char b[]) { for (; *b; *a++, *b++) *a = *b; }
void _stradd (char a[], char b[]) { int i = _strlen (a); while (*b) a[i++] = *b++; }
void _strset (char a[], char b) { for (int i = 0; a[i]; i++) a[i] = b; }
void _strpop (char a[])	{ for (int i = 0; a[i]; i++) a[i] = a[i + 1]; }

int  _nodnul (N *n) { if (n) { if (n->s[0] == '\0') return 1; return 0; } return 1; }
int  _nodlen (N n) { int i; while (!_nodnul (n.e[i])) i++; return i; }
int  _explen (N *n) { int i; while (!_nodnul (&n[i])) i++; return i; }

int  _codlen (unsigned char s[]) {
	for (int i, j, k; ; i++) {
		for (j = 0; j < SYM_LEN; j++) if (s[i + j] == '\0') k++;
		if (k >= SYM_LEN) return i;
		k = 0;
	}
}


void DEBUG_PrintTokens (unsigned char s[EXP_LEN][SYM_LEN]) { for (int i = 0; i < EXP_LEN; i++) if (!_strnul (s[i])) printf ("%i : %s\n", i, s[i]); }
void DEBUG_PrintCode (unsigned char s[STR_LEN]) { 
	if (!_strnul (s)) {
		printf ("Code : ");
		for (int i = 0; i < _codlen (s); i++) printf ("%hhx", s[i]);
		printf ("\n");
	} 
}
void DEBUG_PrintNode (N n) { 
	printf ("Symbol : %s", n.s); 
	for (int i = 0; i < _nodlen (n); i++) {
		printf (" | Next : %s", n.e[i]->s);
	}
	printf ("\n"); 
}
void DEBUG_PrintProgram (E e) {
	for (int i = 0; i < _explen (e); i++) {
		printf ("Node : %i | ", i);
		DEBUG_PrintNode (e[i]);
	}
} 


N *GetBySymbol (E e, unsigned char s[]) {
	if (_nodnul (e)) return NULL;
	if (_strequ (e->s, s)) return e;
	GetBySymbol (e + 1, s);
}

void WriteSymbol (unsigned char s[STR_LEN], N n) {
	if (!_nodlen (n)) _stradd (s, n.s);
	for (int i = 0; i < _nodlen(n); i++)
		if (_nodlen (n)) WriteSymbol (s, *n.e[i]);
}


void GetTokens (unsigned char r[EXP_LEN][SYM_LEN], unsigned char *s, unsigned char c[]) {	
	for (int i = 0, j = 0, k = 0; i < _strlen (s); i++) {
		for (int l = 0; l < _strlen (c); l++) {	
			if (s[i] == c[l]) { j=0; k++; goto next; } 
		}
		r[k][j++] = s[i];
		if (_strnul (r[k])) printf ("true\n");
next:	}
}

void StringConvert (unsigned char *s) {
	int len = _strlen (s);
	unsigned char r[len];

	for (int i = 0; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9')	r[i] = s[i] - '0';
		if (s[i] >= 'a' && s[i] <= 'f')	r[i] = s[i] - ('a' - 10);
	}
	for (int i = 0; i < len; i++) s[i] = '\0';
	for (int i, j = 0; j < len; i++, j += 2) { s[i] = r[j] * 0x10 + r[j+1]; }
}

/*
void CreateNode (unsigned char s[EXP_LEN][SYM_LEN], unsigned char c[STR_LEN], E e) {
				N n = {""};
				_strcpy (n.s, s[i++]);

				for (int j = 0; s[i + j][0] != '@' && s[i + j][0] != '%' && s[i + j][0] != '#' && s[i + j][0] != '\0'; j++) {
					// Add Monode	
					if (!GetBySymbol (e, s[i + j])) {
						N m = {""}; _strcpy (m.s, s[i + j]); e[_explen (e)] = m;
					}
					n.e[_nodlen (n)] = GetBySymbol (e, s[i + j]);	
				}
				e[_explen (e)] = n; // Add Main Node
}

*/

void CreateNode (unsigned char s[EXP_LEN][SYM_LEN], unsigned char c[STR_LEN], E e, int i) {
				N n = {""};
				_strcpy (n.s, s[i++]);

				for (int j = 0; s[i + j][0] != '@' && s[i + j][0] != '%' && s[i + j][0] != '#' && s[i + j][0] != '\0'; j++) {
					// Add Monode	
					if (!GetBySymbol (e, s[i + j])) {
						N m = {""}; _strcpy (m.s, s[i + j]); e[_explen (e)] = m;
					}
					n.e[_nodlen (n)] = GetBySymbol (e, s[i + j]);	
				}
				e[_explen (e)] = n; // Add Main Node
}

void Parse (unsigned char s[EXP_LEN][SYM_LEN], unsigned char c[STR_LEN], E e) {
	for (int i = 0; i < EXP_LEN; i++) {	//
		switch (s[i][0]) {
			case '@':
				_strpop (s[i]);
				CreateNode (s, c, e, i);
				break;
			case '%':
				_strpop (s[i]);
				if (_nodnul (GetBySymbol (e, s[i]))) CreateNode (s, c, e, i);
				WriteSymbol (c, *GetBySymbol (e, s[i]));
				break;
			default:
				break;
		}
	}
}


void Run (unsigned char *s) { void (*f) () = (void (*)()) s; f (); }
void ReadFile (unsigned char s[], unsigned char r[]) {
	FILE *f = fopen (s, "r");
	if (!f) return;
	char c; while (c != EOF) { c = fgetc (f); r[_strlen (r)] = c; }
	r[_strlen (r) - 1] = '\0';		// Removes EOF
	fclose (f);
}

void WriteFile (unsigned char s[], unsigned char r[]) {
	FILE *f = fopen (s, "w");
	if (!f) return;
	for (int i = 0; i < _codlen (r); i++) fputc (buffer[i], f);
	fclose (f);
}


int main (int argc, char *argv[]) {
	if (!argv[1]) { 
		scanf ("%[^\n]", buffer);
		GetTokens (token, buffer, " 	\n");
		_strset (buffer, '\0');
		Parse (token, buffer, prog);
		Run (buffer);
	}
	for (int i = 0; argv[i]; i++) {
		if (argv[i][0] == '-' && argv[i][1]) {
			switch (argv[i][1]) {
				case 'i':
					scanf ("%[^\n]", buffer);
				case 'f':
					for (int j = 1; argv[i + j][0] != '-'; j++)
						ReadFile (argv[i + j], buffer);
					GetTokens (token, buffer, " 	\n");
					_strset (buffer, '\0');
					Parse (token, buffer, prog);
					StringConvert (buffer);
					break;
				case 'r':
					Run (buffer);
					break;
				case 'o':
					WriteFile (argv[i + 1], buffer);
					break;
				case 'd':
					if (_strnul (buffer)) break;
					DEBUG_PrintTokens (token);
					DEBUG_PrintProgram (prog);
					DEBUG_PrintCode (buffer);
				default:
					break;
			}
		}
	}
}
