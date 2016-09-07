#ifndef ERROR
#define ERROR


namespace Core {

    enum States{
        SUCCESSFUL,
        BOOT_LOADING_ERROR,
        LOGGER_LOADING_ERROR,
        MANAGERS_LOADING_ERROR,
        NO_MANAGERS_ERROR,
        NO_MAIN_INI_ERROR
    };

}


#endif // ERROR

