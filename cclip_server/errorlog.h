#pragma once

#ifndef CCLIP_ERRORLOG_H
#define CCLIP_ERRORLOG_H

#include <fstream>
#include <string>
#include <mutex>
#include <ctime>

#define ERROR_LOG "error.log"

void write_errorlog(std::ofstream& lerr, std::mutex& mtx_errorlog, const std::string& e);
void close_errorlog(std::ofstream& lerr, std::mutex& mtx_errorlog);

#endif