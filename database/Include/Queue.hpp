/*
Athor: Loke Strøm
*/
#pragma once

namespace Database {

	template <typename T>
	class Queue {
	public:
		Queue() noexcept;
		~Queue() noexcept;

		T& viewFront();
		T& viewBack();

		void pushOn(T val) noexcept;
		T pushOff();

		unsigned int size() const noexcept;
		bool empty() const noexcept;
		void clear() noexcept;
		
	private:

		struct node {
			T val = 0;
			node<T>* next = nullptr;
		};

		node<T>* front = nullptr;
		node<T>* back = nullptr;
	};
}

#include "TemplateFiles/Queue.tpp"