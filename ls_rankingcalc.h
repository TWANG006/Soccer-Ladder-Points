#ifndef LS_RANKINGCALC_H
#define LS_RANKINGCALC_H

#include "rankingcalc.h"

namespace soccerbro_stats {
	namespace rankingCalc
	{
		//@brief: Use the Least Squares ranking algorithm. This json file used in this 
		//		  algorithm should contain all the match results of a certain period of 
		//		  all teams need to be ranked. 
		//
		//@model:
		//	y = rA - rB + e
		//		y: goal diff of team A and B
		//		rA: ranking of team A
		//		rB: ranking of team B
		//
		//@definition:
		//	min.  sum(y-(rA-rB))^2
		//
		//@Input&output:
		//	Input: json file of "mathes" array
		//	Output: json file containing teamIds as the keys and their rankings as the values 
		class SOCCERBRO_DLL_EXPORTS LS_RankingCalc : public AbstractRankingCalc
		{
		public:
			LS_RankingCalc() = default;
			LS_RankingCalc(const LS_RankingCalc&) = default;
			LS_RankingCalc(LS_RankingCalc&&) = default;
			LS_RankingCalc& operator=(const LS_RankingCalc&) = default;

			~LS_RankingCalc();

		public:
			/* The input json file should contain all the mathes played for all
			   the teams. */
			virtual Error_Code compute_and_update(const char* injsonFile, const char* outjsonFile) override;
			virtual Error_Code compute_and_update(const nlojson& injson, const char* outjsonFile) override;
			virtual Error_Code compute_and_update(const nlojson& injson, nlojson& outjson) override;

		private:
			//!- construct the linear system for the ls solver
			void constructSystem(const nlojson&, std::vector<float>& A, std::vector<float>& b);

			//!- Make this private since it will never be called by LS method
			virtual Error_Code initialize(const nlojson& initialRanking) override;

		private:
			int m_iNumTeams;
			team_set m_teamSet;
		};

	} // namespace rankingCalc
} // namespace soccerbro_stats
#endif // !LS_RANKINGCALC_H
