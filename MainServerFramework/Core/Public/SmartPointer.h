#pragma once

SPACE_BEGIN(Core)

template <class T>
class ASharedPtr;

template<class T>
class AWeakPtr;

template<class T>
class AEnableSharedFromThis;

template<class T, typename = void>
struct EnableShared : std::false_type{};

template<class T>
struct EnableShared<T, std::void_t<typename T::Enable_Shared_From_This>>
	: std::is_convertible<std::remove_cv_t<T>*, typename T::Enable_Shared_From_This*>::type
{};

template<class T>
class ARefCounter {

	template<class T, class ...Args>
	friend ASharedPtr<T> MakeShared(Args&&... _args);

	template<class T, class U>
	friend ASharedPtr<T> static_shared_cast(const ASharedPtr<U>& _rhs);

	template<class T, class U>
	friend ASharedPtr<T> dynamic_shared_cast(const ASharedPtr<U>& _rhs);

public:
	ARefCounter() : _Pointer{ nullptr }, _iStrongRefCounter{ 0 }, _iWeakRefCounter{ 0 } {}
	ARefCounter(T* ptr)	: _Pointer(ptr), _iStrongRefCounter(1), _iWeakRefCounter(1){}
	~ARefCounter() { }

	ARefCounter<T>* AddRefStrong() {
		_iStrongRefCounter.fetch_add(1);
		return this;
	}

	int64 ReleaseRefStrong() {
		int64 refCount = _iStrongRefCounter.fetch_sub(1);
		if (refCount <= 0)
		{
			AMemoryAdiminstor::Release(_Pointer);
			AMemoryAdiminstor::Release(this);
		}
		return refCount;
	}

	ARefCounter<T>* AddRefWeak() {
		_iWeakRefCounter.fetch_add(1);
		return this;
	}

	int64 ReleaseRefWeak() {
		return  _iWeakRefCounter.fetch_sub(1);
	}

	T* get() const { return _iStrongRefCounter; }
	T** getAddressof() const { return &_iStrongRefCounter; }

	void SetShared(T* shared) { _iStrongRefCounter = shared; }

	int64 use_count() { return _iStrongRefCounter.load(); }
private:
	Atomic_int64		_iStrongRefCounter;
	Atomic_int64		_iWeakRefCounter;
	mutable T*			_Pointer;
};

template <class T> 
class ASharedPtr {
	using REFCOUNTER = ARefCounter<T>*;;
	friend  class AEnableSharedFromThis<T>;
	friend class AWeakPtr<T>;

	template<class T, class ...Args>
	friend ASharedPtr<T> MakeShared(Args&&... _args);
	template<class T, class U>
	friend ASharedPtr<T> static_shared_cast(const ASharedPtr<U>& _rhs);
	template<class T, class U>
	friend ASharedPtr<T> dynamic_shared_cast(const ASharedPtr<U>& _rhs);

public:
	ASharedPtr() : _RefCounter{ nullptr } {}
	explicit ASharedPtr(ARefCounter<T>* ref) : _RefCounter{ ref } {}
	ASharedPtr(std::nullptr_t) : _RefCounter{ nullptr } {}
	ASharedPtr(const ASharedPtr& rhs) : _RefCounter{ nullptr } { Move(rhs); }
	ASharedPtr(ASharedPtr&& rhs) noexcept : _RefCounter{ rhs._RefCounter } { rhs._RefCounter = nullptr; }
	~ASharedPtr()
	{
		reset();
	}

	ASharedPtr& operator=(std::nullptr_t)
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (nullptr == ref)
				return *this;

