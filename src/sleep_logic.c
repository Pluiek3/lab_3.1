/**
 * @file sleep_logic.c
 * @brief Реализация логики расчета сна
 */

#include "../include/sleep_logic.h"
#include <math.h>

/**
 * @brief Получает текстовый комментарий о качестве сна
 * @param hours Количество часов сна
 * @return Соответствующий комментарий в виде строки
 * 
 * Функция возвращает различные комментарии в зависимости от количества часов сна:
 * - Менее 4 часов: критическое предупреждение
 * - 4-6 часов: предупреждение
 * - 6-8 часов: нейтральный комментарий
 * - 8-10 часов: положительный комментарий
 * - Более 10 часов: предупреждение о пересыпе
 */
static const char* get_sleep_comment(double hours) {
    if (hours < 4) return "💀 Критически мало! Очень вредно для здоровья!. P.S Вы случайно не ЖОП?";
    else if (hours < 6)  return "⚠️ Маловато... Старайтесь спать больше.";
    else if (hours < 8)  return "😐 Нормально, но можно лучше.";
    else if (hours < 10) return "😊 Отлично! Идеальное количество сна.";
    return "🤔 Перебор! Это может быть вредно.";
}

/**
 * @brief Вычисляет продолжительность сна и дает оценку
 * @param data Входные данные о времени отхода ко сну и пробуждения
 * @return Структура SleepResult с результатами расчета
 * 
 * Функция выполняет следующие действия:
 * 1. Конвертирует время в минуты
 * 2. Учитывает случай сна через полночь
 * 3. Вычисляет общую продолжительность сна
 * 4. Формирует комментарий о качестве сна
 */
SleepResult calculate_sleep(SleepData data) {
    int bedtime_mins  = time_to_minutes(data.bedtime);
    int waketime_mins = time_to_minutes(data.waketime);
    
    // Учет сна через полночь
    if (waketime_mins < bedtime_mins) {
        waketime_mins += 24 * 60;
    }
    
    int total_mins = waketime_mins - bedtime_mins;
    Time duration  = minutes_to_time(total_mins);
    
    double hours = total_mins / 60.0;
    
    return (SleepResult){
        .hours   = duration.hours,
        .minutes = duration.minutes,
        .comment = get_sleep_comment(hours)
    };
}