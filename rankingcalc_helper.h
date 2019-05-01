#ifndef RANKINGCALC_HELPER_H
#define RANKINGCALC_HELPER_H

#include "ls_rankingcalc.h"
#include "Elonet_rankingcalc.h"
#include "wmElo_rankingcalc.h"

namespace soccerbro_stats {
	namespace rankingCalc {

		// Helper functions to calculate the rankings in one functions call
		SOCCERBRO_DLL_EXPORTS void calculateLeastSquareRanking(const char* inFile, const char* outFile);
		SOCCERBRO_DLL_EXPORTS void updateRankingUsingElo_Net(const char* matchesJson, const char* currentRankingJson, const char* newRankingJson);
		SOCCERBRO_DLL_EXPORTS void updateRankingUsingWM_Elo(const char* matchesJson, const char* currentRankingJson, const char* newRankingJson);
		
		SOCCERBRO_DLL_EXPORTS void updateRankingUsingElo_Net(const nlojson &matchesJson, const nlojson &currentRankingJson, const char* newRankingJson);
		SOCCERBRO_DLL_EXPORTS void updateRankingUsingWM_Elo(const nlojson &matchesJson, const nlojson &currentRankingJson, const char* newRankingJson);
		
		SOCCERBRO_DLL_EXPORTS void updateRankingUsingElo_Net(const nlojson &matchesJson, const nlojson &currentRankingJson, nlojson & newRankingJson);
		SOCCERBRO_DLL_EXPORTS void updateRankingUsingWM_Elo(const nlojson &matchesJson, const nlojson &currentRankingJson, nlojson & newRankingJson);

	} // namespace rankingCalc
} // namespace soccerbro_stats


#endif // !RANKINGCALC_HELPER_H
