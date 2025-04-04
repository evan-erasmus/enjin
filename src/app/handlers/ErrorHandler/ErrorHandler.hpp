#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <fstream> // Added to define std::ofstream

enum class ErrorSeverity
{
    INFO,
    WARNING,
    ERROR,
    FATAL
};

struct ErrorEntry
{
    std::string message;
    ErrorSeverity severity;
    std::string timestamp;
};

class ErrorHandler
{
public:
    ErrorHandler();
    ~ErrorHandler();

    void initialize();
    void cleanup();
    void handleError(const std::string &message, ErrorSeverity severity = ErrorSeverity::ERROR);
    void logError(const std::string &message, ErrorSeverity severity);
    void handleException(const std::exception &e);

private:
    bool is_initialized;
    std::vector<ErrorEntry> error_log;

    std::string logfile_path;
    std::ofstream logfile;
    bool console_output;
};

ErrorHandler &getErrorHandler();