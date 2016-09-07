#ifndef STATUS_CODES
#define STATUS_CODES


namespace Core {

    enum Status{
        SUCCESSFUL,
        BOOT_LOADING_ERROR,
        LOGGER_LOADING_ERROR,
        MANAGERS_LOADING_ERROR,
        NO_MANAGERS_ERROR,
        NO_MAIN_INI_ERROR
    };
}

namespace Library {

}

namespace Forms {

}

#endif // STATUS_CODES

