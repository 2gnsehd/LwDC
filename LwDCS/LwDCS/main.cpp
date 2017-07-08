
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

class Signal {
	unsigned int TxModulecount;
	unsigned int RouteModulecount;
	unsigned int RxModulecount;
};

class Msg : public Signal {

public:
	int Msg;

};


class Module {
public:

	/*
	* 본 Class만 수정할 변수.
	*/
	string name;                        //모듈 이름
	uint32_t number;                    //모듈 번호
	bool isBusy = false;                //지금 바쁜가?
	bool isTask = true;                 //더이상 처리할 것이 없는가?
	Module *Connection;                 //연결된 곳
	Msg *TxFIFO;                        //크기가 1인 송신용 FIFO
	Msg *RxFIFO;                        //크기가 1인 수신용 FIFO

										/*
										* 다른 Class도 수정할 변수.
										*/
	bool isTxIRQ = false;               //이벤트가 일어났는지 체크
	bool isRxIRQ = false;
	Msg *IRQMsg;                        //이벤트로 일어난 임시 메시지

										/*
										* 테스트용 변수
										*/
	int count = 0;                     //보낸 횟수

	Module();
	void Init();
	void txMsg(Msg *TxFIFO);
	void rxMsg(Msg *RxFIFO);
	void setConnection(Module *Connection);

	void vTask();
	void vTaskOver();
	bool getIsTask();

};

Module::Module() {
	this->TxFIFO = new Msg();
	this->RxFIFO = new Msg();
	this->IRQMsg = new Msg();
}

void Module::vTask() {
	//thraed로 하면 풀어줘야함..
	//while(1){
	if (isTask)
	{
		this->rxMsg(this->IRQMsg);
	}

	if (this->count == 3)
	{
		vTaskOver();
	}
	//}
}

void Module::vTaskOver()
{
	this->isTask = false;
}

bool Module::getIsTask()
{
	return this->isTask;
}

void Module::Init()
{
	if (!this->name.compare("Module1")) {
		this->TxFIFO->Msg = 100;
		this->txMsg(this->TxFIFO);
	}
}

void Module::txMsg(Msg *TxFIFO)
{
	//1. 커넥션이 어딘지 확인한다.   this->Connection
	//2. 커넥션 된 곳의 수신되고 있는 메시지를 바꾸어준다.
	this->Connection->IRQMsg = TxFIFO;
	this->Connection->isRxIRQ = true;
}

void Module::rxMsg(Msg *IRQMsg)
{
	if (this->isRxIRQ == true)
	{
		this->RxFIFO = IRQMsg;           //메시지 복사
		this->RxFIFO->Msg++;
		this->isRxIRQ = false;
		this->count++;

		cout << this->name << "/rxMsg(name)" << endl;
		cout << this->isRxIRQ << "/rxMsg(isRxIRQ)" << endl;
		cout << this->count << "/rxMsg(count)" << endl;
		cout << this->RxFIFO->Msg << "/rxMsg(Msg)\r\n\r\n" << endl;

		this->TxFIFO = this->RxFIFO;
		txMsg(this->TxFIFO);
	}
}

void Module::setConnection(Module *Connection) {
	this->Connection = Connection;
}


int main() {
	//0. 시뮬레이션의 끝을 확인하기 위한것, Task가 단 하나라도 살아있는지 아닌지 확인.
	bool isOneTask = true;

	//1. 모듈 생성, 모듈 자체에 대한 초기화는 Class 생성자에서 고고
	Module *Module1 = new Module();
	Module *Module2 = new Module();

	//2. 모듈에 대한 이름들? 이것은 1로 옮겨야 할듯
	Module1->name = "Module1";
	Module2->name = "Module2";

	//3. 네트워크를 모델링. 즉, 와이어링
	Module1->setConnection(Module2);
	Module2->setConnection(Module1);

	//4. 시뮬레이션을 위한 초기화
	Module1->Init();
	Module2->Init();



	//단순 계산용
	int i = 0;

	//시뮬레이션 시작
	while (isOneTask) {
		i = 0;

		Module1->vTask();
		Module2->vTask();

		// 매번, i는 0이 된다. 그리고 Task를 처리한 후, 자신이 처리할 것이 없다면 Task가 죽은 것으로 판단!
		// 따라서, 클래스에 포함된 Taskover를 적적힐 사용해야함
		// 추후 이것은 스케줄러 클래스를 만든 후 조정해야 할듯.
		i += Module1->getIsTask();
		i += Module2->getIsTask();
		if (i == 0) isOneTask = false;
	}

	//임시로 남겨두지만. 스레드는 버려야 할듯, 이벤트 기반의 시뮬레이션에 굳이 필요가 없어보임..., 디버깅도 매우 힘듬
	//시뮬레이션 시작(스레드 생성)
	//thread th1(&Module::vTask, Module1);
	//thread th2(&Module::vTask, Module2);

	//메인 함수가 끝나기 이전에, 쓰레드 종료를 기다린다.
	//th1.join();
	//th2.join();

	return 0;
}
