/**
 * @file http_handler.h
 * @brief Интерфейс обработчика HTTP-запросов для сервиса анализа сна
 */

#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "../mongoose/mongoose.h"

// Добавляем флаг для управления состоянием сервера
extern volatile bool server_running;

/**
 * @brief Основная функция обработки HTTP-запросов
 */
void handle_request(struct mg_connection *c, 
                   struct mg_http_message *hm);

#endif /* HTTP_HANDLER_H */