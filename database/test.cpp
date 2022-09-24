#include <fstream>
#include <iostream>
#include "String.hpp"
#include <filesystem>
namespace fs = std::filesystem;

using namespace Database;

std::ifstream* ifile;
std::ofstream* ofile;
Vector<String>* fileName;

class definitions {
public:
	Vector<char> fungtionCharList;
	Vector<char> fungtionArgsCharList;
	Vector<String> blueWords;
	Vector<String> greenWords;
	definitions() {
		for (int i = 48; i < 58; i++)
			fungtionCharList.pushBack(char(i));
		for (int i = 65; i < 91; i++)
			fungtionCharList.pushBack(char(i));
		fungtionCharList.pushBack(char(95));
		for (int i = 97; i < 123; i++)
			fungtionCharList.pushBack(char(i));
		fungtionCharList.pushBack(char(126));

		fungtionArgsCharList = { char(32), char(44) };
		fungtionArgsCharList += fungtionCharList;

		blueWords = { "class", "template", "typename", "char", "int", "double", "float", "long", "short", "unsigned", "signed", "auto" };
		greenWords = { "T" };
		String path = "documetasion\\classes";
		for (const auto& entry : fs::directory_iterator(toSTD(path)))
			greenWords.pushBack(String(entry.path().string()));
	}
};

bool green(const String& s, int i);

String findLocalFungtionFile(String& s) {
	if (green((*fileName)[fileName->size() - 2], 0))
		return "documentation/" + (*fileName)[fileName->size() - 2] + '/' + s + ".html";
	else if (green((*fileName)[fileName->size() - 1].split('.')[0], 0))
		return "documentation/" + (*fileName)[fileName->size() - 1].split('.')[0] + '/' + s + ".html";
	return "";
}

String findClassFile(String& s) {
	return "documentation/classes/" + s + ".html";
}

String findClassFungtionFile(String& className, String& s) {
	return "documentation/" + className + '/' + s + ".html";
}

bool manual(const String& s, int i) {
	if (s[i] == '<')
		for (; i < s.length(); i++)
			if (s[i] == '>')
				for (; i < s.length()-1; i++)
					if (s[i] == '<' && s[i + 1] == '>')
						return true;
	return false;
}

bool classFungtion(const String& s, int i) {
	if (s[i] == '.')
		return localFungtion(s, i);
	return false;
}

bool definitionFungtion(const String& s, int i) {
	if ((*fileName)[fileName->size() - 1].split('.')[0] == s(i, s.length()).split('(')[0]) {
		return true;
	}
	return false;
}

bool localFungtion(const String& s, int i) {
	definitions d;
	for (; i < s.length() - 1; i++) {
		if (s[i] == '(')
			for (; i < s.length(); i++) {
				if (s[i] == ')')
					return true;
				else if (d.fungtionArgsCharList.binarySerch(s[i]))
					return false;
			}

		else if (d.fungtionCharList.binarySerch(s[i]) == -1)
			return false;
	}
	return false;
}

bool string(const String& s, int i) {
	if (s[i] == '"')
		for (; i < s.length(); i++)
			if (s[i] == '"')
				return true;
	return false;
}

bool blue(const String& s, int i) {
	if (s[i] == ' ')
		return false;
	definitions d;
	String word = s(i, s.length());
	word = word.split(' ')[0];

	for (const String& j : d.blueWords)
		if (word == j)
			return true;
	return false;
}

bool green(const String& s, int i) {
	if (s[i] == ' ')
		return false;
	definitions d;
	String word = s(i, s.length());
	word = word.split(' ')[0];
	word = word.split('.')[0];

	for (const String& j : d.greenWords)
		if (word == j)
			return true;
	return false;
}

void fileWriter(const String& s, const String type) {
	*ofile << "<" << type << ">";
	String r = s;
	String sub;
	for (auto i = 0; i < s.length();) {
		if (manual(s, i)) {
			*ofile << '\n';
			i++;
			sub.clear();
			for (; s[i] != ',' && s[i] != '>'; i++)
				sub.pushBack(s[i]);
			if (sub != "")
				*ofile << "<a class=\"" << sub << "\"";

			if (s[i] == ',') {
				i++;
				sub.clear();
				for (; s[i] != '>'; i++)
					sub.pushBack(s[i]);
				*ofile << " href=\"" << sub << "\"";
			}
			*ofile << ">";
			sub.clear();
			for (; s[i] != '<' && s[i + 1] != '>'; i++)
				sub.pushBack(s[i]);
			*ofile << sub;
			i += 2;
			*ofile << "</a>\n";
			continue;
		}

		if (string(s, i)) {
			sub.clear();
			sub.pushBack(s[i]);
			i++;
			for (bool first = true; (s[i-1] != '"' && s[i-1] != '\'') || first; first = false, i++)
				sub.pushBack(s[i]);
			*ofile << "<a class=\"string\">" << sub << "</a>\n";
			continue;
		}

		if (classFungtion(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != '('; i++)
				sub.pushBack(s[i]);

			*ofile << "<a class=\"fungtion\">" << sub << "</a>\n(";
			i++;
			continue;
		}

		if (localFungtion(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != '('; i++)
				sub.pushBack(s[i]);

			String file = findLocalFungtionFile(sub);
			*ofile << "<a class=\"fungtion\"";
			if (file.length() != 0)
				*ofile << " href=\"" << file << "\"";
			*ofile << ">" << sub << "</a>\n(";
			continue;
		}

		if (green(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != '.' || s[i] != ' '; i++)
				sub.pushBack(s[i]);

			String file = findClassFile(sub);
			*ofile << "<a class=\"classGreen\"";
			if (file.length() != 0)
				*ofile << " href=\"" << file << "\"";
			*ofile << ">" << sub << "</a>\n";

			if (classFungtion(s, i)) {
				String className = sub;
				sub.clear();
				i++;
				for (;s[i] != '('; i++)
					sub.pushBack(s[i]);
				file = findClassFungtionFile(className, sub);
				*ofile << ".\n";
				*ofile << "<a class=\"fungtion\" href=\"" << file << "\">" << sub << "</a>\n";
				*ofile << "(";
				i++;
			}
			continue;
		}

		if (blue(s, i)) {
			*ofile << '\n';
			sub.clear();
			for (; s[i] != ' '; i++)
				sub.pushBack(s[i]);
			*ofile << "<a class=\"blue\">" << sub << "</a>\n";
			continue;
		}

		*ofile << s[i];
		i++;
	}
	*ofile << "<" << type.split(' ')[0] << ">\n";
}

