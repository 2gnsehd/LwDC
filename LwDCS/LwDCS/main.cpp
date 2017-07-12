/*
*	TODO:
*   1. 딜레이를 할 수 있는 시간은 넣었다. 따라서, 스케줄링을 구현해야한다.
*   2. 즉, 먼저 처리를 해야하는 개념이 없다. 현재로선...
*/

#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h> 

using namespace std;

enum isSchedule {
	NO = 0,
	YES = 1,
	PROCESS = 2
};

/*
* 시뮬레이션을 위한 전역 변수
*/

long long global_under_Sec = 0;
long long global_upper_Sec = 0;
int sizeModule = 0;;
int nowSechduleNumber = 0;
/*
* Calss: 스케줄러를 위한 클래스
*/

class infoModule
{
public:
	infoModule* next;
	string name;
	int number;
	long long under_Sec;
	long long upper_Sec;
};

class vScheduler {
public:
	infoModule* head;
	infoModule* tail;
	int length;

	vScheduler();
	void addNode(int number, long long upper_Sec, long long under_Sec);
	int getLength();
	void deleteList();
	void printAllData();
	void compareTime();
};

vScheduler::vScheduler() {
	this->length = 0;
	this->head = NULL;
	this->tail = NULL;
}

void vScheduler::addNode(int number, long long upper_Sec, long long under_Sec) {
	infoModule* node = new infoModule();
	if (length == 0)
	{
		this->head = node;
		this->tail = node;
		this->head->upper_Sec = upper_Sec;
		this->head->under_Sec = under_Sec;
		this->head->number = number;
		this->length++;
	}

	else
	{
		this->tail->next = node;
		this->tail = node;
		this->tail->upper_Sec = upper_Sec;
		this->tail->under_Sec = under_Sec;
		this->tail->number = number;
		this->length++;
	}
}

void vScheduler::deleteList() {
	delete this;
}

int vScheduler::getLength() {
	return this->length;
}

void vScheduler::printAllData() {
	infoModule* head = this->head;
	int i = 1;
	cout << "입력된 시간 값" << endl;
	while (head) {
		cout << "Node upper sec" << i << " - " << head->upper_Sec << endl;
		cout << "Node under sec" << i << " - " << head->under_Sec << endl;
		head = head->next;
		i++;
	}
	cout << endl;
}

