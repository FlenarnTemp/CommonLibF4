#include "API.h"

#include "F4SE/Interfaces.h"
#include "F4SE/Logger.h"
#include "F4SE/Trampoline.h"

namespace F4SE
{
	namespace detail
	{
		struct APIStorage
		{
		public:
			APIStorage(const APIStorage&) = delete;
			APIStorage(APIStorage&&) = delete;

			APIStorage& operator=(const APIStorage&) = delete;
			APIStorage& operator=(APIStorage&&) = delete;

			[[nodiscard]] static APIStorage& get() noexcept
			{
				static APIStorage singleton;
				return singleton;
			}

			PluginHandle pluginHandle{ static_cast<PluginHandle>(-1) };
			std::uint32_t releaseIndex{ 0 };

			MessagingInterface* messagingInterface{ nullptr };
			ScaleformInterface* scaleformInterface{ nullptr };
			PapyrusInterface* papyrusInterface{ nullptr };
			SerializationInterface* serializationInterface{ nullptr };
			TaskInterface* taskInterface{ nullptr };
			ObjectInterface* objectInterface{ nullptr };
			//TrampolineInterface* trampolineInterface{ nullptr };

		private:
			APIStorage() noexcept = default;
			~APIStorage() noexcept = default;
		};

		template <class T>
		T* QueryInterface(const LoadInterface* a_intfc, std::uint32_t a_id) noexcept
		{
			auto result = static_cast<T*>(a_intfc->QueryInterface(a_id));
			if (result && result->Version() > T::kVersion) {
				log::warn("interface definition is out of date");
			}
			return result;
		}
	}

	void Init(const LoadInterface* a_intfc) noexcept
	{
		if (!a_intfc) {
			stl::report_and_fail("interface is null"sv);
		}

		(void)REL::Module::get();
		(void)REL::IDDatabase::get();

		auto& storage = detail::APIStorage::get();
		const auto& intfc = *a_intfc;

		storage.pluginHandle = intfc.GetPluginHandle();
		storage.releaseIndex = intfc.GetReleaseIndex();

		storage.messagingInterface = detail::QueryInterface<MessagingInterface>(a_intfc, LoadInterface::kMessaging);
		storage.scaleformInterface = detail::QueryInterface<ScaleformInterface>(a_intfc, LoadInterface::kScaleform);
		storage.papyrusInterface = detail::QueryInterface<PapyrusInterface>(a_intfc, LoadInterface::kPapyrus);
		storage.serializationInterface = detail::QueryInterface<SerializationInterface>(a_intfc, LoadInterface::kSerialization);
		storage.taskInterface = detail::QueryInterface<TaskInterface>(a_intfc, LoadInterface::kTask);
		storage.objectInterface = detail::QueryInterface<ObjectInterface>(a_intfc, LoadInterface::kObject);
		//storage.trampolineInterface = detail::QueryInterface<TrampolineInterface>(a_intfc, LoadInterface::kTrampoline);
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return detail::APIStorage::get().pluginHandle;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return detail::APIStorage::get().releaseIndex;
	}

	const MessagingInterface* GetMessagingInterface() noexcept
	{
		return detail::APIStorage::get().messagingInterface;
	}

	const ScaleformInterface* GetScaleformInterface() noexcept
	{
		return detail::APIStorage::get().scaleformInterface;
	}

	const PapyrusInterface* GetPapyrusInterface() noexcept
	{
		return detail::APIStorage::get().papyrusInterface;
	}

	const SerializationInterface* GetSerializationInterface() noexcept
	{
		return detail::APIStorage::get().serializationInterface;
	}

	const TaskInterface* GetTaskInterface() noexcept
	{
		return detail::APIStorage::get().taskInterface;
	}

	const ObjectInterface* GetObjectInterface() noexcept
	{
		return detail::APIStorage::get().objectInterface;
	}

#if 0
	const TrampolineInterface* GetTrampolineInterface() noexcept
	{
		return detail::APIStorage::get().trampolineInterface;
	}
#endif

	Trampoline& GetTrampoline() noexcept
	{
		static Trampoline trampoline;
		return trampoline;
	}

	void AllocTrampoline(std::size_t a_size) noexcept
	{
		auto& trampoline = GetTrampoline();
#if 0
		const auto interface = GetTrampolineInterface();
		const auto mem = interface ? interface->AllocateFromBranchPool(a_size) : nullptr;
		if (mem) {
			trampoline.set_trampoline(mem, a_size);
		} else {
			trampoline.create(a_size);
		}
#else
		trampoline.create(a_size);
#endif
	}
}
