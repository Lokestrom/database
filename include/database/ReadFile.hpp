/*
Author: Loke Strøm
*/
#pragma once

#include "String.hpp"
#include "Vector.hpp"
#include "traits.hpp"
#include "concepts.hpp"

#include <fstream>
#include <filesystem>
#include <functional>
#include <concepts>

namespace Database
{
	//IDEA: make it take in a template unsigned int to allow for performance improvements 
	// and debug improvements like static_assert

	namespace newImplementation {
		template<BinarySerializable T>
		class ReadFile {
		public:
			ReadFile() noexcept = default;
			template<validfstreamFilePathFormat FilePathFormat>
			explicit ReadFile(const FilePathFormat& fileName);
			~ReadFile() noexcept = default;

			ReadFile(const ReadFile<T>&) = delete;
			ReadFile<T>& operator=(const ReadFile<T>&) = delete;
			ReadFile(ReadFile<T>&&) noexcept = default;
			ReadFile<T>& operator=(ReadFile<T>&&) noexcept = default;

			template<validfstreamFilePathFormat FilePathFormat>
			void open(const FilePathFormat& fileName);
			void close() noexcept;
			[[nodiscard]]
			bool isOpen() noexcept;

			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void getColumn(Container& data, const std::string& columnName)
				noexcept(TraitReserveNoexceptV<Container>);
			template<typename Container>
				requires ArrayConcept<Container, T>
			void getColumn(Container& data, const std::string& columnName) noexcept;
			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void getColumn(Container& data, const std::string& columnName, 
				std::function<bool(const Container&)> condition);

			template<typename Container, StringIndexable StringContainer>
				requires NestedDynamicArray<Container, T>
			void getColumns(Container& data, const StringContainer& columnNames);
			template<typename Container, StringIndexable StringContainer>
				requires NestedArray<Container, T>
			void getColumns(Container& data, const StringContainer& columnNames) noexcept;
			template<typename Container, StringIndexable StringContainer>
				requires DynamicArrayArray<Container, T>
			void getColumns(Container& data, const StringContainer& columnNames);

			template<typename Container, StringIndexable StringContainer>
				requires NestedDynamicArray<Container, T>
			[[nodiscard]]
			bool getColumns(Container& data, const StringContainer& columnNames, 
				std::function<bool(range_value_t<Container>)> condition);
			template<typename Container, StringIndexable StringContainer>
				requires DynamicArrayArray<Container, T>
			[[nodiscard]]
			bool getColumns(Container& data, const StringContainer& columnNames,
				std::function<bool(range_value_t<Container>)> condition);

			template<StringIndexable Container>
			void getColumns(std::unordered_map<std::string, std::vector<T>>& data);
			template<StringIndexable Container>
			void getColumns(std::unordered_map<std::string, std::vector<T>>& data, 
				std::function<bool(::std::vector<T>)> condition);

			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void getRow(Container& data, size_t row)
				noexcept(TraitReserveNoexceptV<Container>);
			template<typename Container>
				requires ArrayConcept<Container, T>
			void getRow(Container& data, size_t row) noexcept;
			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			[[nodiscard]]
			bool getRow(Container& data, std::function<bool(const Container&)> condition);
			template<typename Container>
				requires ArrayConcept<Container, T>
			[[nodiscard]]
			bool getRow(Container& data, std::function<bool(const Container&)> condition);

			template<typename Container>
				requires DynamicArrayConcept<Container, range_value_t<Container>> &&
					DynamicArrayConcept<range_value_t<Container>, T>
			void getRows(Container& data, size_t min, size_t max);
			template<typename Container>
				requires DynamicArrayConcept<Container, range_value_t<Container>> &&
					ArrayConcept<range_value_t<Container>, T>
			void getRows(Container& data, size_t min, size_t max);
			
			template<typename Container>
				requires NestedDynamicArray<Container, T>
			void getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition);
			template<typename Container>
				requires DynamicArrayArray<Container, T>
			void getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition) 
				noexcept(TraitReserveNoexceptV<Container>&& TraitConstructCapacityNoexceptV<range_value_t<Container>>);

			template<typename Container>
				requires NestedDynamicArray<Container, T>
			void getAllColumns(Container& data) 
				noexcept(TraitReserveNoexceptV<Container>&& TraitConstructCapacityNoexceptV<range_value_t<Container>>);
			template<typename Container>
				requires NestedArray<Container, T>
			void getAllColumns(Container& data) noexcept;
			template<typename Container>
				requires NestedDynamicArray<Container, T>
			void getAllRows(Container& data) 
				noexcept(TraitReserveNoexceptV<Container>&& TraitConstructCapacityNoexceptV<range_value_t<Container>>);
			template<typename Container>
				requires NestedArray<Container, T>
			void getAllRows(Container& data) noexcept;

			[[nodiscard]]
			const std::vector<String>& getColumnNames() const noexcept;
			[[nodiscard]]
			const unsigned int columnCount() const noexcept;
			[[nodiscard]]
			const bool contains(const CharSpan& name) const noexcept;

		private:
			[[nodiscard]]
			const unsigned int rowLengthBytes() const noexcept;
			[[nodiscard]]
			const size_t dataLengthBytes() const noexcept;
			[[nodiscard]]
			const size_t itemOffsetBytes(unsigned int column) const noexcept;
			[[nodiscard]]
			const unsigned int column(const CharSpan& name) const noexcept;

			void moveReader(std::streamoff offset, std::ios_base::seekdir dir = std::ios::beg) noexcept;

			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void readRow(Container& data) noexcept;
			template<typename Container>
				requires ArrayConcept<Container, T>
			void readRow(Container& data) noexcept;
			[[nodiscard]]
			T readItem() noexcept;

			template<validfstreamFilePathFormat FilePathFormat>
			void setup(const FilePathFormat& filePath);

		private:
			std::ifstream _file;
			std::vector<String> _columnNames;
			size_t _rowCount;
			unsigned int _dataStart;
		};
	}
}

#include "TemplateFiles/ReadFile.tpp"