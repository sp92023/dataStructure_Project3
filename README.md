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
	// 將instruction分別記錄以下結構 ex: add R1,R2,R3
	// instFirst會記錄R1
	// instSecond會記錄R2
	// instThird會記錄R3
	// instName會記錄add
	vector<string> instFirst;
	vector<string> instSecond;
	vector<string> instThird;
	vector<string> instName;
	
	vector<string> regName; // 紀錄每個register的名字
	vector<int> regValue; // 紀錄每個register的值
	vector<vector<string> > addRs;
	vector<vector<string> > mulRs;
	vector<string> rat;
	string first, second, third;
	int cycle = 0;
	vector<string> addBuffer; // 0:RS, 1:operation, 2:result, 3:cycle, 4:tag
	// buffer內存五個值，第一個存RAT所對應的RS，第二個存式子，第三個存執行後的結果，第四個存在第幾個cycle會write back，第五個存tag
	vector<string> mulBuffer;
	vector<int> ratTag;
	vector<int> addTag;
	vector<int> mulTag;
	
	3. 資料儲存好以後，開始執行tomasulo
	4. 輸出結果

## Function：

* bool addRSisEnough(), bool mulRSisEnough() // 判斷RS裡面是否有空間可以issue
* int returnAddRsloca(), int returnMulRsloca() // 當RS裡面有空間可以issue時，回傳所要儲存的location資訊
* pair<bool, int> addRsisReady(), pair<bool, int> mulRsisReady() // 判斷RS裡面，是否可以做dispatch(沒有RSX在RS裡面)，如果有已經準備完成的RS，回傳true並回傳RS location
* void addRsValueUpdate(), void mulRsValueUpdate() // buffer釋出後，更新RAT和RS裡面的資訊
* string ifHaveRat() // 當RAT裡面有值，拿取RAT裡面資訊，否則直接使用RF裡面的值
