#ifndef RANKINGCALC_H
#define RANKINGCALC_H

#include <set>
#include "SoccerBro-Stats.h"
#include "Utils.h"
#include "teams.h"

namespace soccerbro_stats {
	namespace rankingCalc {
		using match_pair = std::pair<std::string, std::string>;	// home & away teams pair
		using versus_map = std::map<match_pair, int>;			// keep track of number of versus games

		using team_games_scores_map = std::map<std::string, std::pair<int, int>>;
		// <teamID, ranking>
		using team_ranking = std::map<std::string, float>;
		// Ordered team set
		using team_set = std::set<std::string>;

		enum class Error_Code
		{
			Success,
			NoRecords,
			Invalid
		};

		//@brief: The abstract factory class for multiple ranking calculation moedels
		//
		//@json of "mathes" file format:
		/*----------------------------------------------*
		 *	{											*
		 *		"matches": [							*
		 *			{									*
		 *				"homeId": ...,					*
		 *				"awayId": ...,					*
		 *				"homeScore": ...,				*
		 *				"awayScore": ...				*
		 *			},									*
		 *		]										*
		 *	}											*
		 *----------------------------------------------*/
		 //@json of team rankings file format:
		 /*----------------------------------------------*
		 *	{											*
		 *		"teamId_1": ranking_1					*
		 *		"teamId_2": ranking_2					*
		 *		...										*
		 *	}											*
		 *----------------------------------------------*/
		class SOCCERBRO_DLL_EXPORTS AbstractRankingCalc
		{
		public:
			AbstractRankingCalc() = default;
			AbstractRankingCalc(const AbstractRankingCalc&) = default;
			AbstractRankingCalc(AbstractRankingCalc&&) = default;
			AbstractRankingCalc& operator=(const AbstractRankingCalc&) = default;

			virtual ~AbstractRankingCalc();

		public:
			virtual void outputToConsole() const;
			virtual Error_Code initialize(const nlojson& initialRanking) = 0;
			virtual Error_Code compute_and_update(const char* injsonFile,
				const char* outjsonFile) = 0;
			virtual Error_Code compute_and_update(const nlojson& injson,
				const char* outjsonFile) = 0;
			virtual Error_Code compute_and_update(const nlojson& injson,
				nlojson& outjson) = 0;

		protected:
			nlojson m_teamRankings;
		};

		using rankingCalcPtr = std::shared_ptr<AbstractRankingCalc>;

	} // namespace rankingCalc
} // namespace soccerbro_stats
#endif // !RANKINGCALC_H
