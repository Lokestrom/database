#include <string>

#ifndef DATABASE_EXCEPTIONS_ENABLED
#error macro: DATABASE_EXCEPTIONS_ENABLED, not defined. must include link the CMake or add DATABASE_EXCEPTIONS_ENABLED some other way
#endif

#if DATABASE_EXCEPTIONS_ENABLED == 1
#include <exception>
#else
#include <expected>
#endif


namespace Database{
#if DATABASE_EXCEPTIONS_ENABLED == 1
#define DATABASE_EXCEPTION_HANDLING_NOEXCEPT noexcept(false)
template<typename T>
using Expected = T;
#define DATABASE_EXCEPTION_HANDLING_THROW_ERROR(errMsg) throw std::exception(errMsg)
#define DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(lhs, expr) lhs = expr
#define DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(Expr) (Expr);
#define DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
#define DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
#define DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(expr) expr
#define DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(expr) expr
#define DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD [[]]
#else
#define DATABASE_EXCEPTION_HANDLING_NOEXCEPT noexcept(true)
template<typename T, bool = std::is_reference_v<T>>
struct ExpectedHelper {
	using type = std::expected<T, std::string>;
};
template<typename T>
struct ExpectedHelper<T, true> {
	using type = std::expected<std::reference_wrapper<std::remove_reference_t<T>>, std::string>;
};
template<typename T>
using Expected = typename ExpectedHelper<T>::type;
#define DATABASE_EXCEPTION_HANDLING_THROW_ERROR(err) return std::unexpected(err)
#define DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(Expr) if (auto _tmp = (Expr); !_tmp) return std::unexpected(_tmp.error());
#define DB_CONCAT_IMPL(a, b) a##b 
#define DB_CONCAT(a, b) DB_CONCAT_IMPL(a, b)
#define DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(lhs, expr)                                 \
	auto DB_CONCAT(_db_try_res_, __LINE__) = (expr);          \
	if (!DB_CONCAT(_db_try_res_, __LINE__))                   \
		DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(DB_CONCAT(_db_try_res_, __LINE__));   \
	(lhs) = std::move(*DB_CONCAT(_db_try_res_, __LINE__));
#define DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN try {

#define DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END \
	} catch (const std::exception& e) { \
		return std::unexpected(e.what()); \
	}
#define DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(expr) expr.value()
#define DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(expr) expr.value()
#define DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD [[nodiscard]]
#endif

}