contract test {
    mapping(uint=>uint) map;
    function fun() public {
        mapping(uint=>uint) storage a = map;
        map = a;
        (map) = a;
        (map, map) = (a, a);
    }
}
// ----
// TypeError: (126-129): Types in storage containing (nested) mappings cannot be assigned to.
// TypeError: (144-147): Types in storage containing (nested) mappings cannot be assigned to.
// TypeError: (163-166): Types in storage containing (nested) mappings cannot be assigned to.
// TypeError: (168-171): Types in storage containing (nested) mappings cannot be assigned to.
