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
}

