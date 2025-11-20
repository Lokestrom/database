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
	//TODO: possibly create a minimal heap allocated container instead of using
	//Container temp = InnerContainerTraits::constructCapacity(columnCount()); // DynamicArray
	//Vector temp(columnCount()); // Array

	namespace newImplementation {
		template<BinarySerializable T>
		class ReadFile {
		public:
			ReadFile() noexcept = default;
			template<validfstreamFilePathFormat FilePathFormat>
			ReadFile(const FilePathFormat& fileName);
			~ReadFile() noexcept = default;

			ReadFile(const ReadFile<T>&) = delete;
			ReadFile<T>& operator=(const ReadFile<T>&) = delete;
			ReadFile(ReadFile<T>&& readFile) noexcept = default;
			ReadFile<T>& operator=(ReadFile<T>&&) noexcept = default;

			template<validfstreamFilePathFormat FilePathFormat>
			void open(const FilePathFormat& fileName);
			void close() noexcept;
			bool isOpen() noexcept;

			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void getColumn(Container& data, const std::string& columnName);
			template<typename Container>
				requires ArrayConcept<Container, T>
			void getColumn(Container& data, const std::string& columnName);
			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void getColumn(Container& data, const std::string& columnName, 
				std::function<bool(const Container&)> condition);

			template<typename Container, StringIndexable StringContainer>
				requires NestedDynamicArray<Container, T>
			void getColumns(Container& data, const StringContainer& columnNames);
			template<typename Container, StringIndexable StringContainer>
				requires NestedArray<Container, T>
			void getColumns(Container& data, const StringContainer& columnNames);
			template<typename Container, StringIndexable StringContainer>
				requires NestedDynamicArray<Container, T>
			bool getColumns(Container& data, const StringContainer& columnNames, 
				std::function<bool(range_value_t<Container>)> condition);

			template<StringIndexable Container>
			void getColumns(std::unordered_map<std::string, std::vector<T>>& data);
			template<StringIndexable Container>
			void getColumns(std::unordered_map<std::string, std::vector<T>>& data, 
				std::function<bool(::std::vector<T>)> condition);

			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void getRow(Container& data, unsigned long long row) noexcept;
			template<typename Container>
				requires ArrayConcept<Container, T>
			void getRow(Container& data, unsigned long long row) noexcept;
			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			bool getRow(Container& data, std::function<bool(const Container&)> condition) noexcept;
			template<typename Container>
				requires ArrayConcept<Container, T>
			bool getRow(Container& data, std::function<bool(const Container&)> condition) noexcept;

			template<typename Container>
				requires NestedDynamicArray<Container, T>
			void getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition) noexcept;
			template<typename Container>
				requires DynamicArrayArray<Container, T>
			void getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition) noexcept;

			template<typename Container>
				requires NestedDynamicArray<Container, T>
			void getAllColumns(Container& data) noexcept;
			template<typename Container>
				requires NestedArray<Container, T>
			void getAllColumns(Container& data) noexcept;
			template<typename Container>
				requires NestedDynamicArray<Container, T>
			void getAllRows(Container& data) noexcept;
			template<typename Container>
				requires NestedArray<Container, T>
			void getAllRows(Container& data) noexcept;

			const std::vector<std::string>& getColumnNames() const noexcept;
			const unsigned int columnCount() const noexcept;

			const bool contains(const CharSpan& name);

		public:
			const unsigned int rowLengthBytes() const noexcept;
			const unsigned long long dataLengthBytes() const noexcept;
			const unsigned long long itemOffsetBytes(unsigned int column) const noexcept;

			const unsigned int column(const CharSpan& name) const noexcept;

			void moveReader(std::streamoff offset, std::ios_base::seekdir dir = std::ios::beg);

			template<typename Container>
				requires DynamicArrayConcept<Container, T>
			void readRow(Container& data);
			template<typename Container>
				requires ArrayConcept<Container, T>
			void readRow(Container& data);

			T readItem();

			template<validfstreamFilePathFormat FilePathFormat>
			void setup(const FilePathFormat& filePath);

		private:
			std::ifstream _file;
			std::vector<std::string> _columnNames;
			unsigned long long _rowCount;
			unsigned int _dataStart;
		};
	}
}

#include "TemplateFiles/ReadFile.tpp"