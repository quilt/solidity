contract D {
}

contract C is D {
    /// @inheritdoc D
    function f() internal {
    }
}
// ----
// DocstringParsingError 1430: (38-55): Documentation tag @inheritdoc references contract "D", but the contract doesn't exist or doesn't override this function.
