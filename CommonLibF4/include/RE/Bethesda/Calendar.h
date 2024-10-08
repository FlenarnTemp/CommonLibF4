#pragma once

#include "RE/Bethesda/BSTSingleton.h"

namespace RE
{
	class TESGlobal;

	class Calendar :
		public BSTSingletonSDM<Calendar>
	{
	public:
		struct Months
		{
			enum Month
			{
				kJanuary = 0x0,
				kFebruary = 0x1,
				kMarch = 0x2,
				kApril = 0x3,
				kMay = 0x4,
				kJune = 0x5,
				kJuly = 0x6,
				kAugust = 0x7,
				kSeptember = 0x8,
				kOctober = 0x9,
				kNovember = 0xA,
				kDecember = 0xB,
				kTotal = 0xC
			};
		};
		using Month = Months::Month;

		[[nodiscard]] static Calendar* GetSingleton()
		{
			static REL::Relocation<Calendar**> singleton{ REL::ID(2689092) };
			return *singleton;
		}

		[[nodiscard]] float         GetHoursPassed() const noexcept;
		[[nodiscard]] std::uint32_t GetMonth() const noexcept;

		// members
		TESGlobal*    gameYear;         // 08
		TESGlobal*    gameMonth;        // 10
		TESGlobal*    gameDay;          // 18
		TESGlobal*    gameHour;         // 20
		TESGlobal*    gameDaysPassed;   // 28
		TESGlobal*    timeScale;        // 30
		std::uint32_t midnightsPassed;  // 38
		float         rawDaysPassed;    // 3C
	};
	static_assert(sizeof(Calendar) == 0x40);
}
