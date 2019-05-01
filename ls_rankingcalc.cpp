#include "ls_rankingcalc.h"

#include <set>
#include <mkl.h>

namespace soccerbro_stats {
	namespace rankingCalc
	{
		LS_RankingCalc::~LS_RankingCalc()
		{}

		Error_Code LS_RankingCalc::compute_and_update(const char* injsonFile,
			const char* outjsonFile)
		{
			// 1. clear the map & team set
			m_teamRankings.clear();
			m_teamSet.clear();

			// 2. Load data
			nlojson jsonHandle = utils::loadDataFromJason(injsonFile);

			if (jsonHandle["matches"].is_null())
			{
				std::cerr << injsonFile << " contains no matches at all!" << std::endl;
				return Error_Code::NoRecords;
			}

			// 3. Construct the Ax = b linear system
			std::vector<float> A;
			std::vector<float> b;

			constructSystem(jsonHandle, A, b);

			// For debug
			/*for (int i = 0; i < m_iNumTeams; i++)
			{
			for (int j = 0; j < m_iNumTeams; j++)
			{
			std::cout << A[i*m_iNumTeams + j] << ",";
			}
			std::cout << b[i] << std::endl;
			}*/

			// 4. Solve the linear A*X = b system using MKL LAPACK routine
			MKL_INT *ipiv = (MKL_INT*)malloc(sizeof(MKL_INT)*m_iNumTeams);

			int info = LAPACKE_sgesv(LAPACK_ROW_MAJOR,
				m_iNumTeams,
				1,
				A.data(),
				m_iNumTeams,
				ipiv,
				b.data(),
				1);
			if (info > 0)
			{
				printf("The diagonal element of the triangular factor of A,\n");
				printf("U(%i,%i) is zero, so that A is singular;\n", info, info);
				printf("the solution could not be computed.\n");

				return Error_Code::Invalid;
			}

			free(ipiv); ipiv = nullptr;

			// 5. Scale the results from [-,+] to [1500]
			// Get the min ranking number
			float min_rank = 10000.0f;
			for (const auto&i : b)
			{
				if (i < min_rank)
					min_rank = i;
			}

			// 6. Update the ranking 
			team_ranking ranking_map;
			auto it = m_teamSet.begin();
			for (auto i = 0; i < b.size(); i++)
			{
				b[i] = ceil(sqrt((b[i] - min_rank) * 1000 + 1000) * 30);
				ranking_map.insert(std::make_pair(*it, b[i]));
				++it;
			}

			// 7. Output to json file
			m_teamRankings = ranking_map;
			
			utils::saveDataToJason(outjsonFile, m_teamRankings);

			return Error_Code::Success;
		}

		Error_Code LS_RankingCalc::compute_and_update(const nlojson & jsonHandle, const char * outjsonFile)
		{
			// 1. clear the map & team set
			m_teamRankings.clear();
			m_teamSet.clear();

			// 2. Load data
			if (jsonHandle["matches"].is_null())
			{
				std::cerr << "json contains no matches at all!" << std::endl;
				return Error_Code::NoRecords;
			}

			// 3. Construct the Ax = b linear system
			std::vector<float> A;
			std::vector<float> b;

			constructSystem(jsonHandle, A, b);

			// 4. Solve the linear A*X = b system using MKL LAPACK routine
			MKL_INT *ipiv = (MKL_INT*)malloc(sizeof(MKL_INT)*m_iNumTeams);

			int info = LAPACKE_sgesv(LAPACK_ROW_MAJOR,
				m_iNumTeams,
				1,
				A.data(),
				m_iNumTeams,
				ipiv,
				b.data(),
				1);
			if (info > 0)
			{
				printf("The diagonal element of the triangular factor of A,\n");
				printf("U(%i,%i) is zero, so that A is singular;\n", info, info);
				printf("the solution could not be computed.\n");

				return Error_Code::Invalid;
			}

			free(ipiv); ipiv = nullptr;

			// 5. Scale the results from [-,+] to [1500]
			// Get the min ranking number
			float min_rank = 10000.0f;
			for (const auto&i : b)
			{
				if (i < min_rank)
					min_rank = i;
			}

			// 6. Update the ranking 
			team_ranking ranking_map;
			auto it = m_teamSet.begin();
			for (auto i = 0; i < b.size(); i++)
			{
				b[i] = ceil(sqrt((b[i] - min_rank) * 1000 + 1000) * 30);
				ranking_map.insert(std::make_pair(*it, b[i]));
				++it;
			}

			// 7. Output to json file
			m_teamRankings = ranking_map;

			utils::saveDataToJason(outjsonFile, m_teamRankings);

			return Error_Code::Success;
		}

