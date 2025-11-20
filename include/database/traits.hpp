#pragma once

#include <vector>
#include <ranges>
#include <array>

#include "Vector.hpp"

namespace Database {
	/*
	* "must" is used when the action is required
	* "should" is used when the action is not needed but heavily recommended
	* "can" is used when a action is possible and recommended
	*/

	/*
	* defaults for traits:
	* the traits is defined in this order where the ones above fill all functions applicable to it:
	*	std::vector
	*	
	*/
	template<typename Container>
	struct ContainerTraits {
		/* must return a container which should have the specified capacity*/
		static Container constructCapacity(unsigned long long capacity)
		{
			Container c;
			c.reserve(capacity);
			return c;
		}

		/* 
		* must append element to the end of the container
		* must increase the capacity if full
		*/
		template<typename T>
		static void pushBack(Container& c, const T& element)
		{
			c.push_back(element);
		}

		/*
		* should set the capacity to the specified capacity
		*/
		static void reserve(Container& c, unsigned long long newCapacity)
		{
			c.reserve(newCapacity);
		}

		/*
		* must return the amount of elements in the container
		*/
		static const unsigned long long size(const Container& c) {
			return c.size();
		}
		/*
		* must return the size of the container that must be known at compile time
		*/
		static consteval unsigned long long size() {
			return 0;
		}

		/*
		* must return a reference to the element at the specified index
		*/
		static auto& at(Container& c, unsigned long long index) {
			return c[index];
		}

		/*
		* must move the old one into the new one
		* must leave the oldOwner container in a valid state
		*/
		static void safeMove(Container& newOwner, Container& oldOwner) {
			newOwner = std::move(oldOwner);
		}
		/*
		* must move the old one into the new one
		* can leave the oldOwner in a non valid state
		*/
		static void destructiveMove(Container& newOwner, Container& oldOwner) {
			safeMove(newOwner, oldOwner);
		}

		/*
		* must empty the container of elements
		*/
		static void clear(Container& c) {
			c.clear();
		}

		/*
		* must return a reference to the last element of the container
		*/
		static auto& endElement(Container& c) {
			return ContainerTraits<Container>::at(c, ContainerTraits<Container>::size(c) - 1);
		}
	};


	template<typename R>
	using range_value_t = std::remove_reference_t<decltype(*std::begin(std::declval<R&>()))>;

	template<typename C, typename T>
	concept IterableArray =
		std::ranges::range<C> &&
		std::same_as<std::ranges::range_value_t<C>, T> &&
		requires(C c) {
			{ ContainerTraits<C>::size(c) } -> std::convertible_to<unsigned long long>;
	};

	template<typename C, typename T>
	concept ArrayConcept =
		std::ranges::range<C> &&
		requires(C c, const C cc, unsigned long long i) {
			{ ContainerTraits<C>::at(c, i) } -> std::same_as<T&>;
			{ ContainerTraits<C>::size() } -> std::convertible_to<unsigned long long>;
	} &&
		!requires(C c, const T& elem) {
			{ ContainerTraits<C>::pushBack(c, elem) };
	};

	template<typename C, typename T>
	concept DynamicArrayConcept =
		std::ranges::range<C> &&
		requires(C c, const C cc, const T& elem, unsigned long long cap) {
			{ ContainerTraits<C>::constructCapacity(cap) } -> std::same_as<C>;
			{ ContainerTraits<C>::pushBack(c, elem) };
			{ ContainerTraits<C>::reserve(c, cap) };
			{ ContainerTraits<C>::size(cc) } -> std::convertible_to<unsigned long long>;
			{ ContainerTraits<C>::safeMove(c, c) };
			{ ContainerTraits<C>::clear(c) };
			{ ContainerTraits<C>::at(c, cap) } -> std::same_as<T&>;
			{ ContainerTraits<C>::endElement(c) } -> std::same_as<T&>;
	};

	template<typename C, typename T>
	concept MapConcept =
		std::ranges::range<C> &&
		requires(C c) {
			{ ContainerTraits<C>::size(c) } -> std::convertible_to<unsigned long long>;
	};

	template<typename Container, typename T>
	concept NestedDynamicArray =
		DynamicArrayConcept<Container, range_value_t<Container>> &&
		DynamicArrayConcept<range_value_t<Container>, T>;

	template<typename Container, typename T>
	concept NestedArray =
		ArrayConcept<Container, range_value_t<Container>> &&
		ArrayConcept<range_value_t<Container>, T>;

	template<typename Container, typename T>
	concept DynamicArrayArray =
		DynamicArrayConcept<Container, range_value_t<Container>> &&
		ArrayConcept<range_value_t<Container>, T>;

	template<typename Container, typename T>
	concept OuterMap =
		MapConcept<Container, range_value_t<Container>> &&
		(ArrayConcept<range_value_t<Container>, T> || DynamicArrayConcept<range_value_t<Container>, T>);
	
	template<typename Container, typename T>
	concept InnerMap =
		(ArrayConcept<Container, T> || DynamicArrayConcept<Container, T>) &&
		MapConcept<range_value_t<Container>, T>;

	/*template<typename T>
	struct ContainerTratis<std::vector<T>> {
		static Container constructCapasity(unsigned long long capasity) {
			Container c;
			c.reserve(capasity);
			return c;
		}
	};*/
	
	template<typename T, size_t _size>
	struct ContainerTraits<std::array<T, _size>>{
		static T& at(std::array<T, _size>& c, unsigned long long index) {
			return c[index];
		}

		static consteval unsigned long long size() {
			return _size;
		}
	};

	template<TrivialElement T>
	struct ContainerTraits<Vector<T>> {
		static Vector<T> constructCapacity(unsigned long long capacity)
		{
			return Vector<T>(capacity);
		}

		static void pushBack(Vector<T>& v, const T& element)
		{
			v.pushBack(element);
		}

		static void reserve(Vector<T>& v, unsigned long long newCapacity)
		{
			v.reserve(newCapacity);
		}

		static unsigned long long size(const Vector<T>& v) {
			return v.size();
		}

		static T& at(Vector<T>& c, unsigned long long index) {
			return c[index];
		}

		static void safeMove(Vector<T>& newOwner, Vector<T>& oldOwner) {
			newOwner = std::move(oldOwner);
		}

		static void clear(Vector<T>& c) {
			c.clear();
		}

		static T& endElement(Vector<T>& v) {
			return ContainerTraits<Vector<T>>::at(v, ContainerTraits<Vector<T>>::size(v) - 1);
		}
	};
}

#include "TemplateFiles/traits.tpp"