void FungtionList(String s) {
	Vector<String> v(s.split(':'));
	*ofile << "<tr>\n"
		<< "<th><a class = \"blue\" href = \"" + findLocalFungtionFile(v[0]) + "\">" + v[0] + "</a></th>\n"
		<< "<th>";
	fileWriter(v[1], "span");
	*ofile << "</th>\n"
		<< "</tr>\n";
}

void subList(String s) {
	s.popBack();
	*ofile << "<tr>\n"
		<< "<th>\n"
		<< "<h4 style=\"line-height: 0px;\">" + s + "</h4>\n"
		<< "</th>\n"
		<< "</tr>\n";
}

int main(int argc)
{
	String argv[] = { "a", "String.txt" };
	fileName = new Vector<String>(argv[1].split('/'));
	ifile = new std::ifstream("String.txt");
	ofile = new std::ofstream("out.html");
	String text;
	String className = argv[1].split('.')[0];

	*ofile << "<!DOCTYPE html>\n"
		<< "<head>\n"
		<< "	<link rel = \"stylesheet\" href=\"../documentationStyles/all.css\">\n"
		<< "	<link rel=\"stylesheet\" href=\"../documentationStyles/class.css\">\n"
		<< "</head>\n\n"
		<< "<header>\n"
		<< "	<a class = \"homeButton\" href=\"../main.html\">Home</a>\n"
		<< "    <h1 class = \"white underline\">" << className << "</h1>\n"
		<< "</header>\n\n"
		<< "<body class=\"background white\">\n"
		<< "	<div>\n"
		<< "		<p class=\"header\">\n"
		<< "			<span>Defined in header</span>\n"
		<< "			<a href=\"https://github.com/Lokestrom/database/blob/main/database/" << className << ".hpp\">" << "\"" << className << ".hpp\"" << "</a>\n"
		<< "			<br>\n"
		<< "			<span>Code in</span>\n";

	getline(ifile, text);
	text.lower();
	if (text.contains("github")) {
		if (text.contains("cpp"))
			*ofile << "			<a href=\"https://github.com/Lokestrom/database/blob/main/database/" << className << ".cpp\">" << "\"" << className << ".cpp\"" << "</a>\n";
		if (text.contains("cpp") && text.contains("tpp"))
			*ofile << "<span> and </span>\n";
		if (text.contains("tpp"))
			*ofile << "			<a href=\"https://github.com/Lokestrom/database/blob/main/database/" << className << ".tpp\">" << "\"" << className << ".tpp\"" << "</a>\n";
	}
	
	*ofile << "		</p>\n"
		<< "		<p class=\"definition\">\n";
	while(getline(ifile, text)){
		text.lower();
		if (text.contains("class defintition")) {
			getline(ifile, text);
			String definition = text;
			getline(ifile, text);
			if(text != "}")
				definition += "<br>" + text;
			fileWriter(definition, "p class=\"definition\"");
		}
	}

	while (getline(ifile, text)) {
		text.lower();
		if (!text.contains("class description"))
			continue;
		String description = "";
		for (; text != "}"; getline(ifile, text))
			description += text + "\n<br>\n";
		description.pop(description.length() - 7, description.length());
		fileWriter(description, "span class=\"description\"");
	}

	*ofile << "    <br><br> \n <h2 style=\"line-height: 0px;\"> Member fungtions </h2>\n\n <table class=\"linkToFungtionsTable\">";

	while (getline(ifile, text)) {
		text.lower();
		if (!text.contains("member fungtions"))
			continue;
		for (; text != "}"; getline(ifile, text)) {
			if (text.contains(":")) 
				FungtionList(text);

			else if (text.contains("{")) {
				subList(text(0, text.length()));
				for (; text != "}"; getline(ifile, text))
					if (text.contains(":"))
						FungtionList(text);
			}
		}
		*ofile << "</table>\n";
	}

	while (getline(ifile, text)) {
		text.lower();
		if (text.contains("non-member fungtions")) {
			*ofile <<  "<br>\n<h2 style = \"line-height: 0px;\">Non - Member fungtions< / h2>\n<table class = \"linkToFungtionsTable\">";
			for (; text != "}"; getline(ifile, text)) {
				if (text.contains(":"))
					FungtionList(text);

				else if (text.contains("{")) {
					subList(text(0, text.length()));
					for (; text != "}"; getline(ifile, text))
						if (text.contains(":"))
							FungtionList(text);
				}
			}
		}
		*ofile << "</table>";
	}
	
	*ofile << "<br><br><br><br><br><br><br><br><br>\n</body>";

	delete ifile;
	delete ofile;
	delete fileName;
}