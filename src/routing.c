/**
 * @file router.c
 * @brief Реализация маршрутизатора HTTP-запросов
 */

#include "include/routing.h"
#include "include/http_handler.h"
#include <string.h>

volatile bool server_running = true;

static bool uri_matches(const struct mg_str *uri, const char *pattern) {
    size_t n = strlen(pattern);
    return uri->len == n && memcmp(uri->buf, pattern, n) == 0;
}

bool route_request(struct mg_connection *c, struct mg_http_message *hm) {
    if (uri_matches(&hm->uri, "/shutdown")) {
        mg_http_reply(c, 200, "Content-Type: text/plain\r\n", 
                     "Server shutting down...");
        server_running = false;
        return true;
    }
    
    if (uri_matches(&hm->uri, "/")) {
        send_file_response(c, hm, "templates/sleep.html");
        return true;
    } 
    else if (uri_matches(&hm->uri, "/calculate")) {
        handle_calculation(c, hm);
        return true;
    } 
    else if (uri_matches(&hm->uri, "/styles.css")) {
        send_file_response(c, hm, "css/styles.css");
        return true;
    }
    
    return false;
}