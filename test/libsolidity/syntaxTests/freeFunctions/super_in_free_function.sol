contract C {}
function f() {
    super;
}
// ----
// DeclarationError: (33-38): Undeclared identifier. "super" is not (or not yet) visible at this point.
