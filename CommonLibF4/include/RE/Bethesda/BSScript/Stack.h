#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSScript/IMemoryPagePolicy.h"
#include "RE/Bethesda/BSScript/IProfilePolicy.h"
#include "RE/Bethesda/BSScript/IStackCallbackFunctor.h"
#include "RE/Bethesda/BSScript/Object.h"
#include "RE/Bethesda/BSScript/StackFrame.h"
#include "RE/Bethesda/BSScript/Variable.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTObjectArena.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	namespace BSScript
	{
		class IProfilePolicy;
		class IStackCallbackFunctor;
		class MemoryPage;  // stub
		class Object;
		class StackFrame;
		class Variable;

		struct IMemoryPagePolicy;

		namespace Internal
		{
			class CodeTasklet;
		}

		namespace UnlinkedTypes
		{
			struct Object;  // stub
		}

		class Stack :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			enum class StackType;

			enum class FreezeState
			{
				kUnfrozen = 0x0,
				kFreezing = 0x1,
				kFrozen = 0x2
			};

			enum class State
			{
				kRunning = 0x0,
				kFinished = 0x1,
				kWaitingOnMemory = 0x2,
				kWaitingOnLatentFunction = 0x3,
				kWaitingInOtherStackForCall = 0x4,
				kWaitingInOtherStackForReturn = 0x5,
				kWaitingInOtherStackForReturnNoPop = 0x6,
				kRetryReturnNoPop = 0x7,
				kRetryCall = 0x8
			};

			struct MemoryPageData
			{
			public:
				// members
				BSTAutoPointer<MemoryPage> page;                    // 00
				std::uint32_t              availableMemoryInBytes;  // 08
			};
			static_assert(sizeof(MemoryPageData) == 0x10);

			[[nodiscard]] std::uint32_t GetPageForFrame(const StackFrame* a_frame) const
			{
				using func_t = decltype(&Stack::GetPageForFrame);
				static REL::Relocation<func_t> func{ REL::ID(1429302) };
				return func(this, a_frame);
			}

			[[nodiscard]] Variable& GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint)
			{
				using func_t = decltype(&Stack::GetStackFrameVariable);
				static REL::Relocation<func_t> func{ REL::ID(2314681) };
				return func(this, a_frame, a_index, a_pageHint);
			}

			// members
			IMemoryPagePolicy*                      policy;         // 08
			IProfilePolicy*                         profilePolicy;  // 10
			BSTSmallArray<MemoryPageData, 3>        pages;          // 18
			std::uint32_t                           frames;         // 58
			StackFrame*                             top;            // 60
			REX::EnumSet<State, std::int32_t>       state;          // 68
			REX::EnumSet<FreezeState, std::int32_t> freezeState;    // 6C
			Variable                                returnValue;    // 70
			std::uint32_t                           stackID;        // 80
			REX::EnumSet<StackType, std::int32_t>   stackType;      // 84
			BSTSmartPointer<Internal::CodeTasklet>  owningTasklet;  // 88
			BSTSmartPointer<IStackCallbackFunctor>  callback;       // 90
			BSTSmartPointer<Object>                 objToUnbind;    // 98
			BSTSmartPointer<Stack>                  nextStack;      // A0
		};
		static_assert(sizeof(Stack) == 0xA8);
	}
}
