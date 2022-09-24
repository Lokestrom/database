#include "Exception.hpp"

namespace Database {
    Exception::Exception(const char* ExceptionMsg) {
        auto i = 0;
        for (; ExceptionMsg[i] != '\0'; i++);
        if (msg != nullptr)
            delete[] msg;
        msg = new char[i+1];
        for (auto j = 0; j < i; j++) {
            msg[j] = ExceptionMsg[j];
        }
        msg[i] = '\0';
    }
    Exception::~Exception() {
        delete[] msg;
    }

    char* Exception::what() const noexcept{
        return msg;
    }

    OutOfRange::OutOfRange(const char* ExceptionMsg) : Exception(ExceptionMsg) {};

	InvalidArgument::InvalidArgument(const char* ExceptionMsg) : Exception(ExceptionMsg) {};

	LengthError::LengthError(const char* ExceptionMsg) : Exception(ExceptionMsg) {};
} 