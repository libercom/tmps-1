#include "Logger.h"

#include <cstdio>  //needed for printf
#define print(a) printf("%s(%s:%d) " a,  __func__,__FILE__, __LINE__)
#define println(a) print(a "\n")

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(const std::string& message)
{
	println("Hello mi lady");
}