// 여러 가지 vTime 클래스 중 가장 빠른(숫자입장에선 작은) 시간을 가진 클래스 추출
// 그러려면 구조체가 필요할듯...
// 각 vTime의 클래스의 주소 값을 알고 있어야 할듯!
void vScheduler::compareTime() {
	//1. 전체 vTime 클래들 중에서 upper_Sec의 min 값을 구한다.
	//2. 전체 min 값과 같은 vTime class들의 배열을 만든다.
	//3. 추려진 배열에서 down_Sec의 min 값을 구한다.
	//4. 그 중 하나를 처리한다.

	infoModule* tmpHead = new infoModule();
	infoModule* min_upper_Sec_Array;
	infoModule* min_under_Sec_Array;

	long long min_upper_Sec = 10000000000000;
	int size_min_upper_Sec = 0;

	long long min_under_Sec = 10000000000000;
	int size_min_under_Sec = 0;

	int tmpsize = 0;
	//upper Second 최소값 검색
	tmpHead = this->head;
	while (tmpHead)
	{
		if (min_upper_Sec > tmpHead->upper_Sec)
		{
			min_upper_Sec = tmpHead->upper_Sec;
		}
		tmpHead = tmpHead->next;
	}

	//upper Second 최소값인 모듈 개수 계산
	tmpHead = this->head;
	while (tmpHead)
	{
		if (min_upper_Sec == tmpHead->upper_Sec)
		{
			size_min_upper_Sec++;
		}
		tmpHead = tmpHead->next;
	}

	//upper Second 최소값인 모듈만큼 배열 다시 생성
	//under Second 값도 동시에 저장해줘야 함.
	tmpHead = this->head;
	min_upper_Sec_Array = new infoModule[size_min_upper_Sec];
	tmpsize = 0;
	while (tmpHead)
	{
		if (min_upper_Sec == tmpHead->upper_Sec)
		{
			min_upper_Sec_Array[tmpsize].number = tmpHead->number;
			min_upper_Sec_Array[tmpsize].upper_Sec = tmpHead->upper_Sec;
			min_upper_Sec_Array[tmpsize].under_Sec = tmpHead->under_Sec;
			tmpsize++;
		}
		tmpHead = tmpHead->next;
	}

	// -----------------------------------------------------

	//under Second 최소값 검색
	for (int i = 0; i<size_min_upper_Sec; i++)
	{
		if (min_under_Sec > min_upper_Sec_Array[i].under_Sec)
		{
			min_under_Sec = min_upper_Sec_Array[i].under_Sec;
		}
	}

	//under Second 최소값인 모듈 개수 계산
	for (int i = 0; i<size_min_upper_Sec; i++)
	{
		if (min_under_Sec == min_upper_Sec_Array[i].under_Sec)
		{
			size_min_under_Sec++;
		}
	}

	//under Second 최소값 검색최소값인 모듈만큼 배열 다시 생성
	min_under_Sec_Array = new infoModule[size_min_under_Sec];
	tmpsize = 0;
	for (int i = 0; i<size_min_upper_Sec; i++)
	{
		if (min_under_Sec == min_upper_Sec_Array[i].under_Sec)
		{
			min_under_Sec_Array[tmpsize].number = min_upper_Sec_Array[i].number;
			min_under_Sec_Array[tmpsize].upper_Sec = min_upper_Sec_Array[i].upper_Sec;
			min_under_Sec_Array[tmpsize].under_Sec = min_upper_Sec_Array[i].under_Sec;

			tmpsize++;
		}
	}

	//global_upper_Sec = min_upper_Sec_Array[0].upper_Sec;
	//global_under_Sec = min_upper_Sec_Array[0].under_Sec;
	if(global_upper_Sec <= min_under_Sec_Array[0].upper_Sec && global_under_Sec <= min_under_Sec_Array[0].under_Sec)
	{
		global_upper_Sec = min_under_Sec_Array[0].upper_Sec;
		global_under_Sec = min_under_Sec_Array[0].under_Sec;
		nowSechduleNumber = min_under_Sec_Array[0].number;
		cout << global_under_Sec << "Global Under Sec" << endl;
	}
	// 초기화

	delete tmpHead;
	delete[]min_upper_Sec_Array;
	delete[]min_under_Sec_Array;
	this->deleteList();
	/*
	cout << "가장 빠른 시간 값" << endl;
	cout << "Minimum, upperSec - " << min_under_Sec_Array[0].upper_Sec << endl;
	cout << "Minimum, underSec - " << min_under_Sec_Array[0].under_Sec << endl;
	cout << "가장 빠른 시간 값을 가진 객체 개수 " << size_min_under_Sec << endl;
	cout << endl << endl;
	*/
};



/*
* Calss: 메시지를 위한 클래스
*/

class Signal {
public:
	long long maked_under_Sec = 0;					//메시지가 만들어진 under_Sec / 초기에만 바꾸고 절대 바꾸지 않음
	long long maked_upper_Sec = 0;					//메시지가 만들어진 upper_Sec / 초기에만 바꾸고 절대 바꾸지 않음

	long long processed_under_Sec = 0;				//메시지가 가장 최근에 처리된 under_Sec / 즉, 여러 Hop을 걸칠때마다 변경
	long long processed_upper_Sec = 0;				//메시지가 가장 최근에 처리된 upper_Sec / 즉, 여러 Hop을 걸칠때마다 변경
};

class Msg : public Signal {
public:
	int tmpMsg;
};

