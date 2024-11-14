#include <stdio.h>

int check (FILE * f, char expect, char status, char esc) {
	int c = fgetc(stdin);

	switch ( esc ) {
	case 0: {
		switch (status) {
		case 0: {
			switch (c) {
			case '"': return check(f, expect, 1, 0);
			case '\\': return check(f, expect, 0, 1);
			case EOF: return expect == 0;
			case '{': return check(f, '}', 0, 0) && check(f, expect, 0, 0);
			case '[': return check(f, ']', 0, 0) && check(f, expect, 0, 0);
			case '(': return check(f, ')', 0, 0) && check(f, expect, 0, 0);
			case '}': case ']': case ')': return expect == c;
			default: return 0;
			}
		}

		case 1: {
			if (c == '\\') return check(f, expect, 1, 1);
			if (c == '"') return check(f, expect, 0, 0);
			if (c == EOF) return 0;
			return check(f, expect, 1, 0);
			}
		}
	}
	case 1: {
		if ( c == EOF ) return 0;
		return check(f, expect, status, 0);
		}
	}
}

int main(int argc, char * argv[]) {
	if ( check(stdin, 0, 0, 0) ) printf("YES\n");
	else printf("NO\n");
}
