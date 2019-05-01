#include "rankingcalc.h"
#include <fstream>

namespace soccerbro_stats {
	namespace rankingCalc {

		AbstractRankingCalc::~AbstractRankingCalc()
		{}

		void AbstractRankingCalc::outputToConsole() const
		{
			utils::printJson(m_teamRankings);
		}

	} // namespace rankingCalc
} // namespace soccerbro_stats