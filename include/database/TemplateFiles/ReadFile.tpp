/*
Author: Loke Strøm
*/
#include "ReadFile.hpp"
#include "exceptionHandeling.hpp"

#include <assert.h>
#include <algorithm>
#include <numeric>

namespace Database
{
	template<BinarySerializable T>
	template<validfstreamFilePathFormat FilePathFormat>
	Database::newImplementation::ReadFile<T>::ReadFile(const FilePathFormat& fileName)
		: _file(fileName, ::std::ios::binary)
	{
		setup(fileName);
	}

	template<BinarySerializable T>
	template<validfstreamFilePathFormat FilePathFormat>
	void newImplementation::ReadFile<T>::open(const FilePathFormat& fileName)
	{
		assert(!isOpen() && "File already open unexpected behavior follows");
		_file.open(fileName);
		setup(fileName);
	}

	template<BinarySerializable T>
	void newImplementation::ReadFile<T>::close() noexcept {
		_file.close();
	}

	template<BinarySerializable T>
	bool newImplementation::ReadFile<T>::isOpen() noexcept {
		return _file.is_open();
	}

	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getColumn(Container& data, const::std::string& columnName) 
		noexcept(TraitReserveNoexceptV<Container>)
	{
		assert(contains(columnName) && "the file does not contain a column of this name");
		
		ContainerTraits<Container>::reserve(data, _rowCount);
		unsigned int columnNumber = column(columnName);
		moveReader(columnNumber * sizeof(T));
		for (auto i = 0; i < _rowCount - 1; i++) {
			ContainerTraits<Container>::pushBack(data, readItem());
			moveReader(rowLengthBytes() - sizeof(T), std::ios::cur);
		}
		ContainerTraits<Container>::pushBack(data, readItem());
	}

	template<BinarySerializable T>
	template<typename Container>
		requires ArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getColumn(Container& data, const std::string& columnName) noexcept
	{
		assert(contains(columnName) && "the file does not contain a column of this name");
		assert(ContainerTraits<Container>::size() >= _rowCount && "container is not big enough");

		unsigned int columnNumber = column(columnName);
		moveReader(columnNumber * sizeof(T));
		for (auto i = 0; i < _rowCount - 1; i++) {
			ContainerTraits<Container>::at(data, i) = readItem();
			moveReader(rowLengthBytes() - sizeof(T), std::ios::cur);
		}
		ContainerTraits<Container>::at(data, _rowCount - 1) = readItem();
	}

	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getColumn(Container& data, 
		const std::string& columnName, std::function<bool(const Container&)> condition) 
	{
		assert(contains(columnName) && "the file does not contain a column of this name");

		moveReader(0);
		unsigned int columnNumber = column(columnName);
		HeapArray rowData(columnCount());
		for (auto i = 0; i < _rowCount; i++) {
			readRow(rowData);
			if(condition(rowData))
				ContainerTraits<Container>::pushBack(data, rowData[columnNumber]);
		}
	}

	template<BinarySerializable T>
	template<typename Container, StringIndexable StringContainer>
		requires NestedDynamicArray<Container, T>
	void newImplementation::ReadFile<T>::getColumns(Container& data, const StringContainer& columnNames) 
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		assert(std::ranges::all_of(columnNames, [&](const auto& name) {return contains(name); }) &&
			"one or more of the names does not exist in the file");

