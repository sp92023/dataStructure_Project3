// project3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int cacheSize = 0;
int block = 0;
int way = 0;
int k = 0;
int offset, index, tag = 0;
vector<string> tagName;
vector<string> indexName;
vector<vector<string> > cache;
vector<vector<int> > noUseCount;
vector<string> hitOrMiss;

void cal();
void printAddr();
string GetBinaryStringFromHexString(string sHex);
string toHex(string s);

int main()
{
	//std::cout << "Hello World!\n";

	cout << "set k-bit address:" << endl << "k = ";
	cin >> k;
	cout << "input cache data size(KB):" << endl;
	cin >> cacheSize;
	cout << endl << "input block size(byte):" << endl;
	cin >> block;
	cout << endl << "input N-way set associative:" << endl << "N = ";
	cin >> way;
	//k = 20;
	//cacheSize = 16;
	//block = 16;
	//way = 4;

	cal();
	printAddr();

	ifstream input;
	vector<string> inputContent;
	string inp;
	input.open("example.txt", ios::in);
	if (!input) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}

	while (!input.eof()) {
		while (getline(input, inp, '\n')) {
			inputContent.push_back(inp);
		}
	}

	for (int i = 0; i < inputContent.size(); i++) {
		inputContent[i] = GetBinaryStringFromHexString(inputContent[i]);
	}

	for (int i = 0; i < inputContent.size(); i++) {
		string s = "";
		for (int j = 0; j < tag; j++) {
			s.push_back(inputContent[i][j]);
		}
		tagName.push_back(toHex(s));
	}
	for (int i = 0; i < inputContent.size(); i++) {
		string s = "";
		for (int j = tag; j < tag + index; j++) {
			s.push_back(inputContent[i][j]);
		}
		indexName.push_back(toHex(s));
	}
	for (int i = 0; i < inputContent.size(); i++) {
		cout << "tag" << setw(3) << i << ": " << setw(7) << tagName[i] << "   " 
			<< "index" << setw(3) << i << ": " << setw(7) << indexName[i] << endl;
	}
	cout << endl;

	vector<string> indexTemp;
	vector<string>::iterator it;
	indexTemp.assign(indexName.begin(), indexName.end());
	sort(indexTemp.begin(), indexTemp.end());
	it = unique(indexTemp.begin(), indexTemp.end());
	indexTemp.resize(distance(indexTemp.begin(), it));
	//cout << indexTemp.size() << endl;
	//for (int i = 0; i < indexTemp.size(); i++)
	//	cout << indexTemp[i] << endl;

	vector<string> set;
	vector<int> count;
	for (int i = 0; i < way; i++) {
		set.push_back("NUL");
		count.push_back(0);
	}
	for (int i = 0; i < indexTemp.size(); i++) { // initial cache and count
		cache.push_back(set);
		noUseCount.push_back(count);
	}

	// do replacement
	for (int i = 0; i < tagName.size(); i++) {
		cout << "time:" << setw(3) << i + 1 << 
			setw(7) << "tag:" << setw(5) << tagName[i] << 
			setw(9) << "index:" << setw(5) << indexName[i] << endl;

		int location;
		for (int j = 0; j < indexTemp.size(); j++) {
			if (indexTemp[j] == indexName[i]) { // need to know which set
				location = j;
				break;
			}
		}

		bool isFind = false;
		for (int j = 0; j < cache[location].size(); j++) {
			noUseCount[location][j]++; // count++
			if (cache[location][j] == tagName[i]) { // if found, update count
				noUseCount[location][j] = 0;
				hitOrMiss.push_back("Hit");
				isFind = true;
			}
		}
		if (isFind == false) {
			int changeLocation = 0;
			int max = -1;
			for (int j = noUseCount[location].size()-1; j >= 0; j--) { // find max count_value to replace
				if (noUseCount[location][j] >= max) {
					max = noUseCount[location][j];
					changeLocation = j;
				}
			}

			noUseCount[location][changeLocation] = 0; // update count
			cache[location][changeLocation] = tagName[i]; // replace cache tag
			hitOrMiss.push_back("Miss");
		}

		for (int j = 0; j < cache.size(); j++) {
			for (int k = 0; k < cache[j].size(); k++) {
				cout << indexTemp[j] << setw(7) << cache[j][k] << endl;
			}
			cout << "=====" << endl;
		}
		cout << hitOrMiss[i] << endl;
		cout << endl << endl << endl;
	}
	// end replacement

	//for (int i = 0; i < hitOrMiss.size(); i++)
	//	cout << hitOrMiss[i] << endl;
	system("pause");
}

void cal() {
	offset = log2(block);
	index = log2((cacheSize * 1024 / block) / way);
	tag = k - (offset + index);
}

void printAddr() {
	cout << "tag: " << tag << setw(10)
		<< "index: " << index << setw(11)
		<< "offset: " << offset << endl << endl;
}

string GetBinaryStringFromHexString(string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length(); ++i)
	{
		switch (sHex[i])
		{
		case '0': sReturn.append("0000"); break;
		case '1': sReturn.append("0001"); break;
		case '2': sReturn.append("0010"); break;
		case '3': sReturn.append("0011"); break;
		case '4': sReturn.append("0100"); break;
		case '5': sReturn.append("0101"); break;
		case '6': sReturn.append("0110"); break;
		case '7': sReturn.append("0111"); break;
		case '8': sReturn.append("1000"); break;
		case '9': sReturn.append("1001"); break;
		case 'A': sReturn.append("1010"); break;
		case 'B': sReturn.append("1011"); break;
		case 'C': sReturn.append("1100"); break;
		case 'D': sReturn.append("1101"); break;
		case 'E': sReturn.append("1110"); break;
		case 'F': sReturn.append("1111"); break;
		}
	}
	return sReturn;
}

string toHex(string s) {
	string sReturn = "";
	for (int i = 0; i < s.length(); i += 4)
	{
		string ss = "";
		for (int j = i; j < i + 4; j++) {
			ss.push_back(s[j]);
		}
		if (ss == "0000") {
			sReturn.append("0");
		}
		else if (ss == "0001") {
			sReturn.append("1");
		}
		else if (ss == "0010") {
			sReturn.append("2");
		}
		else if (ss == "0011") {
			sReturn.append("3");
		}
		else if (ss == "0100") {
			sReturn.append("4");
		}
		else if (ss == "0101") {
			sReturn.append("5");
		}
		else if (ss == "0110") {
			sReturn.append("6");
		}
		else if (ss == "0111") {
			sReturn.append("7");
		}
		else if (ss == "1000") {
			sReturn.append("8");
		}
		else if (ss == "1001") {
			sReturn.append("9");
		}
		else if (ss == "1010") {
			sReturn.append("A");
		}
		else if (ss == "1011") {
			sReturn.append("B");
		}
		else if (ss == "1100") {
			sReturn.append("C");
		}
		else if (ss == "1101") {
			sReturn.append("D");
		}
		else if (ss == "1110") {
			sReturn.append("E");
		}
		else if (ss == "1111") {
			sReturn.append("F");
		}
	}
	return sReturn;
}
// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
