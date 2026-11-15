typedef int (*PFN)();


int Tst000() {
	return 2 + 2 == 4;
}


int Tst013() {
	int x;
	int *p;
	x = 0;
	p = &x;
	return !p[0];
}

int Tst017() {
	struct { int x; int y; } s;

	s.x = 3;
	s.y = 5;
	return s.y - s.x == 2;
}


PFN tests[] = {
	Tst000	, 0	, 0	, 0	, 0	, 0	, 0	, 0	, 0	, 0
	, 0	, 0	, 0, Tst013	, 0	, 0	, 0	, Tst017
};


int main() {
	int count = sizeof(tests)/sizeof(tests[0]);
	int i;
	for (i = 0; i != count; ++i) {
		PFN test = tests[i];
		if (test && !test()) {
			printf("Test %03d FAILED!\n", i);
			return 1;
		}
	}

	printf("Tests succeeded\n");
	return 0;
}
