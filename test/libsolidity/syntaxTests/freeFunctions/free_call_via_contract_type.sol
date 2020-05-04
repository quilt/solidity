contract C {
    function f() public pure {}
}
function fun() {
    C.f();
}
// ----
// TypeError: (68-73): Cannot call function via contract type name.
