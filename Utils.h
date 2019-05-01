#ifndef UTILS_H
#define UTILS_H

#include "SoccerBro-Stats.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>
#include <map>

namespace soccerbro_stats {
	namespace utils {
		
		// Generic function to get the number of digits of an integer
		template<class T>
		int numDigits(T number)
		{
			int digits = 0;
			if (number < 0) digits = 1;
			while (number) {
				number /= 10;
				digits++;
			}
			return digits;
		}

		/* nlojson Utility functions */
		SOCCERBRO_DLL_EXPORTS void printJson(const nlojson& jsonObj);
		SOCCERBRO_DLL_EXPORTS nlojson loadDataFromJason(const char* jsonFile);
		SOCCERBRO_DLL_EXPORTS void saveDataToJason(const char* jsonFile, const nlojson& j);

		// Get the current time and convert it to string
		SOCCERBRO_DLL_EXPORTS std::string current_time2string();
		SOCCERBRO_DLL_EXPORTS std::string current_year();
		SOCCERBRO_DLL_EXPORTS std::string previous_year();
		SOCCERBRO_DLL_EXPORTS std::string timestamp2time(const std::string &timestamp);
		SOCCERBRO_DLL_EXPORTS int timestamp2year_i(const long long &timestamp);
		SOCCERBRO_DLL_EXPORTS std::string timestamp2date_str(const long long &timestamp);
		SOCCERBRO_DLL_EXPORTS std::string timestamp2year_str(const long long &timestamp);

	} // namespace utils
} // namespace soccerbro_stats

#endif // UTILS_H
