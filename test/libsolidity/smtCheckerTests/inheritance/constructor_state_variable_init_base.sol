pragma experimental SMTChecker;

contract C {
	uint x = 2;
}

contract D is C {
	constructor() {
		assert(x == 2);
		assert(x == 3);
	}
}
// ----
// Warning 4661: (124-138): Assertion violation happens here
