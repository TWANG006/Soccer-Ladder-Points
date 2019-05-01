#include "Utils.h"

namespace soccerbro_stats {
	namespace utils {

		/* nlojson Related Utility functions */
		void printJson(const nlojson& jsonObj)
		{
			std::cout << std::setw(4) << jsonObj << std::endl;
		}

		nlojson loadDataFromJason(const char* jsonFile)
		{
			std::ifstream jsonStream(jsonFile, std::ifstream::in);
			nlojson jsonHandle;
			jsonStream >> jsonHandle;
			jsonStream.close();

			return jsonHandle;
		}

		void saveDataToJason(const char* jsonFile, const nlojson& j)
		{
			std::ofstream out(jsonFile, std::ios::out | std::ios::trunc);
			out << std::setw(4) << j;
			out.close();
		}

		/* Time related utilities */
		std::string current_time2string()
		{
			// Get the current time
			std::time_t currentTime_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &currentTime_t);

			// Format the string
			std::ostringstream stringStream;
			stringStream << "_" << t_tmNowTime.tm_year + 1900
				<< "_" << t_tmNowTime.tm_mon + 1
				<< "_" << t_tmNowTime.tm_mday
				<< "-"
				<< t_tmNowTime.tm_hour;

			return stringStream.str();
		}

		std::string current_year()
		{
			// Get the current time
			std::time_t currentTime_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &currentTime_t);

			std::ostringstream stringStream;
			stringStream << t_tmNowTime.tm_year + 1900;

			return stringStream.str();
		}

		std::string previous_year()
		{
			// Get the current time
			std::time_t currentTime_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &currentTime_t);

			std::ostringstream stringStream;
			stringStream << t_tmNowTime.tm_year + 1900 - 1;

			return stringStream.str();
		}

		std::string timestamp2time(const std::string& timestamp)
		{
			// Validate the timestamp
			if (timestamp.size() != 13 && timestamp.size() != 10)
			{
				throw std::exception("Invalid Time stampe!");
			}

			// Convert the timestamp string to integer
			auto timeInt = std::strtoll(timestamp.c_str(), NULL, 10);

			if (timestamp.size() == 13) {
				timeInt = (timeInt / 1000);
			}

			// Convert timestamp to time
			auto filetime = time_t(timeInt);
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &filetime);

			// Format the string
			std::ostringstream stringStream;
			stringStream << "_" << t_tmNowTime.tm_year + 1900
				<< "_" << t_tmNowTime.tm_mon + 1
				<< "_" << t_tmNowTime.tm_mday
				<< "-"
				<< t_tmNowTime.tm_hour;

			return stringStream.str();
		}

		int timestamp2year_i(const long long &timestamp)
		{
			// Validate the time stamp
			int num_digits = numDigits<long long>(timestamp);
			if (num_digits != 13 && num_digits != 10)
			{
				throw std::exception("Invalid Time stampe!");
			}

			auto temp_timestamp = timestamp;
			if (num_digits == 13) temp_timestamp /= 1000;

			// Convert timestamp to time
			auto filetime = time_t(temp_timestamp);
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &filetime);

			return t_tmNowTime.tm_year + 1900;
		}

		std::string timestamp2date_str(const long long &timestamp)
		{
			// Validate the time stamp
			int num_digits = numDigits<long long>(timestamp);
			if (num_digits != 13 && num_digits != 10)
			{
				throw std::exception("Invalid Time stampe!");
			}

			auto temp_timestamp = timestamp;
			if (num_digits == 13) temp_timestamp /= 1000;

			// Convert timestamp to time
			auto filetime = time_t(temp_timestamp);
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &filetime);

			// Format the string
			std::ostringstream stringStream;
			stringStream << t_tmNowTime.tm_year + 1900
				<< t_tmNowTime.tm_mon + 1
				<< t_tmNowTime.tm_mday;

			return stringStream.str();
		}

		std::string timestamp2year_str(const long long &timestamp)
		{
			// Validate the time stamp
			int num_digits = numDigits<long long>(timestamp);
			if (num_digits != 13 && num_digits != 10)
			{
				throw std::exception("Invalid Time stampe!");
			}

			auto temp_timestamp = timestamp;
			if (num_digits == 13) temp_timestamp /= 1000;

			// Convert timestamp to time
			auto filetime = time_t(temp_timestamp);
			struct tm t_tmNowTime;
			localtime_s(&t_tmNowTime, &filetime);

			// Format the string
			std::ostringstream stringStream;
			stringStream << t_tmNowTime.tm_year + 1900;

			return stringStream.str();
		}

	} // namespace utils
} // namespace soccerbro_stats