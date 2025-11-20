/*
Athor: Loke Strøm
*/
#pragma once

#include "Vector.hpp"
#include "String.hpp"
#include "concepts.hpp"
#include "traits.hpp"

#include <fstream>

namespace Database
{
    namespace newImplementation {
        template<BinarySerializable T>
        class WriteFile {
        public:
            WriteFile() noexcept;
            template<validfstreamFilePathFormat FilePathFormat>
            WriteFile(const FilePathFormat& filename) noexcept;

            WriteFile(const WriteFile<T>&) = delete;
            WriteFile& operator=(const WriteFile<T>&) = delete;
            WriteFile(WriteFile<T>&& writeFile) noexcept = default;
            WriteFile& operator=(WriteFile<T>&&) noexcept = default;

            ~WriteFile() noexcept = default;

            template<validfstreamFilePathFormat FilePathFormat>
            void open(const FilePathFormat& filename) noexcept;
            bool is_open() const noexcept;
            void close() noexcept;
            
            template<StringIndexable container>
            void addColumns(const container& columnNames) noexcept;
            void addColumns(const std::initializer_list<CharSpan>& names) noexcept;

            template<typename Container>
                requires IterableArray<Container, T>
            void addData(const Container& data) noexcept;

            const unsigned int getColumCount() const noexcept;

            bool fail() const noexcept;
            bool bad() const noexcept;

        private:
            template<validfstreamFilePathFormat FilePathFormat>
            void setup(const FilePathFormat& path) noexcept;
        private:
            std::ofstream _file;
            unsigned int _columnCount;
#ifdef _DEBUG
            bool dataWritten;
#endif
        };
    }
}

#include "TemplateFiles/WriteFile.tpp"