			if (true == CAS_POINTER(&_RefCounter, ref, nullptr))
				return *this;
		}
		return *this;
	}
	ASharedPtr& operator=(const ASharedPtr& rhs)	noexcept
	{
		REFCOUNTER old_ref{ nullptr }, curr_ref{ nullptr };

		while (true)
		{
			old_ref = _RefCounter;
			curr_ref = rhs.AddShared();
			if (nullptr == old_ref)
			{
				if (true == CAS_POINTER(&_RefCounter, old_ref, nullptr))
				{
					return *this;
				}
				continue;
			}

			if (curr_ref == old_ref)
			{
				Release(curr_ref);
				return *this;
			}

			if (true == CAS_POINTER(&_RefCounter, old_ref, nullptr))
			{
				if (nullptr != old_ref)
					Release(old_ref);
				return *this;
			}
			Release(curr_ref);
		}
	}

	ASharedPtr& operator=(ASharedPtr&& rhs) noexcept 
	{
		REFCOUNTER old_ref{ nullptr }, curr_ref{ nullptr };

		while (true)
		{
			old_ref = _RefCounter;
			curr_ref = rhs._RefCounter;
			if (nullptr == old_ref)
			{
				if (true == CAS_POINTER(&_RefCounter, old_ref, nullptr))
				{
					return *this;
				}
				continue;
			}

			if (curr_ref == old_ref)
			{
				rhs._RefCounter = nullptr;
				return *this;
			}

			if (true == CAS_POINTER(&_RefCounter, old_ref, nullptr))
			{
				rhs._RefCounter = nullptr;
				return *this;
			}
		}
	}

	T* operator->() const { return get(); }
	T& operator*() const
	{
		T* p = get();
		if (p == nullptr)
			return T{};
		return *p;
	}

	bool operator==(std::nullptr_t) const { return _RefCounter == nullptr; }
	bool operator!=(std::nullptr_t) const { return _RefCounter != nullptr; }
	bool operator==(const ASharedPtr& other) const { return _RefCounter == other._RefCounter; }
	bool operator!=(const ASharedPtr& other) const { return _RefCounter != other._RefCounter; }
	template<class U>
	bool operator==(const U* ptr) const
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (nullptr == ref)
				return false;

			return ref->get() == ptr;
		}
		return false;
	}
	template<class U>
	bool operator!=(const U* ptr) const { return !(*this == ptr); }

	ASharedPtr<T>* operator&() { return this; }
	T* get() const
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (nullptr == ref)
				return nullptr;

			return ref->get();
		}
		return nullptr;
	}
	T** getAddressof() const
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (nullptr == ref)
				return nullptr;

			return ref->getAddressof();
		}
		return nullptr;
	}
	void reset()
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (nullptr == ref)
				return;

			Release(ref);
		}
	}
	int64 use_count() const
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (nullptr == ref)
				return 0;

			return ref->use_count();
		}
		return 0;
	}
	explicit operator bool() const
	{
		REFCOUNTER currptr = _RefCounter;
		if (nullptr != currptr)
			if (currptr->use_count() > 0)
				return true;

		return false;
	}
private:
	REFCOUNTER AddShared() const
	{
		REFCOUNTER old{ nullptr }, curr{ nullptr };
		while (true)
		{
			old = _RefCounter;
			if (nullptr == old)
				return nullptr;

			// curr이 비어있으면 처음부터 다시한다. 
			curr = old->AddRefStrong();

			if (old == curr)
				return curr;
			
			if (curr != nullptr)
				curr->ReleaseRefStrong();
		}
		return nullptr;
	}
	REFCOUNTER AddWeak() const
	{
		REFCOUNTER old{ nullptr }, curr{ nullptr };
		while (true)
		{
			old = _RefCounter;
			if (nullptr == old)
				return nullptr;

			// curr이 비어있으면 처음부터 다시한다. 
			curr = old->AddRefWeak();

			if (old == curr)
				return curr;

			if (curr != nullptr)
				curr->ReleaseRefWeak();
		}
		return nullptr;
	}

	void Release(REFCOUNTER& ref)
	{
		if (nullptr != ref)
		{
			int64 value = ref->ReleaseRefStrong();
			if (value < 0)
			{
				while (true)
				{
					REFCOUNTER curr_ref = ref;
					if (true == CAS_POINTER(&ref, curr_ref, nullptr))
						return;
				}
			}
		}
	}

	bool CAS_POINTER(REFCOUNTER* target, REFCOUNTER expected, REFCOUNTER desired) const
	{
		int64 old_value = reinterpret_cast<int64>(expected);
		int64 new_value = reinterpret_cast<int64>(desired);
		return std::atomic_compare_exchange_strong(reinterpret_cast<Atomic_int64*>(target), &old_value, new_value);
	}

	void SetEnableShared(T* ptr, REFCOUNTER new_ctr)
	{
		_RefCounter = new_ctr;
		Enable_shared_from_this(ptr, std::bool_constant<std::conjunction_v<EnableShared<T>>>{});
	}

	void Enable_shared_from_this(T* _ptr, std::true_type) { _ptr->SetSharedFromThis(*this); }
	void Enable_shared_from_this(T* _ptr, std::false_type) {}
private:
	mutable REFCOUNTER		_RefCounter;
};

template<class T>
bool operator==(nullptr_t lhs, const ASharedPtr<T>& rhs) { return lhs == rhs.get(); }
template<class T>
bool operator!=(nullptr_t lhs, const ASharedPtr<T>& rhs) { return lhs != rhs.get(); }
template<class T, class U>
bool operator==(U* lhs, const ASharedPtr<T>& rhs) { return lhs == rhs.get(); }
template<class T, class U>
bool operator!=(U* lhs, const ASharedPtr<T>& rhs) { return lhs != rhs.get(); }


