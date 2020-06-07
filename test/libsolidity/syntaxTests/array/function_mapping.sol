pragma experimental ABIEncoderV2;

contract Test {
    function f(mapping(uint => uint)[] memory x) public pure {}
}
// ----
// TypeError: (66-98): Types containing (nested) mappings can only be parameters or return variables of internal or library functions.
// TypeError: (66-98): Type mapping(uint256 => uint256)[] is only valid in storage because it contains a (nested) mapping.
