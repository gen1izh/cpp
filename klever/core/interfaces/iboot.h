#ifndef IBOOT
#define IBOOT

/*!
 * \brief Интерфейс загрузчика
 */
class IBoot {

  public:
    IBoot(){}
    virtual ~IBoot(){}

    /*!
     * \brief Запуск кода загрузчика
     * \return возвращает результат true - все успешно
     */
    virtual bool execute() = 0;
};


#endif // IBOOT

