/*
Author: Loke Strøm
*/
#include "Exception.hpp"
#include "ReadFile.hpp"

#include <assert.h>
#include <algorithm>
#include <numeric>

namespace Database
{
	/*template<typename T>
	ReadFile<T>::ReadFile() noexcept 
		: file()
	{
	}

	template<typename T>
	ReadFile<T>::ReadFile(const String& fileName) noexcept 
		: fileName(fileName), file(toSTD(fileName), ::std::ios::binary)
	{
		unsigned int columnNummber = 0;
		file.read(reinterpret_cast<char*>(&columnNummber), sizeof(unsigned int));
		dataStart = 4;
		String temps;
		char* tempc = new char[1];
		for (int i = 0; i < columnNummber;) {
			file.read(tempc, sizeof(char));
			dataStart++;
			if (tempc[0] == splitByte) {
				ColumnNames.pushBack(temps);
				temps.clear();
				i++;
				continue;
			}
			temps.pushBack(tempc[0]);
		}
	}

	template <typename T>
	ReadFile<T>::ReadFile(ReadFile<T>&& readFile) noexcept {
		file = std::move(readFile.file);
		fileName = std::move(readFile.fileName);
		dataStart = readFile.dataStart;
		ColumnNames = std::move(readFile.ColumnNames);
	}

	template<typename T>
	ReadFile<T>::~ReadFile() noexcept {
		if (file.is_open())
			file.close();
	}

	template<typename T>
	void ReadFile<T>::open(const String& fileName) {
		if (file.is_open())
			throw SystemError("A file is alredy open");
		this(fileName);
	}

	template<typename T>
	void ReadFile<T>::close() noexcept {
		if (file.is_open())
			file.close();
		file.close();
	}

	template<typename T>
	bool ReadFile<T>::isOpen() noexcept {
		return file.is_open();
	}

	template<typename T>
	void ReadFile<T>::getAllDataFromColumn(Vector<T>& data, const String& columnName) noexcept {
		file.clear();
		file.seekg(dataStart, ::std::ios::beg);
		data.clear();
		T x;
		auto columnNummber = ColumnNames.linearSearch(columnName);
		for (auto i = 0; file.read(reinterpret_cast<char*>(&x), sizeof(T)); i++) {
			if (i == columnNummber)
				data.pushBack(x);
			if (i == ColumnNames.size()-1)
				i = -1;
		}
	}

	template<typename T>
	void ReadFile<T>::getAllRowsWhereColumnIsEqualeToAValue(Vector<Vector<T>>& data, const String& columnName, T value) noexcept
	{
		file.clear();
		file.seekg(dataStart, ::std::ios::beg);
		data.clear();
		T x;
		auto columnNumber = ColumnNames.linearSearch(columnName);
		data.pushBack(Vector<T>(ColumnNames.size()));
		for (auto i = 0; !file.eof();) {
			for (auto j = 0; j < ColumnNames.size(); j++) {
				file.read(reinterpret_cast<char*>(&x), sizeof(T));
				data[i].pushBack(x);
				if (j != columnNumber)
					continue;
				if (x != value) {
					data[i].clear();
					for (j++; j < ColumnNames.size(); j++)
						file.read(reinterpret_cast<char*>(&x), sizeof(T));
					break;
				}
			}
			if (!data[i].empty()) {
				data.pushBack(Vector<T>(ColumnNames.size()));
				i++;
			}

		}
		data.popBack(); 
	}

	template<typename T>
	void ReadFile<T>::getRow(Vector<T>& data, unsigned int row) {
		file.clear();
		file.seekg(dataStart + (row * sizeof(T) * ColumnNames.size()), ::std::ios::beg);

		data.clear();
		if(data.size() < ColumnNames.size())
			data.reserve(ColumnNames.size());
		T x;
		for (auto i = 0; i < ColumnNames.size(); i++) {
			if (file.eof())
				throw InvalidArgument("Row does not exist in file");
			file.read(reinterpret_cast<char*>(&x), sizeof(T));
			data.pushBack(x);
		}
	}

	template<typename T>
	void ReadFile<T>::getAll(Vector<Vector<T>>& data) noexcept {
		file.clear();
		file.seekg(dataStart, ::std::ios::beg);
		data.clear();
		T x;
		for (auto i = 0; !file.eof(); i++) {
			data.pushBack(Vector<T>(ColumnNames.size()));
			for (auto j = 0; j < ColumnNames.size() && file.read(reinterpret_cast<char*>(&x), sizeof(T)); j++)
				data[i].pushBack(x);
		}
	}

	template<typename T>
	std::vector<String> ReadFile<T>::getColumnNames() noexcept {
		return ColumnNames;
	}*/

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
	void newImplementation::ReadFile<T>::getColumn(Container& data, const::std::string& columnName) {
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
	void newImplementation::ReadFile<T>::getColumn(Container& data, const std::string& columnName) {
		assert(contains(columnName) && "the file does not contain a column of this name");
		assert(ContainerTraits<Container>::size() < _rowCount && "container is not big enough");

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
		const std::string& columnName, std::function<bool(const Container&)> condition) {
		assert(contains(columnName) && "the file does not contain a column of this name");

		moveReader(0);
		unsigned int columnNumber = column(columnName);
		Container temp = ContainerTraits<Container>::constructCapacity(columnCount());
		for (auto i = 0; i < _rowCount; i++) {
			readRow(temp);
			if(condition(temp))
				ContainerTraits<Container>::pushBack(data, temp[columnNumber]);
		}
	}

	template<BinarySerializable T>
	template<typename Container, StringIndexable StringContainer>
		requires NestedDynamicArray<Container, T>
	void newImplementation::ReadFile<T>::getColumns(Container& data, const StringContainer& columnNames) {
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		assert(std::ranges::all_of(columnNames, [&](const auto& name) {return contains(name); }) &&
			"one or more of the names does not exist in the file");

		OuterContainerTraits::reserve(data, columnNames.size());
		Container temp = InnerContainerTraits::constructCapacity(columnCount());
		unsigned int* columnNumbers = new unsigned int[columnNames.size()];
		for (auto i = 0; i < columnNames.size(); i++) {
			columnNumbers[i] = column(columnNames[i]);
			OuterContainerTraits::pushBack(data,
				InnerContainerTraits::constructCapacity(columnNames.size()));
		}
		moveReader(0);
		for (auto row = 0; row < _rowCount; row++) {
			readRow(temp);
			for (auto column = 0; column < columnNames.size(); column++)
				InnerContainerTraits::pushBack(OuterContainerTraits::at(data, column),
					temp[columnNumbers[row]]);
		}
		delete[] columnNumbers;
	}

	template<BinarySerializable T>
	template<typename Container, StringIndexable StringContainer>
		requires NestedArray<Container, T>
	void newImplementation::ReadFile<T>::getColumns(Container& data, const StringContainer& columnNames) {
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		assert(std::ranges::all_of(columnNames, [&](const auto& name) {return contains(name); }) &&
			"one or more of the names does not exist in the file");
		assert(OuterContainerTraits::size() < columnCount() && "container has to few columns");
		assert(InnerContainerTraits::size() < _rowCount && "container has to few rows");

		unsigned int columnNumbers[OuterContainerTraits::size()];
		for (auto i = 0; i < columnNames.size(); i++) {
			columnNumbers[i] = column(columnNames[i]);
		}
		moveReader(0);
		Vector temp(columnCount());
		for (auto row = 0; row < _rowCount; row++) {
			readRow(temp);
			for (auto column = 0; column < columnNames.size(); column++)
				InnerContainerTraits::at(OuterContainerTraits::at(data, column), row) = temp[columnNumbers[column]];
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getRow(Container& data, unsigned long long row) noexcept
	{
		assert(row <= _rowCount && "The specified row is outside the buffer");
		ContainerTraits<Container>::reserve(data, _columnNames.size());
		moveReader(rowLengthBytes() * row);
		readRow(data);
	}

	template<BinarySerializable T>
	template<typename Container>
		requires ArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::getRow(Container& data, unsigned long long row) noexcept {
		assert(row <= _rowCount && "The specified row is outside the buffer");
		assert(ContainerTraits<Container>::size());
		moveReader(rowLengthBytes() * row);
		readRow(data);
	}

	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayConcept<Container, T>
	bool newImplementation::ReadFile<T>::getRow(Container& data, ::std::function<bool(const Container&)> condition) noexcept
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
	bool newImplementation::ReadFile<T>::getRow(Container& data, std::function<bool(const Container&)> condition) noexcept
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
	void newImplementation::ReadFile<T>::getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition) noexcept
	{
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;

		moveReader(0);
		OuterContainerTraits::pushBack(data,
			InnerContainerTraits::constructCapacity(_columnNames.size()));
		for (auto i = 0; i < _rowCount; i++) {
			readRow(OuterContainerTraits::endElement(data));
			if (condition(OuterContainerTraits::endElement(data)))
				OuterContainerTraits::pushBack(data,
					InnerContainerTraits::constructCapacity(_columnNames.size()));
			InnerContainerTraits::clear(OuterContainerTraits::endElement(data));
		}
	}
	template<BinarySerializable T>
	template<typename Container>
		requires DynamicArrayArray<Container, T>
	void newImplementation::ReadFile<T>::getRows(Container& data, std::function<bool(const range_value_t<Container>&)> condition) noexcept {
		using OuterContainerTraits = ContainerTraits<Container>;
		using InnerContainerTraits = ContainerTraits<range_value_t<Container>>;
		
		moveReader(0);
		OuterContainerTraits::pushBack(data,
			InnerContainerTraits::constructCapacity(_columnNames.size()));
		for (auto i = 0; i < _rowCount; i++) {
			readRow(OuterContainerTraits::endElement(data));
			if (condition(OuterContainerTraits::endElement(data)))
				OuterContainerTraits::pushBack(data,
					InnerContainerTraits::constructCapacity(_columnNames.size()));
		}
	}

	template<BinarySerializable T>
	template<typename Container>
		requires NestedDynamicArray<Container, T>
	void newImplementation::ReadFile<T>::getAllColumns(Container& data) noexcept
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
		assert(OuterContainerTraits::size() == _columnNames.size());
		assert(InnerContainerTraits::size() == _rowCount);

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
	void newImplementation::ReadFile<T>::getAllRows(Container& data) noexcept
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
		assert(OuterContainerTraits::size() == _rowCount);
		assert(InnerContainerTraits::size() == _columnNames.size());

		moveReader(0);
		for (auto i = 0; i < _rowCount; i++) {
			readRow(data[i]);
		}
	}

	template<BinarySerializable T>
	const::std::vector<::std::string>& Database::newImplementation::ReadFile<T>::getColumnNames() const noexcept
	{
		return _columnNames;
	}
	template<BinarySerializable T>
	const unsigned int newImplementation::ReadFile<T>::columnCount() const noexcept {
		return _columnNames.size();
	}
	template<BinarySerializable T>
	const bool newImplementation::ReadFile<T>::contains(const CharSpan& name) {
		return std::find(_columnNames.begin(), _columnNames.end(), name) != _columnNames.end();
	}
	template<BinarySerializable T>
	const unsigned int Database::newImplementation::ReadFile<T>::rowLengthBytes() const noexcept
	{
		return columnCount() * sizeof(T);
	}
	template<BinarySerializable T>
	const unsigned long long Database::newImplementation::ReadFile<T>::dataLengthBytes() const noexcept
	{
		return _rowCount * rowLengthBytes();
	}

	template<BinarySerializable T>
	const unsigned long long newImplementation::ReadFile<T>::itemOffsetBytes(unsigned int column) const noexcept
	{
		return column * sizeof(T);
	}

	template<BinarySerializable T>
	const unsigned int newImplementation::ReadFile<T>::column(const CharSpan& name) const noexcept {
		return std::distance(_columnNames.begin(), std::find(_columnNames.begin(), _columnNames.end(), name));
	}

	template<BinarySerializable T>
	void newImplementation::ReadFile<T>::moveReader(::std::streamoff offset, ::std::ios_base::seekdir dir)
	{
		_file.seekg(offset + (dir == ::std::ios::beg) * _dataStart, dir);
	}

	template<BinarySerializable T>
	template<typename Container>
	requires DynamicArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::readRow(Container& data)
	{
		for (int i = 0; i < columnCount(); i++)
			ContainerTraits<Container>::pushBack(data, readItem());
	}

	template<BinarySerializable T>
	template<typename Container>
		requires ArrayConcept<Container, T>
	void newImplementation::ReadFile<T>::readRow(Container& data) {
		for (int i = 0; i < columnCount(); i++)
			ContainerTraits<Container>::at(data, i) = readItem();
	}

	template<BinarySerializable T>
	T newImplementation::ReadFile<T>::readItem()
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

		std::string temps;
		char tempc;
		for (int i = 0; i < columnNumber; _dataStart++) {
			_file.read(&tempc, sizeof(char));
			if (tempc == Database::_splitByte) {
				_columnNames.push_back(temps);
				temps.clear();
				i++;
				continue;
			}
			temps.push_back(tempc);
		}

		auto size = ::std::filesystem::file_size(filePath);
		_rowCount = (size - _dataStart) / rowLengthBytes();
	}
}