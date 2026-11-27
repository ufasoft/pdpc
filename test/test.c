// A few tests are copied from https://github.com/c-testsuite/c-testsuite


typedef int (*PFN)();


int T000() {
	return 2 + 2 == 4;
}

int T001() {
#ifdef _PDPC
	return sizeof(int) == 2;
#else
	return sizeof(int) == 4;
#endif
}

int T002() {
#ifdef __pdp11__
	return __pdp11__ == 40;
#else
	return 1;
#endif
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

int T019() {
	struct S { struct S *p; int x; } s;
	s.x = 0;
	s.p = &s;
	return !s.p->p->p->p->p->x;
}

int foo(int a, int b) { return 2 + a - b; }

int T021() {
	return foo(1, 3) == 0;
}


#define ADD(X, Y) (X + Y)

int T065() {
	return ADD(1, 2) == 3;
}

int T068() {
#if 0
	return 0;
#elif 1
	return 1;
#else
	return 0;
#endif
}


PFN tests[] = {
	T000	, T001	, T002	, 0				, 0	, 0	, 0	, 0			, 0	, 0
	, 0		, 0	, 0	, T013	, 0		, 0	, 0	, T017			, 0	, &T019
	, 0		, T021	, 0	, 0	, 0		, 0	, 0	, 0	, 0	, 0
	, 0		, 0	, 0	, 0	, 0	, 0		, 0	, 0	, 0	, 0
	, 0		, 0	, 0	, 0	, 0	, 0		, 0	, 0	, 0	, 0
	, 0		, 0	, 0	, 0	, 0	, 0		, 0	, 0	, 0	, 0
	, 0		, 0	, 0	, 0	, 0	, T065	, 0	, 0	, T068	, 0
};


int main() {
	int count = sizeof(tests)/sizeof(tests[0]);
	int i;
	for (i = 0; i != count; ++i) {
		PFN test = tests[i];
		if (test) {
			printf("T%03d ", i);
			if (!test()) {
				printf("\nTest T%03d FAILED!\n", i);
				return 1;
			}
		}
	}

	printf("\nTests succeeded\n");
	return 0;
}
