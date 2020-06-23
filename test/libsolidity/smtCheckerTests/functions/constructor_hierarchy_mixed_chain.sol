pragma experimental SMTChecker;
contract F {
	uint a;
	constructor() {
		a = 2;
	}
}

contract E is F {}
contract D is E {
	constructor() {
		a = 3;
	}
}
contract C is D {}
contract B is C {
	constructor() {
		a = 4;
	}
}

contract A is B {
	constructor(uint x) {
		assert(a == 4);
		assert(a == 5);
	}
}
// ----
// Warning 5667: (275-281): Unused function parameter. Remove or comment out the variable name to silence this warning.
// Warning 4661: (312-326): Assertion violation happens here
