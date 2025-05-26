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

void send_file_response(struct mg_connection *c, 
                       struct mg_http_message *hm, 
                       const char *path) {
    struct mg_http_serve_opts opts = {0};
    mg_http_serve_file(c, hm, path, &opts);
}

void handle_calculation(struct mg_connection *c, 
                       struct mg_http_message *hm) {
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