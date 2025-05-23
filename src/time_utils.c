/**
 * @file time_utils.c
 * @brief Реализация утилит для работы со временем
 * 
 * Модуль предоставляет функции для конвертации и парсинга времени
 */

#include "../include/time_utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Парсит строку времени в формате HH:MM в структуру Time
 * 
 * @param time_str Строка времени в формате "HH:MM"
 * @return Time Структура с распарсенным временем
 * 
 * @note Не выполняет валидацию формата входной строки
 * @warning При неверном формате строки поведение не определено
 * 
 * Пример использования:
 * @code
 * Time t = parse_time("23:45");
 * printf("%02d:%02d", t.hours, t.minutes); // Выведет "23:45"
 * @endcode
 */
Time parse_time(const char *time_str) {
    Time t = {0};
    sscanf(time_str, "%d:%d", &t.hours, &t.minutes);
    return t;
}

/**
 * @brief Конвертирует структуру Time в общее количество минут
 * 
 * @param t Структура Time для конвертации
 * @return int Общее количество минут (часы * 60 + минуты)
 * 
 * Пример использования:
 * @code
 * Time t = {8, 30};
 * int mins = time_to_minutes(t); // Вернет 510
 * @endcode
 */
int time_to_minutes(Time t) {
    return t.hours * 60 + t.minutes;
}

/**
 * @brief Конвертирует минуты в структуру Time
 * 
 * @param total_minutes Общее количество минут
 * @return Time Структура с часами и минутами
 * 
 * @note Выполняет нормализацию часов (значение часов будет в диапазоне 0-23)
 * 
 * Пример использования:
 * @code
 * Time t = minutes_to_time(1470); // 24*60 + 30
 * printf("%02d:%02d", t.hours, t.minutes); // Выведет "00:30"
 * @endcode
 */
Time minutes_to_time(int total_minutes) {
    Time t;
    t.hours   = (total_minutes / 60) % 24;
    t.minutes = total_minutes % 60;
    return t;
}