template<class T>
class AWeakPtr {
	using REFCOUNTER = ARefCounter<T>*;
	friend class ASharedPtr<T>;

public:
	AWeakPtr() : _RefCounter{ nullptr } {}
	AWeakPtr(std::nullptr_t) : _RefCounter{ nullptr } {}
	AWeakPtr(const AWeakPtr& rhs) : _RefCounter{ rhs.AddWeak() } {}
	AWeakPtr(AWeakPtr&& rhs) noexcept : _RefCounter{ rhs._RefCounter } { rhs._RefCounter = nullptr; }
	AWeakPtr(const ASharedPtr<T>& rhs) : _RefCounter{ rhs.AddWeak() } {}
	~AWeakPtr() { reset(); }

public:
	AWeakPtr& operator=(std::nullptr_t)
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (ref == nullptr)
				return *this;

			if (CAS_POINTER(&_RefCounter, ref, nullptr))
			{
				Release(ref);
				return *this;
			}
		}
	}

	AWeakPtr& operator=(const AWeakPtr& rhs)
	{
		while (true)
		{
			REFCOUNTER old_ref = _RefCounter;
			REFCOUNTER new_ref = rhs.AddWeak();

			if (old_ref == new_ref)
			{
				Release(new_ref);
				return *this;
			}

			if (CAS_POINTER(_RefCounter, old_ref, new_ref))
			{
				if (old_ref)
					Release(old_ref);
				return *this;
			}
			Release(new_ref);
		}
	}

	AWeakPtr& operator=(const ASharedPtr<T>& rhs)
	{
		while (true)
		{
			REFCOUNTER old_ref = _RefCounter;
			REFCOUNTER new_ref = rhs.AddWeak();

			if (old_ref == new_ref)
			{
				Release(new_ref);
				return *this;
			}

			if (CAS_POINTER(&_RefCounter, old_ref, new_ref))
			{
				if (old_ref)
					Release(old_ref);
				return *this;
			}
			Release(new_ref);
		}
	}

	bool operator==(std::nullptr_t) const { return _RefCounter == nullptr; }
	bool operator!=(std::nullptr_t) const { return _RefCounter != nullptr; }

	template<class U>
	bool operator==(const ASharedPtr<U>& rhs) const
	{
		return _RefCounter == rhs._RefCounter;
	}

	template<class U>
	bool operator!=(const ASharedPtr<U>& rhs) const
	{
		return _RefCounter != rhs._RefCounter;
	}

	ASharedPtr<T> lock() const
	{
		if (_RefCounter == nullptr)
			return nullptr;
		return ASharedPtr<T>(*this);
	}

	void reset()
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (ref == nullptr)
				return;

			if (CAS_POINTER(&_RefCounter, ref, nullptr))
			{
				Release(ref);
				return;
			}
		}
	}

	int64 use_count() const
	{
		if (_RefCounter == nullptr)
			return 0;
		return _RefCounter->use_count();
	}

	explicit operator bool() const
	{
		if (_RefCounter != nullptr && _RefCounter->use_count() > 0)
			return true;
		return false;
	}

private:
	REFCOUNTER AddWeak() const
	{
		while (true)
		{
			REFCOUNTER ref = _RefCounter;
			if (ref == nullptr)
				return nullptr;

			REFCOUNTER new_ref = ref->AddRefWeak();

			if (ref == new_ref)
				return new_ref;

			if (new_ref != nullptr)
				new_ref->ReleaseRefWeak();
		}
		return nullptr;
	}

	void Release(REFCOUNTER& ref)
	{
		if (ref != nullptr)
		{
			int64 count = ref->ReleaseRefWeak();
			if (count <= 0)
				_RefCounter = nullptr;
		}
	}

	bool CAS_POINTER(REFCOUNTER* target, REFCOUNTER expected, REFCOUNTER desired) const
	{
		int64 expected_val = reinterpret_cast<int64>(expected);
		int64 desired_val = reinterpret_cast<int64>(desired);
		return std::atomic_compare_exchange_strong(
			reinterpret_cast<std::atomic<int64>*>(target),
			&expected_val,
			desired_val);
	}
private:
	mutable REFCOUNTER _RefCounter;
};



template<class T>
class AEnableSharedFromThis abstract {
	friend  class ASharedPtr<T>;
	friend  class ARefCounter<T>;
protected:
	AEnableSharedFromThis()
		: _Wptr(nullptr)
	{
	}

