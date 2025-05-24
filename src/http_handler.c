/**
 * @file http_handler.c
 * @brief Обработчик HTTP-запросов для сервиса анализа сна
 *
 * Модуль обрабатывает входящие HTTP-запросы и предоставляет:
 * - Отдачу статических файлов (HTML, CSS)
 * - API для расчета продолжительности сна
 */

#include "../mongoose/mongoose.h"
#include "../include/http_handler.h"
#include "../include/sleep_logic.h"
#include "../include/time_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Проверяет совпадение URI запроса с шаблоном
 * @param uri URI из HTTP-запроса
 * @param pattern Шаблон для сравнения
 * @return true если URI совпадает с шаблоном, иначе false
 *
 * @note Сравнение выполняется побайтово без учета регистра
 */
static bool uri_matches(const struct mg_str *uri, 
                        const char *pattern) {
                        size_t n = strlen(pattern);
    return uri->len == n && memcmp(uri->buf, pattern, n) == 0;
}

/**
 * @brief Отправляет файл в ответ на HTTP-запрос
 * @param c Подключение Mongoose
 * @param hm HTTP-сообщение
 * @param path Путь к файлу для отправки
 *
 * @warning Файл должен существовать и быть доступным для чтения
 */
static void send_file_response(struct mg_connection *c, 
                              struct mg_http_message *hm, 
                              const char *path) {
    struct mg_http_serve_opts opts = {0};
    mg_http_serve_file(c, hm, path, &opts);
}

/**
 * @brief Основной обработчик HTTP-запросов
 * @param c Подключение Mongoose
 * @param hm Разобранное HTTP-сообщение
 *
 * Обрабатывает следующие маршруты:
 * - / - главная страница (sleep.html)
 * - /calculate - API расчета сна
 * - /styles.css - CSS стили
 *
 * @example Пример запроса расчета сна:
 * GET /calculate?bedtime=22:30&waketime=6:45
 *
 */
void handle_request(struct mg_connection *c, 
                   struct mg_http_message *hm) {
    if (uri_matches(&hm->uri, "/")) {
        send_file_response(c, hm, "templates/sleep.html");
    } 
    // API расчета сна
    else if (uri_matches(&hm->uri, "/calculate")) {
        char bedtime[16] = {0}, waketime[16] = {0};
        
        mg_http_get_var(&hm->query, "bedtime", 
                        bedtime,  sizeof(bedtime));
        mg_http_get_var(&hm->query, "waketime", 
                        waketime, sizeof(waketime));
        
        if (bedtime[0] && waketime[0]) {
            SleepData data = {
                .bedtime  = parse_time(bedtime),
                .waketime = parse_time(waketime)
            };
            
            SleepResult result = calculate_sleep(data);
            mg_http_reply(
                c, 200,
                "Content-Type: application/json\r\n",
                "{\"hours\":%d,\"minutes\":%d,\"comment\":\"%s\"}",
                result.hours, result.minutes, result.comment
            );
            return;
        }
        
        mg_http_reply(c, 400, NULL, "Bad Request");
    } 
    
    else if (uri_matches(&hm->uri, "/styles.css")) {
        send_file_response(c, hm, "css/styles.css");
    }
}