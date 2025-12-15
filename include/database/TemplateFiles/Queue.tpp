#include "Queue.hpp"
#include <concepts>
#include <assert.h>
namespace Database
{
template <typename T>
Queue<T>::Queue() noexcept
	: front(nullptr), back(nullptr) {}

template <typename T>
Queue<T>::~Queue() noexcept {
	if (front == nullptr)
		return;
	node* lastNode = front;
	for (node* i = front->next; i != back; i = i->next) {
		delete lastNode;
		lastNode = i;
	}
	delete back;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other)
	: front(nullptr), back(nullptr) {
	static_assert(std::is_copy_assignable_v<T> && "type must be copy assignable");
	if (other.front == nullptr)
		return;
	for (auto it = other.front; it != nullptr; it = it->next)
		pushOn(it->val);
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other)
	: front(other.front), back(other.back) {
	other.front = nullptr;
	other.back = nullptr;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	static_assert(std::is_copy_assignable_v<T> && "type must be copy assignable");
	clear();
	if (other.front == nullptr)
		return *this;
	for (auto it = other.front; it != nullptr; it = it->next)
		pushOn(it->val);

	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) {
	front = other.front;
	back = other.back;

	other.front = nullptr;
	other.back = nullptr;

	return *this;
}

template<typename T>
Expected<T&> Queue<T>::viewFront() DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (front == nullptr)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Can't return the front of empty queue");
	return front->val;
}
template<typename T>
Expected<T&> Queue<T>::viewBack() DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (front == nullptr)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Can't return the back empty queue");
	if (back == nullptr)
		return front->val;
	return back->val;
}

template <typename T>
Expected<void> Queue<T>::pushOn(const T& val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
		if (front == nullptr) {
			front = new node();
			front->val = val;
			return;
		}
	if (back == nullptr) {
		back = new node();
		back->val = val;
		front->next = back;
		return;
	}
	node* newNode = new node(val, nullptr);
	back->next = newNode;
	back = newNode;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

template<typename T>
Expected<void> Queue<T>::pushOn(T&& val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
		if (front == nullptr) {
			front = new node(std::move(val), nullptr);
			return;
		}
	if (back == nullptr) {
		back = new node(std::move(val), nullptr);
		front->next = back;
		return;
	}
	node* newNode = new node(std::move(val), nullptr);
	back->next = newNode;
	back = newNode;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

template <typename T>
Expected<T> Queue<T>::pushOff() DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (front == nullptr)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Can't pushOff an empty queue");
	T returnVal;
	if constexpr (std::is_move_assignable_v<T>)
		returnVal = (std::move(front->val));
	else {
		static_assert(std::is_copy_assignable_v<T> && "if type not move assignable it must be copy assignable");
		returnVal = front->val;
	}
	node* newNode = front->next;
	delete front;
	front = newNode;
	if (back == front) {
		back = nullptr;
	}
	return returnVal;
}

template <typename T>
size_t Queue<T>::size() const noexcept {
	if (front == nullptr) {
		return 0;
	}
	size_t count = 0;
	for (node* i = front; i != nullptr; i = i->next)
		count++;
	return count;
}

template <typename T>
bool Queue<T>::empty() const noexcept {
	return front == nullptr;
}

template <typename T>
void Queue<T>::clear() noexcept {
	node* nextNode = nullptr;
	for (node* it = front; it != nullptr; it = nextNode) {
		nextNode = it->next;
		delete it;
	}

	front = nullptr;
	back = nullptr;
}
}


namespace Database
{

template<TrivialElement T, size_t N>
	requires(N != 0)
AtomicStaticQueue<T, N>::AtomicStaticQueue() noexcept
	: _front(0), _back(0), _count(0) {}

template<TrivialElement T, size_t N>
	requires(N != 0)
bool AtomicStaticQueue<T, N>::empty() const noexcept {
	return _count.load(std::memory_order_acquire) == 0;
}

template<TrivialElement T, size_t N>
	requires(N != 0)
bool AtomicStaticQueue<T, N>::full() const noexcept {
	return _count.load(std::memory_order_acquire) == N;
}

template<TrivialElement T, size_t N>
	requires(N != 0)
size_t AtomicStaticQueue<T, N>::size() const noexcept {
	return _count.load(std::memory_order_acquire);
}

template<TrivialElement T, size_t N>
	requires(N != 0)
void AtomicStaticQueue<T, N>::pushOn(const T& v) noexcept {
	assert(!full() && "cant pushOn empty queue");

	_arr[_back] = v;

	_back = (_back + 1) % N;
	_count.fetch_add(1, std::memory_order_release);
}

template<TrivialElement T, size_t N>
	requires(N != 0)
T AtomicStaticQueue<T, N>::pushOff() noexcept {
	assert(!empty() && "cant pushOff empty queue");

	T v = _arr[_front];

	_front = (_front + 1) % N;
	_count.fetch_sub(1, std::memory_order_release);

	return v;
}
}


