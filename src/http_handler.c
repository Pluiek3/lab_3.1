/**
 * @file http_handler.c
 * @brief Обработчик HTTP-запросов для сервиса анализа сна
 */

#include "../mongoose/mongoose.h"
#include "include/http_handler.h"
#include "include/sleep_logic.h"
#include "include/time_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

// Глобальная переменная для управления состоянием сервера
volatile bool server_running = true;

static bool uri_matches(const struct mg_str *uri, const char *pattern) {
    size_t n = strlen(pattern);
    return uri->len == n && memcmp(uri->buf, pattern, n) == 0;
}

static void send_file_response(struct mg_connection *c, 
                              struct mg_http_message *hm, 
                              const char *path) {
    struct mg_http_serve_opts opts = {0};
    mg_http_serve_file(c, hm, path, &opts);
}

void handle_request(struct mg_connection *c, 
                    struct mg_http_message *hm) {
    // Обработка запроса на выключение сервера
    if (uri_matches(&hm->uri, "/shutdown")) {
        mg_http_reply(c, 200, "Content-Type: text/plain\r\n", 
                     "Server shutting down...");
        server_running = false;
        return;
    }
    
    if (uri_matches(&hm->uri, "/")) {
        send_file_response(c, hm, "templates/sleep.html");
    } 
    else if (uri_matches(&hm->uri, "/calculate")) {
        char bedtime[16] = {0}, waketime[16] = {0};
        
        mg_http_get_var(&hm->query, "bedtime", bedtime, sizeof(bedtime));
        mg_http_get_var(&hm->query, "waketime", waketime, sizeof(waketime));
        
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
    else {
        mg_http_reply(c, 404, NULL, "Not Found");
    }
}