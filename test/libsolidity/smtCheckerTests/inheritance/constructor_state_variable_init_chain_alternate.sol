pragma experimental SMTChecker;

contract A {
	uint x = 1;
}

contract B is A {
	constructor() { x = 2; }
}

contract C is B {
}

contract D is C {
	constructor() {
		assert(x == 2);
		assert(x == 3);
	}
}
// ----
// Warning 4661: (199-213): Assertion violation happens here
