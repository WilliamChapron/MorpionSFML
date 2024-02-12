#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

inline void printTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Utilisation de std::ctime_s pour obtenir une reprï¿½sentation en texte du temps actuel
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &currentTime);
    std::cout << "Timestamp: " << buffer;
}

inline float getCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();

    // Convertir la durée en secondes à virgule flottante
    return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
}