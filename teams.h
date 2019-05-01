#ifndef TEAMS_H
#define TEAMS_H

#include <string>

// Currently not in use!
namespace soccerbro_stats {
	namespace rankingCalc
	{
		//@brief: class holding team id and its ranking with overloaded binary
		//        operators
		//@Explaination of operators:
		//	t1 != (==) t2: t1.m_id != (==) t2.m_id
		//	t1 > (<) t2: t1.m_iranking > (<) t2.m_iranking;
		class SOCCERBRO_DLL_EXPORTS Teams
		{
		public:
			Teams() = delete;	// Mark the default constructor as deleted func
			Teams(const Teams&) = default;
			Teams(Teams&&) = default;
			Teams& operator=(const Teams&) = default;
			~Teams() = default;

			Teams(std::string id, int ranking = 0)
				: m_id(id)
				, m_iranking(ranking)
			{}

			inline bool operator!=(const Teams& t) { return m_id != t.m_id; }
			inline bool operator==(const Teams& t) { return m_id == t.m_id; }
			inline bool operator<(const Teams& t) { return m_iranking < t.m_iranking; }
			inline bool operator>(const Teams& t) { return m_iranking > t.m_iranking; }

			/* Getters & Setters */
			inline int ranking() const { return m_iranking; }
			inline std::string id() const { return m_id; }
			inline void update(int ranking) { m_iranking = ranking; }

		private:
			int m_iranking;			// ranking can be updated
			const std::string m_id;	// This should be immutable once constructed
		};

	} // namespace rankingCalc
} // namespace soccerbro_stats
#endif // !TEAMS_H
