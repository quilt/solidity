pragma experimental ABIEncoderV2;

contract test {
    struct S {
        T t;
    }
    struct T {
        mapping (uint => uint) k;
    }
    function f(S calldata b) external {
    }
}
// ----
// TypeError: (155-167): Types containing (nested) mappings can only be parameters or return variables of internal or library functions.
// TypeError: (155-167): Type struct test.S is only valid in storage because it contains a (nested) mapping.
