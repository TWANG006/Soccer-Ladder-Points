#include "Elonet_rankingcalc.h"

namespace soccerbro_stats {
	namespace rankingCalc
	{
		Elonet_RankingCalc::Elonet_RankingCalc(const char* jsonFile)
		{
			m_teamRankings = utils::loadDataFromJason(jsonFile);
		}

		Elonet_RankingCalc::~Elonet_RankingCalc()
		{}

		Error_Code Elonet_RankingCalc::initialize(const nlojson& initialRanking)
		{
			if (initialRanking.is_null())
			{
				return Error_Code::NoRecords;
			}

			m_teamRankings = initialRanking;

			return Error_Code::Success;
		}

		Error_Code Elonet_RankingCalc::compute_and_update(const char* injsonFile,
			const char* outjsonFile)
		{
			//1. Load the new matches and load rankings to map
			nlojson inJson = utils::loadDataFromJason(injsonFile);
			team_ranking ranking_map = m_teamRankings;

			if (inJson.is_null() || inJson["matches"].is_null())
			{
				return Error_Code::NoRecords;
			}

			//2. Pre-compute all needed parameters
			float K = 50.0f;

			auto sA = [](const int homeScore, const int awayScore) {
				if (homeScore > awayScore) return 1.0f;
				else if (homeScore == awayScore) return 0.5f;
				else return 0.0f;
			};

			//3. Update the rankings
			for (auto i = 0; i < inJson["matches"].size(); i++)
			{
				std::string homeId = inJson["matches"][i]["homeId"];
				std::string awayId = inJson["matches"][i]["awayId"];

				// K = 50 for 11-aside and K = 40 for 7-aside
				if (static_cast<int>(inJson["matches"][i]["type"]) == 11)
					K = 50.0f;
				else if (static_cast<int>(inJson["matches"][i]["type"]) == 7)
					K = 40.0f;

				float rA = 0, rB = 0;

				// Get rA 
				auto it = ranking_map.find(homeId);
				if (it == ranking_map.end())
				{
					rA = 1000.0f;
					ranking_map.insert(std::make_pair(homeId, 1000.0f));
				}
				else
				{
					rA = it->second;
				}

				// Get rB
				it = ranking_map.find(awayId);
				if (it == ranking_map.end())
				{
					rB = 1000.0f;
					ranking_map.insert(std::make_pair(awayId, 1000.0f));
				}
				else
				{
					rB = it->second;
				}

				// Get scores
				int homeScore = inJson["matches"][i]["homeScore"];
				int awayScore = inJson["matches"][i]["awayScore"];

				// Compute new ranking of rA
				float addParam = ceil(K * G(homeScore, awayScore) * (sA(homeScore, awayScore) - pA(rA, rB, true)));
				ranking_map[homeId] = rA + addParam;

				// Compute new ranking of rB
				addParam = ceil(K * G(homeScore, awayScore) * (sA(awayScore, homeScore) - pA(rB, rA, false)));
				ranking_map[awayId] = rB + addParam;
			}

			//4. Update and output the rankings
			m_teamRankings = ranking_map;

			utils::saveDataToJason(outjsonFile, m_teamRankings);

			return Error_Code::Success;
		}

