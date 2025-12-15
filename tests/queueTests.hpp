#include "Queue.hpp"
#include <vector>
#include <assert.h>
#include <thread>
#include <iostream>

using namespace Database;

template<typename T>
void queueTests(std::vector<T> examples){
	assert(examples.size() == 5 && "there must be 5 examples");
	Queue<T> test;
	assert(test.size() == 0 && "size is wrong");
	assert(test.empty() && "empty is wrong");

	test.pushOn(examples[0]);
	assert(test.size() == 1 && "size is wrong");
	assert(!test.empty() && "empty is wrong");
	assert(test.viewFront() == examples[0] && "Front is wrong");

	test.pushOn(examples[3]);
	assert(test.size() == 2 && "size is wrong");
	assert(test.viewFront() == examples[0] && "Front is wrong");
	assert(test.viewBack() == examples[3] && "Back is wrong");

	assert(test.pushOff() == examples[0] && "given the wrong value");
	assert(test.size() == 1 && "size is wrong");
	assert(test.viewFront() == examples[3] && "Front is wrong");

	test.pushOn(examples[1]);
	test.pushOn(examples[2]);
	test.pushOn(examples[4]);

	assert(test.size() == 4 && "size is wrong");
	assert(test.viewFront() == examples[3] && "Front is wrong");
	assert(test.viewBack() == examples[4] && "Back is wrong");


	assert(test.pushOff() == examples[3] && "given the wrong value");
	assert(test.pushOff() == examples[1] && "given the wrong value");
	assert(test.pushOff() == examples[2] && "given the wrong value");
	assert(test.pushOff() == examples[4] && "given the wrong value");
	assert(test.empty() && "queue should be empty");
	assert(test.size() == 0 && "queue should be empty");

	test.pushOn(examples[0]);
	test.pushOn(examples[1]);
	test.pushOn(examples[2]);
	assert(test.size() == 3 && "queue should be empty");


	Queue<T> other = test;
	assert(other.size() == 3 && "should have 3 elements");
	assert(other.pushOff() == examples[0] && "given the wrong value");
	assert(other.pushOff() == examples[1] && "given the wrong value");
	assert(other.pushOff() == examples[2] && "given the wrong value");
	assert(other.empty() && "other should be empty");

	test.clear();
	assert(test.empty() && "queue should be empty");
}

template<TrivialElement T>
void atomicStaticQueueRaceCondition(std::vector<T> examples){
	AtomicStaticQueue<T, 10> test;
	std::atomic_bool stop = false;
	std::atomic<size_t> count = 0;
	auto pushOn = [&]() {
		while (!stop) {
			for (int i = 0; i < 5; i++) {
				while (test.full()) {
					std::this_thread::yield();
				}
				test.pushOn(examples[i]);
				count++;
			}
		}
	};

	auto pushOff = [&]() {
		while (!stop) {
			for (int i = 0; i < 5; i++) {
				while (test.empty()) {
					std::this_thread::yield();
				}
				assert(test.pushOff() == examples[i] && "issues in multi threading");
				count++;
			}
		}
	};

	std::thread onThread(pushOn);
	std::thread offThread(pushOff);

	std::cout << "started race condition checker\n";
	std::this_thread::sleep_for(std::chrono::seconds(10));
	stop = true;
	onThread.join();
	offThread.join();
	std::cout << "count: " << count << "\n";
}

template<TrivialElement T>
void atomicStaticQueueTests(std::vector<T> examples) {
	AtomicStaticQueue<T, 5> test;
	assert(test.empty() && "test should be empty");
	assert(test.size() == 0 && "size should be 0");

	test.pushOn(examples[0]);
	assert(!test.empty() && "test should not be empty");
	assert(test.size() == 1 && "size should be 1");

	test.pushOn(examples[1]);
	test.pushOn(examples[2]);
	test.pushOn(examples[3]);
	test.pushOn(examples[4]);
	assert(!test.empty() && "test should not be empty");
	assert(test.size() == 5 && "size should be 5");
	assert(test.full() && "test should be full");

	assert(test.pushOff() == examples[0] && "given the wrong value");
	assert(test.size() == 4 && "size should be 5");
	assert(!test.empty() && "test should not be empty");
	assert(!test.full() && "test should not be full");

	assert(test.pushOff() == examples[1] && "given the wrong value");
	assert(test.pushOff() == examples[2] && "given the wrong value");
	assert(test.pushOff() == examples[3] && "given the wrong value");
	assert(test.pushOff() == examples[4] && "given the wrong value");
	assert(test.empty() && "test should be empty");
	assert(test.size() == 0 && "size should be 0");

	test.pushOn(examples[1]);
	test.pushOn(examples[2]);
	test.pushOn(examples[3]);
	assert(test.size() == 3 && "size should be 3");

	atomicStaticQueueRaceCondition(examples);
}

