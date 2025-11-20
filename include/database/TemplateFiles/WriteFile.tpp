/*
Author: Loke Strøm
*/
#include "Exception.hpp"
#include "string.hpp"
#include <fstream>
#include "..\WriteFile.hpp"
#include "traits.hpp"
#include "concepts.hpp"

#include <filesystem>
#include <assert.h>

namespace Database {

	namespace newImplementation {
		template<BinarySerializable T>
		template<validfstreamFilePathFormat FilePathFormat>
		WriteFile<T>::WriteFile(const FilePathFormat& filename) noexcept
		{
			setup(filename);
		}

		template<BinarySerializable T>
		template<validfstreamFilePathFormat FilePathFormat>
		void WriteFile<T>::open(const FilePathFormat& filename) noexcept
		{
			assert(!is_open() && "File is open, must close before opening new one. State of file: failbit set.");
			setup(filename);
		}

		template<BinarySerializable T>
		bool WriteFile<T>::is_open() const noexcept
		{
			return _file.is_open();
		}

		template<BinarySerializable T>
		void WriteFile<T>::close() noexcept {
			_file.close();
		}

		template<BinarySerializable T>
		template<StringIndexable container>
		void WriteFile<T>::addColumns(const container& columnNames) noexcept
		{
			assert(!dataWritten && "Data has been written cant add columns");
			if (_columnCount == 0) {
				_file.write(reinterpret_cast<char*>(&_columnCount), sizeof(_columnCount));
			}
			for (const auto& name : columnNames) {
				_file.write(name.begin(), name.size());
				_file.write(&_splitByte, 1);
			}
			_columnCount += columnNames.size();
			_file.seekp(0);
			_file.write(reinterpret_cast<char*>(&_columnCount), sizeof(_columnCount));
			_file.seekp(0, std::ios::end);
		}
		template<BinarySerializable T>
		void WriteFile<T>::addColumns(const std::initializer_list<CharSpan>& names) noexcept
		{
			addColumns(std::vector<CharSpan>(names));
		}

		template<BinarySerializable T>
		template<typename Container>
			requires IterableArray<Container, T>
		void WriteFile<T>::addData(const Container& data) noexcept
		{
#ifdef _DEBUG
			dataWritten = true;
#endif
			assert(_columnCount == ContainerTraits<Container>::size(data) && "Input must be same size as column count");
			for (const T& i : data) {
				_file.write(reinterpret_cast<const char*>(&i), sizeof(i));
			}
		}

		template<BinarySerializable T>
		const unsigned int WriteFile<T>::getColumCount() const noexcept
		{
			return _columnCount;
		}

		template<BinarySerializable T>
		bool WriteFile<T>::fail() const noexcept
		{
			return _file.fail();
		}

		template<BinarySerializable T>
		bool WriteFile<T>::bad() const noexcept
		{
			return _file.bad();
		}

		template<BinarySerializable T>
		template<validfstreamFilePathFormat FilePathFormat>
		void WriteFile<T>::setup(const FilePathFormat& path) noexcept
		{
			bool existed = std::filesystem::exists(path);
			if (existed) {
				std::ifstream temp(path, std::ios::binary);
				temp.read(reinterpret_cast<char*>(&_columnCount), sizeof(_columnCount));

#ifdef _DEBUG
				char tempReadByte;
				int columnCounter = _columnCount;
				while (!temp.eof()) {
					temp.read(reinterpret_cast<char*>(&tempReadByte), 1);
					if (columnCounter == 0) {
						dataWritten = true;
						break;
					}
					if (tempReadByte == _splitByte)
						columnCounter--;
				}
#endif

				_file.open(path, std::ios::binary | std::ios::ate);
				return;
			}
			_file.open(path, std::ios::binary | std::ios::ate);
			_columnCount = 0;
		}
	}
}