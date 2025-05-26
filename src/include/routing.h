/**
 * @file routing.h
 * @brief Маршрутизатор HTTP-запросов
 */

#ifndef ROUTING_H
#define ROUTING_H

#include "../mongoose/mongoose.h"

extern volatile bool server_running;

/**
 * @brief Обрабатывает маршрутизацию HTTP-запросов
 * 
 * @param c Соединение Mongoose
 * @param hm HTTP-сообщение
 * @return true если маршрут был обработан, false если не найден
 */
bool route_request(struct mg_connection *c, struct mg_http_message *hm);

#endif /* ROUTING_H */