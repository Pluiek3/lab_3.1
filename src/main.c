/**
 * @file main.c
 * @brief Основной файл HTTP-сервера для сервиса анализа сна
 */

#include "../mongoose/mongoose.h"
#include "include/http_handler.h"
#include <stdio.h>
#include <stdbool.h>

static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        handle_request(c, (struct mg_http_message *)ev_data);
    }
}

int main() {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    
    if (!mg_http_listen(&mgr, "http://0.0.0.0:8000", fn, NULL)) {
        fprintf(stderr, "Ошибка запуска сервера\n");
        return 1;
    }
    
    printf("Сервер запущен на http://localhost:8000\n");
    printf("Для выключения сервера отправьте запрос на /shutdown\n");
    
    // Основной цикл обработки событий с проверкой флага
    while (server_running) {
        mg_mgr_poll(&mgr, 1000);
    }
    
    printf("Сервер завершает работу...\n");
    mg_mgr_free(&mgr);
    return 0;
}