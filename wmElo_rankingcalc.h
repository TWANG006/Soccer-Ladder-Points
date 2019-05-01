#ifndef WMELO_RANKIGNCALC_H
#define	WMELO_RANKINGCALC_H

#include "rankingcalc.h"

namespace soccerbro_stats {
	namespace rankingCalc
	{
		//@brief: The class implements FIFA women's world rankings algorithm.
		//
		//@model:
		//	rA' = rA + K x I x (sA - pA)
		//		rA' : team A's new ranking
		//		 rA : team A's current ranking
		//		  K : constant at 15
		//		   I: importance of the match
		//			*--Friendly				, I=1--*
		//			*--Minor Tournaments	, I=2--*
		//			*--Leagues				, I=3--*
		//			*--Premier Tournaments	, I=4--*
		//		NOTE: Currently I = 3
		//		 sA : team A's outcome
		//		 pA : team A's predicted outcome
		//			pA = 1 / (1 + 10^(-(rA + 100 - rB))
		//@input/output:
		//	Inputs: 
		//		1. Initial ranking json, if no, initialize all rankings to 1500 instead
		//		2. json of matches array 
		//  Outputs:
		//		json file containing updated rankings
		class SOCCERBRO_DLL_EXPORTS WMElo_RankingCalc : public AbstractRankingCalc
		{
		public:
			WMElo_RankingCalc() = default;
			WMElo_RankingCalc(const WMElo_RankingCalc&) = default;
			WMElo_RankingCalc(WMElo_RankingCalc&&) = default;
			WMElo_RankingCalc& operator=(const WMElo_RankingCalc&) = default;

			WMElo_RankingCalc(const char* jsonFile);
			~WMElo_RankingCalc();

		public:
			virtual Error_Code initialize(const nlojson& initialRanking) override;
			virtual Error_Code compute_and_update(const char* injsonFile, const char* outjsonFile) override;
			virtual Error_Code compute_and_update(const nlojson& injson, const char* outjsonFile) override;
			virtual Error_Code compute_and_update(const nlojson& injson, nlojson& outjson) override;

		private:
			float pA(const float rA, const float rB, const bool AishomeTeam = true);
			std::pair<float, float>  sA(const int homeScore, const int awayScore);

			static const std::array<std::array<float, 7>, 6> m_sA_LUT;
		};

	} // namespace rankingCalc
} // namespace soccerbro_stats

#endif // !WMELO_RANKIGNCALC_H
