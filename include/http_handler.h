/**
 * @file http_handler.h
 * @brief Интерфейс обработчика HTTP-запросов для сервиса анализа сна
 * 
 * Предоставляет главную функцию обработки запросов для веб-сервера Mongoose,
 * реализующую сервис анализа качества сна.
 */

#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "../mongoose/mongoose.h"

/**
 * @brief Основная функция обработки HTTP-запросов
 * @param c Объект соединения Mongoose
 * @param hm Разобранное HTTP-сообщение
 * 
 * Данная функция обрабатывает все входящие HTTP-запросы и перенаправляет их на:
 * - Отдачу статических файлов (HTML, CSS)
 * - API расчета сна
 * - Обработку ошибок
 * 
 * Поддерживаемые маршруты:
 * - GET / → отдает sleep.html
 * - GET /calculate?bedtime=ЧЧ:ММ&waketime=ЧЧ:ММ → API расчета сна
 * - GET /styles.css → отдает CSS-файл
 * 
 * @note Обработчик должен быть зарегистрирован в Mongoose с помощью mg_http_listen()
 * 
 * @warning Сам обработчик не является потокобезопасным - Mongoose должен
 *          обрабатывать все аспекты многопоточности/синхронизации
 * 
 * @example Пример регистрации обработчика:
 * @code
 * struct mg_mgr mgr;
 * mg_mgr_init(&mgr);
 * mg_http_listen(&mgr, "http://0.0.0.0:8000", handle_request, NULL);
 * @endcode
 */
void handle_request(struct mg_connection *c, 
                   struct mg_http_message *hm);

#endif /* HTTP_HANDLER_H */