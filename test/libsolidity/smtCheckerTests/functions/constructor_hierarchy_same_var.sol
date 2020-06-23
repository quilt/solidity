pragma experimental SMTChecker;
contract C {
	uint a;
	constructor(uint x) {
		a = x;
	}
}

contract A is C {
	constructor() C(2) {
		assert(a == 0);
		assert(C.a == 0);
	}
}
// ----
// Warning 4661: (148-162): Assertion violation happens here
// Warning 4661: (166-182): Assertion violation happens here
