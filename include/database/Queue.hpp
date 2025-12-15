#pragma once

#include <atomic>
#include <mutex>

#include "exceptionHandeling.hpp"
#include "concepts.hpp"

namespace Database
{

template <typename T>
class Queue {
public:
	Queue() noexcept;
	~Queue() noexcept;

	Queue(const Queue<T>& other);
	Queue(Queue<T>&& other);

	[[nodiscard]]
	Queue<T>& operator=(const Queue<T>& other);
	[[nodiscard]]
	Queue<T>& operator=(Queue<T>&& other);

	[[nodiscard]]
	Expected<T&> viewFront() DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	[[nodiscard]]
	Expected<T&> viewBack() DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> pushOn(const T& val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> pushOn(T&& val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	[[nodiscard]]
	Expected<T> pushOff() DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	[[nodiscard]]
	size_t size() const noexcept;
	[[nodiscard]]
	bool empty() const noexcept;
	void clear() noexcept;

private:

	struct node {
		T val;
		node* next = nullptr;
	};

	node* front;
	node* back;
};

template<TrivialElement T, size_t N = 0>
	requires(N != 0)
class AtomicStaticQueue {
public:
	AtomicStaticQueue() noexcept;

	~AtomicStaticQueue() noexcept = default;

	AtomicStaticQueue(const AtomicStaticQueue<T, N>& other) noexcept = delete;
	AtomicStaticQueue(AtomicStaticQueue<T, N>&& other) noexcept = delete;

	AtomicStaticQueue<T, N>& operator=(const AtomicStaticQueue<T, N>& other) noexcept = delete;
	AtomicStaticQueue<T, N>& operator=(AtomicStaticQueue<T, N>&& other) noexcept = delete;
	
	bool empty() const noexcept;
	bool full() const noexcept;

	size_t size() const noexcept;

	void pushOn(const T& v) noexcept;
	T pushOff() noexcept;

private:
	size_t _front;
	size_t _back;
	std::atomic<size_t> _count;
	T _arr[N];
};

template<TrivialElement T, size_t N = 0>
	requires(N == 0)
class AtomicStaticQueue {
public:
	AtomicStaticQueue() noexcept;

	~AtomicStaticQueue() noexcept;

	AtomicStaticQueue(const AtomicStaticQueue<T>& other) noexcept;
	AtomicStaticQueue(AtomicStaticQueue<T>&& other) noexcept;

	AtomicStaticQueue<T>& operator=(const AtomicStaticQueue<T>& other) noexcept;
	AtomicStaticQueue<T>& operator=(AtomicStaticQueue<T>&& other) noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;

	size_t size() const noexcept;

	void pushOn(const T& v) noexcept;
	T pushOff() noexcept;

private:
	size_t _front;
	size_t _back;
	std::atomic<size_t> _count;
	size_t _size;
	T* _arr;
};

}

#include "TemplateFiles/Queue.tpp"