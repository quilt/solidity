pragma experimental SMTChecker;

contract C {
	uint[] a;
	constructor() {
		a.pop();
	}
}
// ----
// Warning 2529: (83-90): Empty array "pop" detected here.
