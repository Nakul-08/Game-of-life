#ifndef LOG_STRUCT_H
#define LOG_STRUCT_H
#include <string>

const std::string app_path = "C:\\Users\\ayaan\\Documents\\Projects\\COA\\GameOfLifeLauncher\\";
struct log {
    std::string timestamp;
    std::string mode;
    std::string num_generations;
    std::string time_taken;
};

#endif // LOG_STRUCT_H
