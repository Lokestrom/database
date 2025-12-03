#include <string>

namespace Database{
#if DATABASE_EXCEPTIONS_ENABLED == 1
#include <exception>
#define NOEXCEPT noexcept(false)
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
#if __cplusplus > 202302L
#error C++23 or later is required when using std::expected \
	use FORCE_THROW_EXCEPTION if compiling without exceptions
#endif
#include <expected>
#define NOEXCEPT noexcept(true)
template<template T>
using Expected = std::expected<T, std::string>;
template<std::is_reference T>
using Expected = std::expected<std::reference_wrapper<T>, std::string>;
#define DATABASE_EXCEPTION_HANDLING_THROW_ERROR(err) return std::unexpected(err)
#define DB_CONCAT_IMPL(a, b) a##b
#define DB_CONCAT(a, b) DB_CONCAT_IMPL(a, b)
#define DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(lhs, expr)                                 \
	auto DB_CONCAT(_db_try_res_, __LINE__) = (expr);          \
	if (!DB_CONCAT(_db_try_res_, __LINE__))                   \
		PROPEGATE_ERROR(DB_CONCAT(_db_try_res_, __LINE__));   \
	(lhs) = std::move(*DB_CONCAT(_db_try_res_, __LINE__));
#define DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(Expr) if (auto _tmp = (Expr); !_tmp) return std::unexpected(_tmp.error());
#define DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN try {

#define DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END \
	} catch (const std::exception& e) { \
		return std::unexpected(e.what()); \
	}
#define DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(expr) expr.value();
#define DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(expr) expr.value();
#define DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD [[nodiscard]]
#endif

}