/*
* Calss: 모듈을 위한 클래스
*/
class Module {
public:

	/*
	* 본 Class만 수정할 변수.
	*/
	string name;									//모듈 이름
	uint32_t number;								//모듈 번호
	bool isBusy = false;							//지금 바쁜가?
	bool isTask = true;								//더이상 처리할 것이 없는가?
	isSchedule isTxSchedule = NO;						//스케줄링 차례인가?
	isSchedule isRxSchedule = NO;

	long long schedule_under_Sec = 0;				//처리해야할 under_Sec
	long long schedule_upper_Sec = 0;				//처리해야할 upper_Sec
	long long delay = 0;							//딜레이 계산

													/*
													* 본 Class만 수정할 Class
													*/
	Module *Connection;								   //연결된 곳
	Msg *TxFIFO;									   //크기가 1인 송신용 FIFO
	Msg *RxFIFO;									   //크기가 1인 수신용 FIFO

													   /*
													   * 다른 Class도 수정할 변수.
													   */
	bool isTxIRQ = false;
	bool isRxIRQ = false;


	/*
	* 다른 Class도 수정할 Class
	*/
	Msg *IRQMsg;									 //이벤트로 일어난 임시 메시지

													 /*
													 * 애플리케이션용 변수
													 */
	int RxCount = 0;									//보낸 횟수

													/*
													* Modul 관련 함수들
													*/
	Module(string name, int number);
	void Init();															//생성자
	void txMsg(Msg *TxFIFO, long long delay);												//메세지 송신
	void rxMsg(Msg *RxFIFO);												//메세지 수신
	void setConnection(Module *Connection);									//모듈 연결
	void setScheduleTime(long long upper_Sec, long long under_Sec);				//나의 다음 스케줄 시간
	long long getScheduleTime(bool under_upper_Sec);
	void vTask();															//프로세스 역할을 하는 테스크
	void vTaskOver();														//개별 테스크 끝을 알림
	bool getIsTask();														//현재 테스크의 상황을 확인
	int getNumber();

};

int Module::getNumber() {
	return this->number;
}

Module::Module(string name, int number) {
	this->name = name;
	this->number = number;
	this->TxFIFO = new Msg();
	this->RxFIFO = new Msg();
	this->IRQMsg = new Msg();
}

void Module::Init()
{
	if (!this->name.compare("Module1")) {
		//생성된 시간을 저장한다.
		this->TxFIFO->tmpMsg = 100;
		this->TxFIFO->maked_under_Sec = 500;
		this->TxFIFO->maked_upper_Sec = 0;
		this->TxFIFO->processed_under_Sec = this->TxFIFO->maked_under_Sec;
		this->TxFIFO->processed_upper_Sec = this->TxFIFO->maked_upper_Sec;

		isTxIRQ = true;
		this->txMsg(this->TxFIFO, 500);
	}

	if (!this->name.compare("Module3")) {
		//생성된 시간을 저장한다.
		this->TxFIFO->tmpMsg = 200;
		this->TxFIFO->maked_under_Sec = 0;
		this->TxFIFO->maked_upper_Sec = 0;
		this->TxFIFO->processed_under_Sec = 0;
		this->TxFIFO->processed_under_Sec = 0;

		isTxIRQ = true;
		this->txMsg(this->TxFIFO, 0);
	}
}

void Module::vTaskOver()
{
	this->isTask = false;
}

bool Module::getIsTask()
{
	return this->isTask;
}

