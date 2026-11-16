// Tests are copied from https://github.com/c-testsuite/c-testsuite


typedef int (*PFN)();


int T000() {
	return 2 + 2 == 4;
}


int T013() {
	int x;
	int *p;
	x = 0;
	p = &x;
	return !p[0];
}

int T017() {
	struct { int x; int y; } s;

	s.x = 3;
	s.y = 5;
	return s.y - s.x == 2;
}


PFN tests[] = {
	T000	, 0	, 0	, 0			, 0	, 0	, 0	, 0			, 0	, 0
	, 0		, 0	, 0	, T013	, 0	, 0	, 0	, T017
};


int main() {
	int count = sizeof(tests)/sizeof(tests[0]);
	int i;
	for (i = 0; i != count; ++i) {
		PFN test = tests[i];
		if (test && !test()) {
			printf("Test T%03d FAILED!\n", i);
			return 1;
		}
	}

	printf("Tests succeeded\n");
	return 0;
}
