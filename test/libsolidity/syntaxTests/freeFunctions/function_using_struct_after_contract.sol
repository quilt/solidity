contract C {
    struct S { uint x; }
}
function f() returns (uint) { S storage t; }
// ----
// DeclarationError: (70-71): Identifier not found or not unique.