		Error_Code LS_RankingCalc::compute_and_update(const nlojson & jsonHandle, nlojson & outjson)
		{
			// 1. clear the map & team set
			m_teamRankings.clear();
			m_teamSet.clear();

			// 2. Load data
			if (jsonHandle["matches"].is_null())
			{
				std::cerr << "json contains no matches at all!" << std::endl;
				return Error_Code::NoRecords;
			}

			// 3. Construct the Ax = b linear system
			std::vector<float> A;
			std::vector<float> b;

			constructSystem(jsonHandle, A, b);

			// 4. Solve the linear A*X = b system using MKL LAPACK routine
			MKL_INT *ipiv = (MKL_INT*)malloc(sizeof(MKL_INT)*m_iNumTeams);

			int info = LAPACKE_sgesv(LAPACK_ROW_MAJOR,
				m_iNumTeams,
				1,
				A.data(),
				m_iNumTeams,
				ipiv,
				b.data(),
				1);
			if (info > 0)
			{
				printf("The diagonal element of the triangular factor of A,\n");
				printf("U(%i,%i) is zero, so that A is singular;\n", info, info);
				printf("the solution could not be computed.\n");

				return Error_Code::Invalid;
			}

			free(ipiv); ipiv = nullptr;

			// 5. Scale the results from [-,+] to [1500]
			// Get the min ranking number
			float min_rank = 10000.0f;
			for (const auto&i : b)
			{
				if (i < min_rank)
					min_rank = i;
			}

			// 6. Update the ranking 
			team_ranking ranking_map;
			auto it = m_teamSet.begin();
			for (auto i = 0; i < b.size(); i++)
			{
				b[i] = ceil(sqrt((b[i] - min_rank) * 1000 + 1000) * 30);
				ranking_map.insert(std::make_pair(*it, b[i]));
				++it;
			}

			// 7. Output to json file
			m_teamRankings = ranking_map;
			outjson = ranking_map;

			return Error_Code::Success;
		}
		
		Error_Code LS_RankingCalc::initialize(const nlojson& initialRanking)
		{
			return Error_Code::Success;
		}

		void LS_RankingCalc::constructSystem(const nlojson& jsonHandle, std::vector<float>& A, std::vector<float>& b)
		{
			versus_map versusNum;		// < <ti, tj>, number of mathes> 
			team_games_scores_map teamGamesScoresNum;

			/* Begin to calculat&construct the linear system */
			// 1. First read of json to get G1, G2, ..., Gn, pd1, pd2, ..., pdn, teamIDSet
			for (int i = 0; i < jsonHandle["matches"].size(); i++)
			{
				// Get string team id from mathes
				std::string homeId = jsonHandle["matches"][i]["homeId"];
				std::string awayId = jsonHandle["matches"][i]["awayId"];

				m_teamSet.insert(homeId);
				m_teamSet.insert(awayId);

				// Get score diff from home&away scores
				int homeScore = jsonHandle["matches"][i]["homeScore"];
				int awayScore = jsonHandle["matches"][i]["awayScore"];
				int home_awayScore = homeScore - awayScore;

				// Accumulate the total number of games played by each team and 
				// save them to the team_map object
				auto it = teamGamesScoresNum.find(homeId);
				if (it == teamGamesScoresNum.end())
				{
					teamGamesScoresNum.insert(std::make_pair(homeId, std::make_pair(1, home_awayScore)));
				}
				else
				{
					it->second.first++;
					it->second.second += home_awayScore;
				}

				it = teamGamesScoresNum.find(awayId);
				if (it == teamGamesScoresNum.end())
				{
					teamGamesScoresNum.insert(std::make_pair(awayId, std::make_pair(1, -home_awayScore)));
				}
				else
				{
					it->second.first++;
					it->second.second -= home_awayScore;
				}
			}

			// 2. Initialize the versus_map with 0's 
			for (int i = 0; i < teamGamesScoresNum.size(); i++)
			{
				auto it = teamGamesScoresNum.begin();
				std::advance(it, i);

				std::string initStr = it->first;

				while (++it != teamGamesScoresNum.end())
				{
					versusNum.insert(std::make_pair(std::make_pair(initStr, it->first), 0));
				}
			}

			// 3. Second read of json to get the number of versus games
			for (int i = 0; i < jsonHandle["matches"].size(); i++)
			{
				// Get string team id from mathes
				std::string homeId = jsonHandle["matches"][i]["homeId"];
				std::string awayId = jsonHandle["matches"][i]["awayId"];

				auto it1 = versusNum.find(std::make_pair(homeId, awayId));
				auto it2 = versusNum.find(std::make_pair(awayId, homeId));

				if (it1 != versusNum.end())
				{
					it1->second++;
				}
				else if (it2 != versusNum.end())
				{
					it2->second++;
				}
			}
			m_iNumTeams = static_cast<int>(teamGamesScoresNum.size());

			// 4. construct the A and b
			A.resize(m_iNumTeams*m_iNumTeams, 0);
			b.resize(m_iNumTeams, 0);

			auto itV = versusNum.begin();
			auto it = teamGamesScoresNum.begin();

			for (int i = 0; i < m_iNumTeams; i++)
			{
				for (int j = i; j < m_iNumTeams; j++)
				{
					if (i == j)
					{
						// Diagnals of A and vector b					
						A[i*m_iNumTeams + j] = static_cast<float>(it->second.first);
						b[i] = static_cast<float>(it->second.second);
						++it;
					}
					else
					{
						A[i*m_iNumTeams + j] = -static_cast<float>(itV->second);
						A[j*m_iNumTeams + i] = -static_cast<float>(itV->second);
						++itV;
					}

				}

				if (i == m_iNumTeams - 1)
				{
					for (int j = 0; j < m_iNumTeams; j++)
					{
						A[i*m_iNumTeams + j] = 1;
					}
					b[i] = 0;
				}
			}
			// For Debug
			/*for (auto it : teamGamesScoresNum)
			{
				std::cout << it.first << ", " << it.second.first << ", " << it.second.second << std::endl;
			}

			for (auto it : versusNum)
			{
				std::cout << it.first.first << ", " << it.first.second << ", " << it.second << std::endl;
			}

			std::cout << teamGamesScoresNum.size() << std::endl;
			std::cout << versusNum.size() << std::endl;*/
		}
	} // namespace rankingCalc
} // namespace soccerbro_stats