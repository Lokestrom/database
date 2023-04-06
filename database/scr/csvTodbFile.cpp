#include "WriteFile.hpp"

using namespace Database;

void csvTodbFile(String fileName) {
	std::ifstream csvFile(toSTD(fileName));
	WriteFile<long double> dbFile(fileName.split('.')[0] + ".db");
	
	String data;
	getline(csvFile, data);
	dbFile.addcolumns(data.split(','));
	
	while (getline(csvFile, data)) {
		Vector<long double> ldData;
		for (String i : data.split(','))
			ldData.pushBack(STold(i));
		dbFile.addData(ldData);
	}
	csvFile.close();
	dbFile.close();
}