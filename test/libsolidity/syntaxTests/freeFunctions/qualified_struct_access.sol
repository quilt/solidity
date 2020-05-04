function f() returns (uint) { C.S storage t; t.x; }

contract C {
    struct S { uint x; }
}
// ----
// TypeError: (45-46): This variable is of storage pointer type and can be accessed without prior assignment, which would lead to undefined behaviour.
