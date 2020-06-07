pragma experimental ABIEncoderV2;

contract C {
    struct S { uint a; S[2][] sub; }
    function f() public pure returns (uint, S memory) {
    }
}
// ----
// TypeError: (129-137): Recursive type not allowed for public or external contract functions.
