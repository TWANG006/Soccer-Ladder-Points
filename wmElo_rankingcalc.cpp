#include "wmElo_rankingcalc.h"

namespace soccerbro_stats {
	namespace rankingCalc
	{
		WMElo_RankingCalc::WMElo_RankingCalc(const char* jsonFile)
		{
			m_teamRankings = utils::loadDataFromJason(jsonFile);
		}

		WMElo_RankingCalc::~WMElo_RankingCalc()
		{}

		Error_Code WMElo_RankingCalc::initialize(const nlojson& initialRanking)
		{
			if (initialRanking.is_null())
			{
				return Error_Code::NoRecords;
			}

			m_teamRankings = initialRanking;

			return Error_Code::Success;
		}

		Error_Code WMElo_RankingCalc::compute_and_update(const char* injsonFile, const char* outjsonFile)
		{
			//1. Load the new matches and load rankings into map
			nlojson inJson = utils::loadDataFromJason(injsonFile);
			team_ranking ranking_map = m_teamRankings;

			if (inJson.is_null() || inJson["matches"].is_null())
			{
				return Error_Code::NoRecords;
			}

			//2. Pre-compute all needed parameters
			float K = 15.0f;
			float I = 3.0f;

			//3. Update the rankings
			for (auto i = 0; i < inJson["matches"].size(); i++)
			{
				std::string homeId = inJson["matches"][i]["homeId"];
				std::string awayId = inJson["matches"][i]["awayId"];

				// K = 50 for 11-aside and K = 40 for 7-aside
				if (static_cast<int>(inJson["matches"][i]["type"]) == 11)
					I = 3.0f;
				else if (static_cast<int>(inJson["matches"][i]["type"]) == 7)
					I = 2.0f;

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

				// Get the outcome
				std::pair<float, float> outcome = sA(homeScore, awayScore);

				// Compute new ranking of rA
				float addParam = ceil(K * I * (outcome.first - pA(rA, rB, true)));
				ranking_map[homeId] = rA + addParam;

				// Compute nea ranking of rB
				addParam = ceil(K * I * (outcome.second - pA(rB, rA, false)));
				ranking_map[awayId] = rB + addParam;
			}

			//4. Update and output the rankings
			m_teamRankings = ranking_map;

			utils::saveDataToJason(outjsonFile, m_teamRankings);

			return Error_Code::Success;
		}

		Error_Code WMElo_RankingCalc::compute_and_update(const nlojson & inJson, const char * outjsonFile)
		{
			team_ranking ranking_map = m_teamRankings;

			if (inJson.is_null() || inJson["matches"].is_null())
			{
				return Error_Code::NoRecords;
			}

			//2. Pre-compute all needed parameters
			float K = 15.0f;
			float I = 3.0f;

			//3. Update the rankings
			for (auto i = 0; i < inJson["matches"].size(); i++)
			{
				std::string homeId = inJson["matches"][i]["homeId"];
				std::string awayId = inJson["matches"][i]["awayId"];

				// K = 50 for 11-aside and K = 40 for 7-aside
				if (static_cast<int>(inJson["matches"][i]["type"]) == 11)
					I = 3.0f;
				else if (static_cast<int>(inJson["matches"][i]["type"]) == 7)
					I = 2.0f;

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

				// Get the outcome
				std::pair<float, float> outcome = sA(homeScore, awayScore);

				// Compute new ranking of rA
				float addParam = ceil(K * I * (outcome.first - pA(rA, rB, true)));
				ranking_map[homeId] = rA + addParam;

				// Compute nea ranking of rB
				addParam = ceil(K * I * (outcome.second - pA(rB, rA, false)));
				ranking_map[awayId] = rB + addParam;
			}

			//4. Update and output the rankings
			m_teamRankings = ranking_map;

			utils::saveDataToJason(outjsonFile, m_teamRankings);

			return Error_Code::Success;
		}

		Error_Code WMElo_RankingCalc::compute_and_update(const nlojson & inJson, nlojson & outjson)
		{
			team_ranking ranking_map = m_teamRankings;

			if (inJson.is_null() || inJson["matches"].is_null())
			{
				return Error_Code::NoRecords;
			}

			//2. Pre-compute all needed parameters
			float K = 15.0f;
			float I = 3.0f;

			//3. Update the rankings
			for (auto i = 0; i < inJson["matches"].size(); i++)
			{
				std::string homeId = inJson["matches"][i]["homeId"];
				std::string awayId = inJson["matches"][i]["awayId"];

				// K = 50 for 11-aside and K = 40 for 7-aside
				if (static_cast<int>(inJson["matches"][i]["type"]) == 11)
					I = 3.0f;
				else if (static_cast<int>(inJson["matches"][i]["type"]) == 7)
					I = 2.0f;

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

				// Get the outcome
				std::pair<float, float> outcome = sA(homeScore, awayScore);

				// Compute new ranking of rA
				float addParam = ceil(K * I * (outcome.first - pA(rA, rB, true)));
				ranking_map[homeId] = rA + addParam;

				// Compute nea ranking of rB
				addParam = ceil(K * I * (outcome.second - pA(rB, rA, false)));
				ranking_map[awayId] = rB + addParam;
			}

			//4. Update and output the rankings
			m_teamRankings = ranking_map;
			outjson = ranking_map;

			return Error_Code::Success;
		}

		float WMElo_RankingCalc::pA(const float rA, const float rB, const bool AishomeTeam)
		{
			if (AishomeTeam)
				return (1.0f / (1.0f + pow(10.0f, -(rA + 100.0f - rB))));
			else
				return (1.0f / (1.0f + pow(10.0f, -(rA - rB))));
		}

		std::pair<float, float> WMElo_RankingCalc::sA(const int homeScore, const int awayScore)
		{
			int goalDiff = abs(homeScore - awayScore);
			int col = goalDiff % 6;

			if (homeScore > awayScore)
			{
				int row = awayScore % 5;

				return std::make_pair(1 - m_sA_LUT[row][col], m_sA_LUT[row][col]);
			}
			else
			{
				int row = homeScore % 5;

				return std::make_pair(m_sA_LUT[row][col], 1 - m_sA_LUT[row][col]);
			}
		};

		const std::array<std::array<float, 7>, 6>  WMElo_RankingCalc::m_sA_LUT = {
			{
				{ 0.5f, 0.15f,  0.08f,  0.04f,  0.03f,  0.02f,  0.01f },
				{ 0.5f, 0.16f, 0.089f, 0.048f, 0.037f, 0.026f, 0.015f },
				{ 0.5f, 0.17f, 0.098f, 0.056f, 0.044f, 0.032f,  0.02f },
				{ 0.5f, 0.18f, 0.107f, 0.064f, 0.051f, 0.038f, 0.025f },
				{ 0.5f, 0.19f, 0.116f, 0.072f, 0.058f, 0.044f,  0.03f },
				{ 0.5f, 0.20f, 0.125f, 0.080f, 0.065f,  0.05f, 0.035f }
			}
		};
	} // namespace rankingCalc
} // namespace soccerbro_stats