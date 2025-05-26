/**
 * @file http_handler.h
 * @brief Интерфейс обработчика HTTP-запросов для сервиса анализа сна
 */

#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "../mongoose/mongoose.h"


/**
 * @brief Обрабатывает запрос на расчет сна
 */
void handle_calculation(struct mg_connection *c, 
                       struct mg_http_message *hm);

/**
 * @brief Отправляет файл в ответ на HTTP-запрос
 */
void send_file_response(struct mg_connection *c, 
                       struct mg_http_message *hm, 
                       const char *path);

#endif /* HTTP_HANDLER_H */