contract D {
    mapping (uint => uint) a;
    mapping (uint => uint) b;
    function foo() public view {
        mapping (uint => uint) storage c = b;
        b = c;
    }
}
// ----
// TypeError: (160-161): Types in storage containing (nested) mappings cannot be assigned to.
