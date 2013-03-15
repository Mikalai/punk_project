#ifndef _H_PUNK_ATOMICINT
#define _H_PUNK_ATOMICINT

#include <atomic>


namespace System {


class AtomicInt
{
public:
	inline AtomicInt(int value = 0) : m_atomic(value) {}
	inline AtomicInt(const AtomicInt &other) : m_atomic(other.m_atomic.load(std::memory_order_relaxed)) {}

	inline AtomicInt &operator=(const AtomicInt &other);
	inline AtomicInt &operator=(int value);

	inline bool Ref();
	inline bool Deref();

	inline int FetchAndAddAcquire(int valueToAdd);
	inline int FetchAndAddOrdered(int valueToAdd);
	inline int FetchAndAddRelaxed(int valueToAdd);
	inline int FetchAndAddRelease(int valueToAdd);
	inline int FetchAndStoreAcquire(int newValue);
	inline int FetchAndStoreOrdered(int newValue);
	inline int FetchAndStoreRelaxed(int newValue);
	inline int FetchAndStoreRelease(int newValue);
	inline int Load() const;
	inline int LoadAcquire() const;
	inline void Store(int newValue);
	inline void StoreRelease(int newValue);
	inline bool TestAndSetAcquire(int expectedValue, int newValue);
	inline bool TestAndSetOrdered(int expectedValue, int newValue);
	inline bool TestAndSetRelaxed(int expectedValue, int newValue);
	inline bool TestAndSetRelease(int expectedValue, int newValue);

private:
	std::atomic<int> m_atomic;
};


inline AtomicInt &AtomicInt::operator=(const AtomicInt &other)
{
	m_atomic = other.m_atomic.load(std::memory_order_relaxed);
	return *this;
}

inline AtomicInt &AtomicInt::operator=(int value)
{
	m_atomic = value;
	return *this;
}

inline bool AtomicInt::Ref()
{
	if (m_atomic.fetch_add(1, std::memory_order_acq_rel) != -1)
		return true;
	return false;
}

inline bool AtomicInt::Deref()
{
	if (m_atomic.fetch_sub(1, std::memory_order_acq_rel) != 1)
		return true;
	return false;
}

inline int AtomicInt::FetchAndAddAcquire(int valueToAdd)
{
	return m_atomic.fetch_add(valueToAdd, std::memory_order_acquire);
}

inline int AtomicInt::FetchAndAddOrdered(int valueToAdd)
{
	return m_atomic.fetch_add(valueToAdd, std::memory_order_acq_rel);
}

inline int AtomicInt::FetchAndAddRelaxed(int valueToAdd)
{
	return m_atomic.fetch_add(valueToAdd, std::memory_order_relaxed);
}

inline int AtomicInt::FetchAndAddRelease(int valueToAdd)
{
	return m_atomic.fetch_add(valueToAdd, std::memory_order_release);
}


inline int AtomicInt::FetchAndStoreAcquire(int newValue)
{
	return m_atomic.exchange(newValue, std::memory_order_acquire);
}

inline int AtomicInt::FetchAndStoreOrdered(int newValue)
{
	return m_atomic.exchange(newValue, std::memory_order_acq_rel);
}

inline int AtomicInt::FetchAndStoreRelaxed(int newValue)
{
	return m_atomic.exchange(newValue, std::memory_order_relaxed);
}

inline int AtomicInt::FetchAndStoreRelease(int newValue)
{
	return m_atomic.exchange(newValue, std::memory_order_release);
}

inline int AtomicInt::Load() const
{
	return m_atomic.load();
}

inline int AtomicInt::LoadAcquire() const
{
	return m_atomic.load(std::memory_order_acquire);
}

inline void AtomicInt::Store(int newValue)
{
	m_atomic.store(newValue);
}

inline void AtomicInt::StoreRelease(int newValue)
{
	m_atomic.store(newValue, std::memory_order_release);
}

inline bool AtomicInt::TestAndSetAcquire(int expectedValue, int newValue)
{
	return m_atomic.compare_exchange_strong(expectedValue, newValue, std::memory_order_acquire);
}

inline bool AtomicInt::TestAndSetOrdered(int expectedValue, int newValue)
{
	return m_atomic.compare_exchange_strong(expectedValue, newValue, std::memory_order_acq_rel);
}

inline bool AtomicInt::TestAndSetRelaxed(int expectedValue, int newValue)
{
	return m_atomic.compare_exchange_strong(expectedValue, newValue, std::memory_order_relaxed);
}

inline bool AtomicInt::TestAndSetRelease(int expectedValue, int newValue)
{
	return m_atomic.compare_exchange_strong(expectedValue, newValue, std::memory_order_release);
}


} //namespace System


#endif //_H_PUNK_ATOMICINT