	AEnableSharedFromThis(const AEnableSharedFromThis& other)
		: _Wptr(nullptr)
	{
	}

	AEnableSharedFromThis& operator=(const AEnableSharedFromThis&){
		return (*this);
	}

	~AEnableSharedFromThis() = default;
protected:
	using Enable_Shared_From_This = AEnableSharedFromThis;

	ASharedPtr<T> shared_from_this()
	{
		return (ASharedPtr<T>(_Wptr));
	}

	AWeakPtr<T> weak_from_this()
	{
		return _Wptr;
	}

	void SetSharedFromThis(const ASharedPtr<T>& ptr) { _Wptr = ptr; }
private:
	AWeakPtr<T> _Wptr;
};

template<class T, class ...Args>
ASharedPtr<T> MakeShared(Args&&... _args)
{
	// 배열 타입에 대한 잘못된 사용 방지
	static_assert(!std::is_array<T>::value,
		"MakeShared: T must not be an array type");
	// 전달된 인자로 T를 생성할 수 있는지 검증
	static_assert(std::is_constructible<T, Args&&...>::value,
		"MakeShared: Cannot construct T with given arguments");

	T* ptr = mnew<T>(std::forward<Args>(_args)...);
	ARefCounter<T>* pRefCounter = mnew<ARefCounter<T>>(ptr);

	ASharedPtr<T> SharedPtr;
	SharedPtr.SetEnableShared(ptr, pRefCounter);
	return SharedPtr;
}


template<class T, class U>
static ASharedPtr<T> static_shared_cast(const ASharedPtr<U>& rhs)
{
	assert(rhs._RefCounter == nullptr);
	std::atomic_thread_fence(std::memory_order_seq_cst);
	while (true)
	{
		// U* → T*로 변환
		T* pCast = static_cast<T*>(rhs.Get());

		// 기존 레퍼런스 카운터를 T 타입에 맞춰 공유 (구조체가 동일하다는 전제 필요)
		ARefCounter<T>* pCounter = reinterpret_cast<ARefCounter<T>*>(rhs._RefCounter);

		if (nullptr != pCounter && nullptr != pCast)
		{
			pCounter->AddRefStrong(); // 참조 카운트 증가
			return ASharedPtr<T>(pCast, pCounter);
		}
	}
	return nullptr;
}
template<class T, class U>
static ASharedPtr<T> dynamic_shared_cast(const ASharedPtr<U>& rhs)
{
	assert(rhs._RefCounter == nullptr);
	std::atomic_thread_fence(std::memory_order_seq_cst);
	while (true)
	{
		// U* → T*로 변환
		T* pCast = dynamic_cast<T*>(rhs.Get());

		// 기존 레퍼런스 카운터를 T 타입에 맞춰 공유 (구조체가 동일하다는 전제 필요)
		ARefCounter<T>* pCounter = reinterpret_cast<ARefCounter<T>*>(rhs._RefCounter);

		if (nullptr != pCounter && nullptr != pCast)
		{
			pCounter->AddRefStrong(); // 참조 카운트 증가
			return ASharedPtr<T>(pCast, pCounter);
		}
	}
	return nullptr;
}

template<class T>
using SHPTR = ASharedPtr<T>;

template<class T>
using CSHPTR = const SHPTR<T>;

template<class T>
using CSHPTRREF = const SHPTR<T>&;

template<class T>
using WKPTR = AWeakPtr<T>;

template<class T>
using CWKPTR = const WKPTR<T>;

template<class T>
using CWKPTRREF = const WKPTR<T>&;

SPACE_END

namespace std
{
	template <typename T>
	struct hash<Core::ASharedPtr<T>> {
		size_t operator()(const Core::ASharedPtr<T>& ptr) const {
			return std::hash<T*>()(ptr.get());
		}
	};

	template <typename T>
	struct equal_to<Core::ASharedPtr<T>> {
		bool operator()(const Core::ASharedPtr<T>& lhs, const Core::ASharedPtr<T>& rhs) const {
			return lhs.get() == rhs.get();
		}
	};

	template <typename T>
	struct less<Core::ASharedPtr<T>> {
		bool operator()(const Core::ASharedPtr<T>& lhs, Core::ASharedPtr<T>& rhs) const {
			return lhs.get() < rhs.get();
		}
	};

	template <typename T>
	struct less_equal<Core::ASharedPtr<T>> {
		bool operator()(const Core::ASharedPtr<T>& lhs, Core::ASharedPtr<T>& rhs) const {
			return lhs.get() <= rhs.get();
		}
	};
}