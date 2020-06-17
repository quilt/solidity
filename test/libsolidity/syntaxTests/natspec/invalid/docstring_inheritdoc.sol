contract C {
    /// @inheritdoc X
    function f() internal {
    }
}
// ----
// DocstringParsingError 1430: (17-34): Documentation tag @inheritdoc references contract "X", but the contract doesn't exist or doesn't override this function.
