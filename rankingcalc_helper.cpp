#include "rankingcalc_helper.h"

namespace soccerbro_stats {
	namespace rankingCalc {
		
		void calculateLeastSquareRanking(const char* inFile, const char* outFile)
		{
			rankingCalc::rankingCalcPtr lsPtr(new rankingCalc::LS_RankingCalc);
			lsPtr->compute_and_update(inFile, outFile);

			std::cout << "-----------------LS Ranking Model--------------------" << std::endl;
			lsPtr->outputToConsole();
		}

		void updateRankingUsingElo_Net(const char* matchesJson, const char* currentRankingJson, const char* newRankingJson)
		{
			rankingCalc::rankingCalcPtr eloPtr(new rankingCalc::Elonet_RankingCalc(currentRankingJson));
			eloPtr->compute_and_update(matchesJson, newRankingJson);

			std::cout << "-----------------EloRating.net Ranking Model--------------------" << std::endl;
			eloPtr->outputToConsole();
		}

		void updateRankingUsingWM_Elo(const char* matchesJson, const char* currentRankingJson, const char* newRankingJson)
		{
			rankingCalc::rankingCalcPtr wmPtr(new rankingCalc::WMElo_RankingCalc(currentRankingJson));
			wmPtr->compute_and_update(matchesJson, newRankingJson);

			std::cout << "-----------------FIFA Women Ranking Model--------------------" << std::endl;
			wmPtr->outputToConsole();
		}

		void updateRankingUsingElo_Net(const nlojson & matchesJson, const nlojson & currentRankingJson, const char * newRankingJson)
		{
			rankingCalc::rankingCalcPtr eloPtr(new rankingCalc::Elonet_RankingCalc());
			eloPtr->initialize(currentRankingJson);
			eloPtr->compute_and_update(matchesJson, newRankingJson);

			std::cout << "-----------------EloRating.net Ranking Model--------------------" << std::endl;
			eloPtr->outputToConsole();
		}

		void updateRankingUsingWM_Elo(const nlojson & matchesJson, const nlojson &currentRankingJson, const char * newRankingJson)
		{
			rankingCalc::rankingCalcPtr wmPtr(new rankingCalc::WMElo_RankingCalc());
			wmPtr->initialize(currentRankingJson);
			wmPtr->compute_and_update(matchesJson, newRankingJson);

			std::cout << "-----------------FIFA Women Ranking Model--------------------" << std::endl;
			wmPtr->outputToConsole();
		}

		void updateRankingUsingElo_Net(const nlojson & matchesJson, const nlojson & currentRankingJson, nlojson & newRankingJson)
		{
			rankingCalc::rankingCalcPtr eloPtr(new rankingCalc::Elonet_RankingCalc());
			eloPtr->initialize(currentRankingJson);
			eloPtr->compute_and_update(matchesJson, newRankingJson);

			std::cout << "-----------------EloRating.net Ranking Model--------------------" << std::endl;
			eloPtr->outputToConsole();
		}

		void updateRankingUsingWM_Elo(const nlojson & matchesJson, const nlojson & currentRankingJson, nlojson & newRankingJson)
		{
			rankingCalc::rankingCalcPtr wmPtr(new rankingCalc::WMElo_RankingCalc());
			wmPtr->initialize(currentRankingJson);
			wmPtr->compute_and_update(matchesJson, newRankingJson);

			std::cout << "-----------------FIFA Women Ranking Model--------------------" << std::endl;
			wmPtr->outputToConsole();
		}

	} // namespace rankingCalc
} // namespace soccerbro_stats