/*
	Module::txMsg
	1. 송신할 메시지가 있는지 판단한다.
	2. 메시지를 송신할 시간이 정해져 있는지 판단한다.
		NO : 메시지를 송신할 시간이 정해져 있지 않는 경우이다.
		YES : 메시지를 송신할 시간이 정해진 경우이다.
			  스케줄러는 이벤트를 발생할 모듈의 번호를 함께 남기는 데, 이게 자신의 모듈과 일치하고
			  현재의 상태가 YES이면 PROCESS 상태로 바꾼다.
		PROCESS : 송신할 메시지를 처리한다.
	3. 커네셕인 무엇인지 확인하고 딜레이를 계산한다. 현재는 1ns를 추가한 것
	4. 커넥션이 어딘지 확인한다.   this->Connection
	5. 커넥션 된 곳의 수신되고 있는 메시지를 바꾸어준다.
*/
void Module::txMsg(Msg *TxFIFO, long long delay)
{
	if (isTxIRQ)
	{
		if (isTxSchedule == NO)
		{
			this->schedule_under_Sec = global_under_Sec + delay;			//강제 딜레이
			this->schedule_upper_Sec = global_upper_Sec;
			isTxSchedule = YES;
		}

		else if (isTxSchedule == PROCESS && schedule_under_Sec == global_under_Sec && schedule_upper_Sec == schedule_upper_Sec)
		{
			//cout << this->name << "/TxMsg(name)" << endl << endl;
			this->Connection->IRQMsg = TxFIFO;
			this->Connection->IRQMsg->processed_under_Sec += 1000;			//전파 딜레이
			this->Connection->isRxIRQ = true;
			isTxIRQ = false;
			isTxSchedule = NO;
		}
	}

}

/*
	Module::rxMsg
	1. 송신할 메시지가 있는지 판단한다.
	2. 메시지를 송신할 시간이 정해져 있는지 판단한다.
		NO : 메시지를 송신할 시간이 정해져 있지 않는 경우이다.
		YES : 메시지를 송신할 시간이 정해진 경우이다.
		스케줄러는 이벤트를 발생할 모듈의 번호를 함께 남기는 데, 이게 자신의 모듈과 일치하고
		현재의 상태가 YES이면 PROCESS 상태로 바꾼다.
		PROCESS : 송신할 메시지를 처리한다.
*/
void Module::rxMsg(Msg *IRQMsg)
{
	if (this->isRxIRQ)
	{
		//시간을 안정했다면, 시간을 정한다.
		//시간이 정해져 있다면, 스케줄러가 검사할 것이다. YES인 경우를!
		//PROCESS가 되면 내가 처리할 순서라는 것이다.
		if (isRxSchedule == NO)
		{
			this->schedule_under_Sec = IRQMsg->processed_under_Sec;
			this->schedule_upper_Sec = IRQMsg->processed_upper_Sec;
			isRxSchedule = YES;
		}

		else if (isRxSchedule == PROCESS && schedule_under_Sec == global_under_Sec && schedule_upper_Sec == schedule_upper_Sec)
		{
			this->RxFIFO = IRQMsg;										/* 메시지 복사 */
			this->RxFIFO->tmpMsg++;
			this->isRxIRQ = false;
			this->RxCount++;

			
			cout << this->name << "/rxMsg(name)" << endl;
			cout << this->isRxIRQ << "/rxMsg(isRxIRQ)" << endl;
			cout << this->RxCount << "/rxMsg(count)" << endl;
			cout << this->RxFIFO->tmpMsg << "/rxMsg(Msg)" << endl;
			cout << this->RxFIFO->processed_under_Sec << "/rxSecond(pSec)\r\n\r\n" << endl;
			
			this->TxFIFO = this->RxFIFO;

			isTxIRQ = true;
			txMsg(this->TxFIFO, 0);
			isRxSchedule = NO;
		}
	}
}

void Module::setConnection(Module *Connection) {
	this->Connection = Connection;
}

void Module::setScheduleTime(long long upper_Sec, long long under_Sec) {
	this->schedule_under_Sec = under_Sec;			//1pSec : 1nSec : 1uSec : 1000mSec
	this->schedule_upper_Sec = upper_Sec;			//11Day : 13Hour : 46Minute : 40Sec
}

