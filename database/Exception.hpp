#pragma once

#include "String.hpp"

namespace Database {
	class Exception {
	private:
		String msg;
	public:
		Exception(const String ExceptionMsg);

		String what() const;
	};

	class OutOfRange : public Exception {
	public:
		OutOfRange(const String ExceptionMsg);
	};

	class InvalidArgument : public Exception {
	public:
		InvalidArgument(const String ExceptionMsg);
	};

	class LengthError : public Exception {
	public:
		LengthError(const String ExceptionMsg);
	};
}

