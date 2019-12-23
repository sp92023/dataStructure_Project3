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