		Error_Code Elonet_RankingCalc::compute_and_update(const nlojson & inJson, const char * outjsonFile)
		{
			team_ranking ranking_map = m_teamRankings;

			if (inJson.is_null() || inJson["matches"].is_null())
			{
				return Error_Code::NoRecords;
			}

			//2. Pre-compute all needed parameters
			float K = 50.0f;

			auto sA = [](const int homeScore, const int awayScore) {
				if (homeScore > awayScore) return 1.0f;
				else if (homeScore == awayScore) return 0.5f;
				else return 0.0f;
			};

			//3. Update the rankings
			for (auto i = 0; i < inJson["matches"].size(); i++)
			{
				std::string homeId = inJson["matches"][i]["homeId"];
				std::string awayId = inJson["matches"][i]["awayId"];

				// K = 50 for 11-aside and K = 40 for 7-aside
				if (static_cast<int>(inJson["matches"][i]["type"]) == 11)
					K = 50.0f;
				else if (static_cast<int>(inJson["matches"][i]["type"]) == 7)
					K = 40.0f;

				float rA = 0, rB = 0;

				// Get rA 
				auto it = ranking_map.find(homeId);
				if (it == ranking_map.end())
				{
					rA = 1000.0f;
					ranking_map.insert(std::make_pair(homeId, 1000.0f));
				}
				else
				{
					rA = it->second;
				}

				// Get rB
				it = ranking_map.find(awayId);
				if (it == ranking_map.end())
				{
					rB = 1000.0f;
					ranking_map.insert(std::make_pair(awayId, 1000.0f));
				}
				else
				{
					rB = it->second;
				}

				// Get scores
				int homeScore = inJson["matches"][i]["homeScore"];
				int awayScore = inJson["matches"][i]["awayScore"];

				// Compute new ranking of rA
				float addParam = ceil(K * G(homeScore, awayScore) * (sA(homeScore, awayScore) - pA(rA, rB, true)));
				ranking_map[homeId] = rA + addParam;

				// Compute new ranking of rB
				addParam = ceil(K * G(homeScore, awayScore) * (sA(awayScore, homeScore) - pA(rB, rA, false)));
				ranking_map[awayId] = rB + addParam;
			}

			//4. Update and output the rankings
			m_teamRankings = ranking_map;

			utils::saveDataToJason(outjsonFile, m_teamRankings);

			return Error_Code::Success;
		}

		Error_Code Elonet_RankingCalc::compute_and_update(const nlojson & inJson, nlojson & outjson)
		{
			team_ranking ranking_map = m_teamRankings;

			if (inJson.is_null() || inJson["matches"].is_null())
			{
				return Error_Code::NoRecords;
			}

			//2. Pre-compute all needed parameters
			float K = 50.0f;

			auto sA = [](const int homeScore, const int awayScore) {
				if (homeScore > awayScore) return 1.0f;
				else if (homeScore == awayScore) return 0.5f;
				else return 0.0f;
			};

			//3. Update the rankings
			for (auto i = 0; i < inJson["matches"].size(); i++)
			{
				std::string homeId = inJson["matches"][i]["homeId"];
				std::string awayId = inJson["matches"][i]["awayId"];

				// K = 50 for 11-aside and K = 40 for 7-aside
				if (static_cast<int>(inJson["matches"][i]["type"]) == 11)
					K = 50.0f;
				else if (static_cast<int>(inJson["matches"][i]["type"]) == 7)
					K = 40.0f;

				float rA = 0, rB = 0;

				// Get rA 
				auto it = ranking_map.find(homeId);
				if (it == ranking_map.end())
				{
					rA = 1000.0f;
					ranking_map.insert(std::make_pair(homeId, 1000.0f));
				}
				else
				{
					rA = it->second;
				}

				// Get rB
				it = ranking_map.find(awayId);
				if (it == ranking_map.end())
				{
					rB = 1000.0f;
					ranking_map.insert(std::make_pair(awayId, 1000.0f));
				}
				else
				{
					rB = it->second;
				}

				// Get scores
				int homeScore = inJson["matches"][i]["homeScore"];
				int awayScore = inJson["matches"][i]["awayScore"];

				// Compute new ranking of rA
				float addParam = ceil(K * G(homeScore, awayScore) * (sA(homeScore, awayScore) - pA(rA, rB, true)));
				ranking_map[homeId] = rA + addParam;

				// Compute new ranking of rB
				addParam = ceil(K * G(homeScore, awayScore) * (sA(awayScore, homeScore) - pA(rB, rA, false)));
				ranking_map[awayId] = rB + addParam;
			}

			//4. Update and output the rankings
			m_teamRankings = ranking_map;
			outjson = m_teamRankings;

			return Error_Code::Success;
		}

		float Elonet_RankingCalc::pA(const float rA, const float rB, const bool AishomeTeam)
		{
			if (AishomeTeam)
				return (1.0f / (1.0f + pow(10.0f, -(rA + 100.0f - rB)/400.0f)));
			else
				return (1.0f / (1.0f + pow(10.0f, -(rA - rB)/400.0f)));
		}

		float Elonet_RankingCalc::G(const int homeScore, const int awayScore)
		{
			int absDiff = abs(homeScore - awayScore);

			if (absDiff <= 1) return 1.0f;
			else if (absDiff == 2) return 1.5f;
			else return float(absDiff + 11) / 8.0f;
		}

	} // namespace rankingCalc
} // namespace soccerbro_stats