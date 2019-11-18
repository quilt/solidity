#include <test/tools/ossfuzz/protomutators/YulProtoMutator.h>

#include <libyul/Exceptions.h>

#include <src/text_format.h>

using namespace solidity::yul::test::yul_fuzzer;
using namespace protobuf_mutator;
using namespace std;

template <typename Proto>
using YPR = YulProtoCBRegistration<Proto>;
using YPM = YulProtoMutator;
using PrintChanges = YPM::PrintChanges;

MutationInfo::MutationInfo(ProtobufMessage const* _message, string const& _info):
	ScopeGuard([&]{ exitInfo(); }),
	m_protobufMsg(_message)
{
	writeLine("----------------------------------");
	writeLine("YULMUTATOR: " + _info);
	writeLine("Before");
	writeLine(SaveMessageAsText(*m_protobufMsg));

}

void MutationInfo::exitInfo()
{
	writeLine("After");
	writeLine(SaveMessageAsText(*m_protobufMsg));
}

template <typename T>
void YulProtoMutator::functionWrapper(
	CustomFuzzMutator<T> const& _callback,
	T* _message,
	unsigned _seed,
	unsigned _period,
	string const& _info,
	PrintChanges _printChanges)
{
	YulRandomNumGenerator random(_seed);

	if (_seed % _period == 0)
	{
		if (_printChanges == PrintChanges::Yes)
			MutationInfo m{_message, _info};
		_callback(_message, random);
	}
}

/// Add m/sstore(0, variable)
static YPR<Block> addStoreToZero(
	[](Block* _message, unsigned _seed)
	{
	  YPM::functionWrapper<Block>(
		  [](Block* _message, YulRandomNumGenerator& _rand)
		  {
			auto storeStmt = new StoreFunc();
			storeStmt->set_st(YPM::EnumTypeConverter<StoreFunc_Storage>{}.enumFromSeed(_rand()));
			storeStmt->set_allocated_loc(YPM::litExpression(0));
			storeStmt->set_allocated_val(YPM::refExpression(_rand));
			auto stmt = _message->add_statements();
			stmt->set_allocated_storage_func(storeStmt);
		  },
		  _message,
		  _seed,
		  YPM::s_highIP,
		  "Store to zero added"
	  );
	}
);

Literal* YPM::intLiteral(unsigned _value)
{
	auto lit = new Literal();
	lit->set_intval(_value);
	return lit;
}

VarRef* YPM::varRef(unsigned _seed)
{
	auto varref = new VarRef();
	varref->set_varnum(_seed);
	return varref;
}

Expression* YPM::refExpression(YulRandomNumGenerator& _rand)
{
	auto refExpr = new Expression();
	refExpr->set_allocated_varref(varRef(_rand()));
	return refExpr;
}

Expression* YPM::litExpression(unsigned _value)
{
	auto lit = intLiteral(_value);
	auto expr = new Expression();
	expr->set_allocated_cons(lit);
	return expr;
}

template <typename T>
T YPM::EnumTypeConverter<T>::validEnum(unsigned _seed)
{
	auto ret = static_cast<T>(_seed % (enumMax() - enumMin() + 1) + enumMin());
	if constexpr (std::is_same_v<std::decay_t<T>, FunctionCall_Returns>)
		yulAssert(FunctionCall_Returns_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, StoreFunc_Storage>)
		yulAssert(StoreFunc_Storage_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, NullaryOp_NOp>)
		yulAssert(NullaryOp_NOp_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, BinaryOp_BOp>)
		yulAssert(BinaryOp_BOp_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, UnaryOp_UOp>)
		yulAssert(UnaryOp_UOp_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, LowLevelCall_Type>)
		yulAssert(LowLevelCall_Type_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, Create_Type>)
		yulAssert(Create_Type_IsValid(ret), "Yul proto mutator: Invalid enum");
	else if constexpr (std::is_same_v<std::decay_t<T>, UnaryOpData_UOpData>)
		yulAssert(UnaryOpData_UOpData_IsValid(ret), "Yul proto mutator: Invalid enum");
	else
		static_assert(AlwaysFalse<T>::value, "Yul proto mutator: non-exhaustive visitor.");
	return ret;
}

template <typename T>
unsigned YPM::EnumTypeConverter<T>::enumMax()
{
	if constexpr (std::is_same_v<std::decay_t<T>, FunctionCall_Returns>)
		return FunctionCall_Returns_Returns_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, StoreFunc_Storage>)
		return StoreFunc_Storage_Storage_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, NullaryOp_NOp>)
		return NullaryOp_NOp_NOp_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, BinaryOp_BOp>)
		return BinaryOp_BOp_BOp_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, UnaryOp_UOp>)
		return UnaryOp_UOp_UOp_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, LowLevelCall_Type>)
		return LowLevelCall_Type_Type_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, Create_Type>)
		return Create_Type_Type_MAX;
	else if constexpr (std::is_same_v<std::decay_t<T>, UnaryOpData_UOpData>)
		return UnaryOpData_UOpData_UOpData_MAX;
	else
		static_assert(AlwaysFalse<T>::value, "Yul proto mutator: non-exhaustive visitor.");
}

template <typename T>
unsigned YPM::EnumTypeConverter<T>::enumMin()
{
	if constexpr (std::is_same_v<std::decay_t<T>, FunctionCall_Returns>)
		return FunctionCall_Returns_Returns_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, StoreFunc_Storage>)
		return StoreFunc_Storage_Storage_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, NullaryOp_NOp>)
		return NullaryOp_NOp_NOp_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, BinaryOp_BOp>)
		return BinaryOp_BOp_BOp_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, UnaryOp_UOp>)
		return UnaryOp_UOp_UOp_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, LowLevelCall_Type>)
		return LowLevelCall_Type_Type_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, Create_Type>)
		return Create_Type_Type_MIN;
	else if constexpr (std::is_same_v<std::decay_t<T>, UnaryOpData_UOpData>)
		return UnaryOpData_UOpData_UOpData_MIN;
	else
		static_assert(AlwaysFalse<T>::value, "Yul proto mutator: non-exhaustive visitor.");
}