long long Module::getScheduleTime(bool under_upper_Sec) {
	if (!under_upper_Sec) return this->schedule_under_Sec;
	else if (under_upper_Sec) return this->schedule_upper_Sec;
	else return 0;
};

/*
	Module::vTask
	1. 모듈이 이벤트를 발생해도 되는지 판단한다.
	2. txMsg와 rxMsg를 통해, 송신 및 수신 스케줄 시간을 정한다.
*/
void Module::vTask() {
	if (this->number == nowSechduleNumber)
	{
		if (isTxSchedule == YES)
			isTxSchedule = PROCESS;
		if (isRxSchedule == YES)
			isRxSchedule = PROCESS;

		this->number = 0;
	}

	this->txMsg(this->TxFIFO, 0);
	this->rxMsg(this->IRQMsg);
	
	//테스크 종료 조건에 부합하면, return!
	if (this->RxCount == 1)
	{
		vTaskOver();
		return;
	}
}




//---------------------------
//|			Main 시작		|
//---------------------------



/*
* Main
*/
int main() {
	

	time_t start = time(NULL);
	//0. 시뮬레이션의 끝을 확인하기 위한것, Task가 단 하나라도 살아있는지 아닌지 확인.
	bool isOneTask = true;

	//1. 모듈 생성, 모듈 자체에 대한 초기화는 Class 생성자에서 고고
	Module *Module1 = new Module("Module1", ++sizeModule);
	Module *Module2 = new Module("Module2", ++sizeModule);

	Module *Module3 = new Module("Module3", ++sizeModule);
	Module *Module4 = new Module("Module4", ++sizeModule);
	vScheduler* myScheduler = new vScheduler();


	//2. 네트워크를 모델링. 즉, 와이어링
	Module1->setConnection(Module2);
	Module2->setConnection(Module1);

	Module3->setConnection(Module4);
	Module4->setConnection(Module3);

	//3. 시뮬레이션을 위한 초기화
	Module1->Init();
	Module2->Init();

	Module3->Init();
	Module4->Init();


	//처리할 수 있는 Task 존재하는지를 검사하기 위한 변수
	int i = 0;

	//시뮬레이션 시작
	while (isOneTask) {
		i = 0;
		Module1->vTask();
		Module2->vTask();

		Module3->vTask();
		Module4->vTask();

		//각 모듈 객체를 넘기는 것이 좋을 것으로 판단...
		if (Module1->isTxIRQ == true || Module1->isRxIRQ == true)
			myScheduler->addNode(Module1->getNumber(), Module1->getScheduleTime(1), Module1->getScheduleTime(0));

		if (Module2->isTxIRQ == true || Module2->isRxIRQ == true)
			myScheduler->addNode(Module2->getNumber(), Module2->getScheduleTime(1), Module2->getScheduleTime(0));

		if (Module3->isTxIRQ == true || Module3->isRxIRQ == true)
			myScheduler->addNode(Module3->getNumber(), Module3->getScheduleTime(1), Module3->getScheduleTime(0));

		if (Module4->isTxIRQ == true || Module4->isRxIRQ == true)
			myScheduler->addNode(Module4->getNumber(), Module4->getScheduleTime(1), Module4->getScheduleTime(0));
		
		myScheduler->compareTime();
		myScheduler = new vScheduler();


		// 매번, i는 0이 된다. 그리고 Task를 처리한 후, 자신이 처리할 것이 없다면 Task가 죽은 것으로 판단!
		// 따라서, 클래스에 포함된 Taskover를 적적힐 사용해야함
		// 추후 이것은 스케줄러 클래스를 만든 후 조정해야 할듯.
		i += Module1->getIsTask();
		i += Module2->getIsTask();

		i += Module3->getIsTask();
		i += Module4->getIsTask();
		if (i == 0) isOneTask = false;
	}

	time_t end = time(NULL);
	printf("실행시간1(time함수 사용): %lf 초\n", (double)(end - start));

	return 0;
}
