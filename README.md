# dataStructure_Project3
## command:
	(in linux)
	1. g++ -std=c++11 project3.cpp -o project3
	2. ./project3 // 執行

## 執行結果：(example)
	time:  1   tag:   C6   index:   4E
	4C    NUL
	4C    NUL
	4C    NUL
	4C    NUL
	=====
	4E     C6
	4E    NUL
	4E    NUL
	4E    NUL
	=====
	Miss



	time:  2   tag:   C6   index:   4C
	4C     C6
	4C    NUL
	4C    NUL
	4C    NUL
	=====
	4E     C6
	4E    NUL
	4E    NUL
	4E    NUL
	=====
	Miss



	time: 11   tag:   C6   index:   4C
	4C     C6
	4C     C7
	4C    NUL
	4C    NUL
	=====
	4E     C6
	4E     F8
	4E     F6
	4E     F7
	=====
	Hit



	time: 12   tag:   C7   index:   4E
	4C     C6
	4C     C7
	4C    NUL
	4C    NUL
	=====
	4E     C6
	4E     F8
	4E     C7
	4E     F7
	=====
	Miss
	
### example:
	C64E5
	C64C5
	C74EA
	C64E8
	C64CF
	F64E6
	F74EA
	F84E6
	C74CF
	C64E6
	C64C9
	C74E8

## 系統流程：
	1. 讀擋
	2. 讀擋完成後將資料存成以下結構
	int cacheSize = 0;
	int block = 0;
	int way = 0;
	int k = 0;
	int offset, index, tag = 0;
	vector<string> tagName;
	vector<string> indexName;
	vector<vector<string> > cache;
	// 使用LRU，作法是每跑一次將未使用到的每個way做count++
	// 並將使用過的歸零，需要replacement時找count數最大的去做取代
	vector<vector<int> > noUseCount;
	vector<string> hitOrMiss;
	
	3. 資料儲存好以後，開始執行replacement
	4. 輸出結果

## Function：

* void cal() // 計算tag, index, offset
* string GetBinaryStringFromHexString() // 16進制轉2進制
* void doLRU(vector<string> indexTemp)
* int haveSpace(int location) // 如果cache裡面有NUL(有空間可以直接放)，return location
* int findFirstIn(int location) // 找到最早進去的tag
* void doFIFO(vector<string> indexTemp)

#### input：
	cout << "set k-bit address:" << endl << "k = ";
	cin >> k;
	cout << endl << "input cache data size(KB):" << endl;
	cin >> cacheSize;
	cout << endl << "input block size(byte):" << endl;
	cin >> block;
	cout << endl << "input N-way set associative:" << endl << "N = ";
	cin >> way;
	int choose = -1;
	do {
		cout << endl << "choose: 1->FIFO, 2->LRU" << endl;
		cin >> choose;
	} while (choose != 1 && choose != 2);
	
	cal();

	一開始先設定所需要的資料
	再利用cal()去計算出tag index offset

#### 讀檔：
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
	
	先把讀進的檔案的值16進制轉成2進制
	再依據剛才算出的tag index樹進行存取
	
#### execute：
	if (choose == 2) {
		doLRU(indexTemp);
	}
	else if (choose == 1) {
		doFIFO(indexTemp);
	}
	
	根據一開始輸入的去選擇要做哪一種cache replacement

	void doLRU(vector<string> indexTemp) {
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
				for (int j = noUseCount[location].size() - 1; j >= 0; j--) { // find max count_value to replace
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
	}
