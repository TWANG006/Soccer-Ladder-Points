#ifndef ELONET_RANKINGCALC_H
#define ELONET_RANKINGCALC_H

#include "rankingcalc.h"

namespace soccerbro_stats {
	namespace rankingCalc
	{
		//@brief: The class implements the improved Elo ranking method EloRating.net. Note that this model
		//		  prefers well-calculated initial rankings of each team. Otherwise, it may consume
		//		  a long time and much more match records to achieve a steady state. This is a self-update
		//		  model. No re-calculation is required for all teams.
		//
		//@model:
		//	rA' = rA + K x G x (sA - pA)
		//		rA': team A's new ranking
		//		rA : team A's current ranking
		//		 K : K-factor indicating the importance of the match
		//			K-factor table
		//			*--Friendly				, K=30--*
		//			*--Minor Tournaments	, K=40--*
		//			*--Leagues				, K=50--*
		//			*--Premier Tournaments	, K=60--*
		//		 NOTE: currently K is made a constant at 50!
		//		 G : Goal diff indicator, suppose diff = N
		//			G = 1 if N <= 1
		//			G = 1.5 if N = 2
		//			G = (N+11)/8 if N >= 3
		//		sA : Real outcome of the match, mapped to {0, 0.5, 1} for lose, draw and win
		//		pA : Predicted outcome of the match, and pA is modeled as a logistic distribution as
		//			pA = 1 / (1 + 10^(-(rA + 100 - rB)), 100 here is added to home team benifit
		//
		//@input/output:
		//	Inputs: 
		//		1. Initial ranking json, if no, initialize all rankings to 1500 instead
		//		2. json of matches array 
		//  Outputs:
		//		json file containing updated rankings
		class SOCCERBRO_DLL_EXPORTS Elonet_RankingCalc : public AbstractRankingCalc
		{
		public:
			Elonet_RankingCalc() = default;
			Elonet_RankingCalc(const Elonet_RankingCalc&) = default;
			Elonet_RankingCalc(Elonet_RankingCalc&&) = default;
			Elonet_RankingCalc& operator=(const Elonet_RankingCalc&) = default;

			Elonet_RankingCalc(const char* jsonFile);
			~Elonet_RankingCalc();

		public:
			virtual Error_Code initialize(const nlojson& initialRanking) override;
			virtual Error_Code compute_and_update(const char* injsonFile, const char* outjsonFile) override;
			virtual Error_Code compute_and_update(const nlojson& inJson, const char* outjsonFile) override;
			virtual Error_Code compute_and_update(const nlojson& inJson, nlojson& outjson) override;

		private:
			float pA(const float rA, const float rB, const bool AishomeTeam = true);
			float  G(const int homeScore, const int awayScore);

		};

	} // namespace rankingCalc
} // namespace soccerbro_stats

#endif // !ELONET_RANKINGCALC_H
