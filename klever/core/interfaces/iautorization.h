#ifndef IAUTORIZATION
#define IAUTORIZATION

/*!
 * \brief Интерфейс авторизации
 */
class IAutorization {

  public:
    IAutorization(){}
    virtual ~IAutorization(){}

    /*!
     * \brief Запуск кода загрузчика
     * \return возвращает результат true - все успешно
     */
    virtual bool execute() = 0;
};

#endif // IAUTORIZATION

