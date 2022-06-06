#include "Exception.hpp"

namespace Database {
    Exception::Exception(const String ExceptionMsg) {
        msg = ExceptionMsg;
    }

    String Exception::what() const {
        return msg;
    }
}