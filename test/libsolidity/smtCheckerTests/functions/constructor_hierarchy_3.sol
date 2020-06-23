pragma experimental SMTChecker;
contract C {
	uint a;
	constructor(uint x) {
		a = x;
	}
}

abstract contract B is C {
	constructor(uint x) {
		a = x;
	}
}

contract A is B {
	constructor(uint x) B(x) C(x + 2) {
		assert(a == x);
		assert(a == x + 1);
	}
}
// ----
// Warning 2661: (217-222): Overflow (resulting value larger than 2**256 - 1) happens here
// Warning 2661: (265-270): Overflow (resulting value larger than 2**256 - 1) happens here
// Warning 4661: (253-271): Assertion violation happens here
