#pragma once 

namespace Core
{
	class CoreFunc {
	public:
		template<class T, class... Args>
			requires CheckToSameMethodArgs<T, Args...>
		static SHPTR<T> Create(Args&&... args)
		{
			SHPTR<T> new_generator = MakeShared<T>(std::forward<Args>(args)...);
			if (EErrorState::None != new_generator->NativeConstruct())
			{

			}
			return new_generator;
		}

		template<class T>
		static uint64 GetTypeSize()
		{
			static constexpr uint64 value = sizeof(T);
			return value;
		}

		template<class T>
		static void ClearMemory(T* ptr, uint64 size) {
			::memset(ptr, 0, size);
		}

		template<typename T>
		static bool CAS(T& target, T expected, T desired)
		{
			int64 exp = reinterpret_cast<int64>(&expected);
			int64 des = reinterpret_cast<int64>(&desired);

			return std::atomic_compare_exchange_strong(
				reinterpret_cast<std::atomic<int64>*>(&target),
				&exp,
				des
			);
		}

		template<typename T>
		static bool CAS(std::atomic<T>& target, T desired)
		{
			T exp = target.load();
			return target.compare_exchange_strong(exp, desired);
		}


		template<typename T>
		static void AtomicChangeValue(T& target, T desired)
		{
			while (true)
			{
				T exp = target;
				if (true == CAS(target, exp, desired))
					return;
			}
		}

		template<typename T>
		static void AtomicChangeValue(std::atomic<T>& target, T desired)
		{
			while (true)
			{
				if (true == CAS(target, desired))
					return ;
			}
		}


		template<typename T>
		static bool CAS_POINTER(T* target, T expected, T desired)
		{
			int64 expected_val = reinterpret_cast<int64>(expected);
			int64 desired_val = reinterpret_cast<int64>(desired);
			return std::atomic_compare_exchange_strong(
				reinterpret_cast<std::atomic<int64>*>(target),
				&expected_val,
				desired_val);
		}

		static uint64 CreateCurrentTime();

		static String FormatTimeFromTime(uint64 secondsSinceEpoch);

		static void OutSystemErrorMsg(const std::exception& ex, const char* file, int line, const char* function);

		static String MakeSystemErrorMsg(const std::exception& ex, const char* file, int line, const char* function);
	};
}
