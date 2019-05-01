#ifndef SOCCERBRO_STATS_H
#define SOCCERBRO_STATS_H

//!- Macro for library dll export utility
#if defined (_WIN32) 
#		if defined (SOCCERBRO_DLL_EXPORTS_MODE)
#			define SOCCERBRO_DLL_EXPORTS __declspec(dllexport)
#		else
#			define SOCCERBRO_DLL_EXPORTS __declspec(dllimport)
#		endif
#else
#    define SOCCERBRO_DLL_EXPORTS
#endif

//!- SoccerBro-Stats Engine Version
#define VERSION "1.0"

//!- Debugging macro
#ifdef SOCCERBRO_DEBUG_MSG
#define DEBUG_MSG(x) do {std::cout<<"[SOCCERBRO_DEBUG]: "<<x<<std::endl;} while(0)
#else
#define DEBUG_MSG(x) do {} while(0);
#endif // SoccerBro-Stats debug message

#include <string>
#include <vector>
#include "json.hpp"

namespace soccerbro_stats
{
	using nlojson = nlohmann::json;	// json parser alias

	enum class DATA_BASE
	{
		TEST,
		MY,
		OFFICIAL
	};

} // namespace soccerbro_stats

#endif // !SOCCERBRO_STATS_H


