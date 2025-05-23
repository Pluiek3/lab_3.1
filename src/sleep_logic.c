#include "../include/sleep_logic.h"
#include <math.h>

static const char* get_sleep_comment(double hours) {
    if (hours < 4) return "💀 Критически мало! Очень вредно для здоровья!. P.S Вы случайно не ЖОП?";
    else if (hours < 6)  return "⚠️ Маловато... Старайтесь спать больше.";
    else if (hours < 8)  return "😐 Нормально, но можно лучше.";
    else if (hours < 10) return "😊 Отлично! Идеальное количество сна.";
    return "🤔 Перебор! Это может быть вредно.";
}

SleepResult calculate_sleep(SleepData data) {
    int bedtime_mins  = time_to_minutes(data.bedtime);
    int waketime_mins = time_to_minutes(data.waketime);
    
    if (waketime_mins < bedtime_mins) {
        waketime_mins += 24 * 60; // Учет сна через полночь
    }
    
    int total_mins = waketime_mins - bedtime_mins;
    Time duration  = minutes_to_time(total_mins);
    
    double hours   = total_mins / 60.0;
    
    return (SleepResult){
        .hours   = duration.hours,
        .minutes = duration.minutes,
        .comment = get_sleep_comment(hours)
    };
}