		OuterContainerTraits::reserve(data, columnNames.size());
		HeapArray columnOrder(columnNames.size());
		for (auto i = 0; i < columnNames.size(); i++) {
			columnOrder[i] = column(columnNames[i]);
			OuterContainerTraits::pushBack(data,
				InnerContainerTraits::constructCapacity(_rowCount));
		}
		HeapArray rowData(columnCount());
		moveReader(0);
		for (auto row = 0; row < _rowCount; row++) {
			readRow(rowData);
			for (auto column = 0; column < columnNames.size(); column++)
				InnerContainerTraits::pushBack(OuterContainerTraits::at(data, column),
					rowData[columnOrder[column]]);
		}
	}

	template<BinarySerializable T>
	template<typename Container, StringIndexable StringContainer>
		requires NestedArray<Container, T>
	void newImplementation::ReadFile<T>::getColumns(Container& data, const StringContainer& columnNames) noexcept {
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		assert(std::ranges::all_of(columnNames, [&](const auto& name) {return contains(name); }) &&
			"one or more of the names does not exist in the file");
		assert(OuterContainerTraits::size() >= columnCount() && "container has to few columns");
		assert(InnerContainerTraits::size() >= _rowCount && "container has to few rows");

		unsigned int columnOrder[OuterContainerTraits::size()];
		for (auto i = 0; i < columnNames.size(); i++) {
			columnOrder[i] = column(columnNames[i]);
		}
		moveReader(0);
		Vector temp(columnCount());
		for (auto row = 0; row < _rowCount; row++) {
			readRow(temp);
			for (auto column = 0; column < columnNames.size(); column++)
				InnerContainerTraits::at(OuterContainerTraits::at(data, column), row) = temp[columnOrder[column]];
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getRow(Container& data, size_t row) 
		noexcept(TraitReserveNoexceptV<Container>)
	{
		assert(row <= _rowCount && "The specified row is outside the buffer");
		ContainerTraits<Container>::reserve(data, columnCount());
		moveReader(rowLengthBytes() * row);
		readRow(data);
	}

	template<BinarySerializable T>
	template<typename Container>
		requires ArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getRow(Container& data, size_t row) noexcept {
		assert(row <= _rowCount && "The specified row is outside the buffer");
		assert(ContainerTraits<Container>::size(data) >= columnCount() && "Array must have a size equal to the column count");
		moveReader(rowLengthBytes() * row);
		readRow(data);
	}

	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayConcept<Container, T>
	bool newImplementation::ReadFile<T>::getRow(Container& data, std::function<bool(const Container&)> condition)
	{
		moveReader(0);
		ContainerTraits<Container>::reserve(data, columnCount());
		for (auto i = 0; i < _rowCount; i++) {
			readRow(data);
			if (condition(data))
				return true;
			ContainerTraits<Container>::clear(data);
		}
		return false;
	}

	template<BinarySerializable T>
	template<typename Container>
		requires ArrayConcept<Container, T>
	bool newImplementation::ReadFile<T>::getRow(Container& data, std::function<bool(const Container&)> condition)
	{
		moveReader(0);
		for (auto i = 0; i < _rowCount; i++) {
			readRow(data);
			if (condition(data))
				return true;
		}
		return false;
	}

	template<BinarySerializable T>
	template<typename Container>
		requires NestedDynamicArray<Container, T>
	void newImplementation::ReadFile<T>::getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition)
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;

		moveReader(0);
		OuterContainerTraits::pushBack(data,
			InnerContainerTraits::constructCapacity(columnCount()));
		for (auto i = 0; i < _rowCount; i++) {
			readRow(OuterContainerTraits::endElement(data));
			if (condition(OuterContainerTraits::endElement(data)))
				OuterContainerTraits::pushBack(data,
					InnerContainerTraits::constructCapacity(columnCount()));
			InnerContainerTraits::clear(OuterContainerTraits::endElement(data));
		}
	}
	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayArray<Container, T>
	void newImplementation::ReadFile<T>::getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition) 
		noexcept(TraitReserveNoexceptV<Container> && TraitConstructCapacityNoexceptV<range_value_t<Container>>)
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		
		moveReader(0);
		OuterContainerTraits::pushBack(data,
			InnerContainerTraits::constructCapacity(columnCount()));
		for (auto i = 0; i < _rowCount; i++) {
			readRow(OuterContainerTraits::endElement(data));
			if (condition(OuterContainerTraits::endElement(data)))
				OuterContainerTraits::pushBack(data,
					InnerContainerTraits::constructCapacity(columnCount()));
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires NestedDynamicArray<Container, T>
	void newImplementation::ReadFile<T>::getAllColumns(Container& data) 
		noexcept(TraitReserveNoexceptV<Container> && TraitConstructCapacityNoexceptV<range_value_t<Container>>)
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		moveReader(0);

		OuterContainerTraits::reserve(data, columnCount());
		for (auto i = 0; i < columnCount(); i++) {
			OuterContainerTraits::pushBack(data,
				InnerContainerTraits::constructCapacity(_rowCount));
		}
		for (auto i = 0; i < _rowCount; i++) {
			for (auto j = 0; j < columnCount(); j++) {
				InnerContainerTraits::pushBack(data[j], readItem());
			}
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires NestedArray<Container, T>
	void newImplementation::ReadFile<T>::getAllColumns(Container& data) noexcept
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		assert(OuterContainerTraits::size(data) >= _columnNames.size());
		assert(InnerContainerTraits::size(data) >= _rowCount);

		moveReader(0);

		for (auto i = 0; i < _rowCount; i++) {
			for (auto j = 0; j < columnCount(); j++) {
				InnerContainerTraits::at(data[j], i) = readItem();
			}
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires NestedDynamicArray<Container, T>
	void newImplementation::ReadFile<T>::getAllRows(Container& data)
		noexcept(TraitReserveNoexceptV<Container> && TraitConstructCapacityNoexceptV<range_value_t<Container>>)
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;

		moveReader(0);
		OuterContainerTraits::reserve(data, _rowCount);
		for (auto i = 0; i < _rowCount; i++) {
			OuterContainerTraits::pushBack(data,
				InnerContainerTraits::constructCapacity(_columnNames.size()));
			readRow(data[i]);
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires NestedArray<Container, T>
	void newImplementation::ReadFile<T>::getAllRows(Container& data) noexcept {
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		assert(OuterContainerTraits::size(data) >= _rowCount);
		assert(InnerContainerTraits::size(data) >= _columnNames.size());

		moveReader(0);
		for (auto i = 0; i < _rowCount; i++) {
			readRow(data[i]);
		}
	}

	template<BinarySerializable T>
	const::std::vector<String>& Database::newImplementation::ReadFile<T>::getColumnNames() const noexcept
	{
		return _columnNames;
	}
	template<BinarySerializable T>
	const unsigned int newImplementation::ReadFile<T>::columnCount() const noexcept {
		return _columnNames.size();
	}
	template<BinarySerializable T>
	const bool newImplementation::ReadFile<T>::contains(const CharSpan& name) const noexcept{
		return std::find(_columnNames.begin(), _columnNames.end(), name) != _columnNames.end();
	}
	template<BinarySerializable T>
	const unsigned int Database::newImplementation::ReadFile<T>::rowLengthBytes() const noexcept
	{
		return columnCount() * sizeof(T);
	}
	template<BinarySerializable T>
	const size_t Database::newImplementation::ReadFile<T>::dataLengthBytes() const noexcept
	{
		return _rowCount * rowLengthBytes();
	}

	template<BinarySerializable T>
	const size_t newImplementation::ReadFile<T>::itemOffsetBytes(unsigned int column) const noexcept
	{
		return column * sizeof(T);
	}

	template<BinarySerializable T>
	const unsigned int newImplementation::ReadFile<T>::column(const CharSpan& name) const noexcept {
		return std::distance(_columnNames.begin(), std::find(_columnNames.begin(), _columnNames.end(), name));
	}

	template<BinarySerializable T>
	void newImplementation::ReadFile<T>::moveReader(::std::streamoff offset, ::std::ios_base::seekdir dir) noexcept
	{
		_file.seekg(offset + (dir == ::std::ios::beg) * _dataStart, dir);
	}

	template<BinarySerializable T>
	template<typename Container>
	requires DynamicArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::readRow(Container& data) noexcept
	{
		for (int i = 0; i < columnCount(); i++)
			ContainerTraits<Container>::pushBack(data, readItem());
	}

	template<BinarySerializable T>
	template<typename Container>
		requires ArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::readRow(Container& data) noexcept
	{
		for (int i = 0; i < columnCount(); i++)
			ContainerTraits<Container>::at(data, i) = readItem();
	}

	template<BinarySerializable T>
	T newImplementation::ReadFile<T>::readItem() noexcept
	{
		T x;
		_file.read(reinterpret_cast<char*>(&x), sizeof(T));
		return x;
	}

	template<BinarySerializable T>
	template<validfstreamFilePathFormat FilePathFormat>
	void newImplementation::ReadFile<T>::setup(const FilePathFormat& filePath) {
		unsigned int columnNumber = 0;
		_file.read(reinterpret_cast<char*>(&columnNumber), sizeof(unsigned int));
		_columnNames.reserve(columnNumber);
		_dataStart = 4;

		String temps;
		char tempc;
		for (int i = 0; i < columnNumber; _dataStart++) {
			_file.read(&tempc, sizeof(char));
			if (tempc == Database::_splitByte) {
				temps.shrinkToFit();
				_columnNames.push_back(temps);
				temps.clear();
				i++;
				continue;
			}
			temps.pushBack(tempc);
		}

		auto size = std::filesystem::file_size(filePath);
		if (rowLengthBytes() == 0) {
			_rowCount = 0;
			return;
		}
		_rowCount = (size - _dataStart) / rowLengthBytes();
	}
}