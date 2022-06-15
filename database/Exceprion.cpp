#include "Exception.hpp"

namespace Database {
    Exception::Exception(const String ExceptionMsg) {
        msg = ExceptionMsg;
    }

    String Exception::what() const {
        return msg;
    }

    OutOfRange::OutOfRange(const String ExceptionMsg) : Exception(ExceptionMsg) {};

	InvalidArgument::InvalidArgument(const String ExceptionMsg) : Exception(ExceptionMsg) {};

	LengthError::LengthError(const String ExceptionMsg) : Exception(ExceptionMsg) {};
}