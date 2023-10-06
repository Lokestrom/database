/*
Athor: Loke Strøm
*/
#include "Exception.hpp"

namespace Database {
    Exception::Exception(const char* ExceptionMsg) noexcept {
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
    Exception::~Exception() noexcept {
        delete[] msg;
    }

    char* Exception::what() const noexcept{
        return msg;
    }

    OutOfRange::OutOfRange(const char* ExceptionMsg) noexcept 
        : Exception(ExceptionMsg) {};

	InvalidArgument::InvalidArgument(const char* ExceptionMsg) noexcept
        : Exception(ExceptionMsg) {};

	LengthError::LengthError(const char* ExceptionMsg) noexcept 
        : Exception(ExceptionMsg) {};

    SystemError::SystemError(const char* ExceptionMsg) noexcept 
        : Exception(ExceptionMsg) {};

    WriteFileError::WriteFileError(const char* ExceptionMsg) noexcept 
        : Exception(ExceptionMsg) {};
} 