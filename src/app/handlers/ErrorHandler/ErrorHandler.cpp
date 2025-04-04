#include "ErrorHandler.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

ErrorHandler::ErrorHandler()
    : logfile_path("./error.log"), console_output(true) {
}

ErrorHandler::~ErrorHandler()
{
    cleanup();
}

ErrorHandler &getErrorHandler()
{
    static ErrorHandler instance;
    return instance;
}

void ErrorHandler::initialize()
{
    logfile.open(logfile_path, std::ios::app);
    if (!logfile.is_open())
    {
        std::cerr << "Failed to open log file: " << logfile_path << std::endl;
    }
}

std::string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void ErrorHandler::logError(const std::string &message, ErrorSeverity severity)
{
    ErrorEntry entry{message, severity, getCurrentTimestamp()};
    error_log.push_back(entry);

    std::string severityStr;
    switch (severity)
    {
    case ErrorSeverity::INFO:
        severityStr = "INFO";
        break;
    case ErrorSeverity::WARNING:
        severityStr = "WARNING";
        break;
    case ErrorSeverity::ERROR:
        severityStr = "ERROR";
        break;
    case ErrorSeverity::FATAL:
        severityStr = "FATAL";
        break;
    }

    std::string logMessage = entry.timestamp + " [" + severityStr + "] " + message;

    if (logfile.is_open())
    {
        logfile << logMessage << std::endl;
    }

    if (console_output)
    {
        std::cerr << logMessage << std::endl;
    }
}

void ErrorHandler::handleException(const std::exception &e)
{
    logError("Exception: " + std::string(e.what()), ErrorSeverity::ERROR);
}

void ErrorHandler::handleError(const std::string &message, ErrorSeverity severity)
{ // = ErrorSeverity::ERROR
    logError(message, severity);
}

void ErrorHandler::cleanup()
{
    error_log.clear();
    if (logfile.is_open())
    {
        logfile.flush();
    }
    if (logfile.is_open())
    {
        logfile.close();
    }
}