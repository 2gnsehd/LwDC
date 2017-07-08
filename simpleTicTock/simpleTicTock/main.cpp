#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

class Module {
public:
	string Name;                        //모듈 이름
	bool busy = false;                  //현재, 바쁜지 체크
	volatile bool isMsg = false;                 //메시지 있는지 체크

	int Msg = -1;                       //메시지
	volatile int tempMsg = -1;                     //수신되고 있는 메시지
	int check = 0;

	Module *Connection;
	int number = 0;                     //보낸 횟수

	void ModuleTh();
	void Init();
	void TxMsg(int Msg);
	void RxMsg();
	void SetConnection(Module *Connection);
};

void Module::SetConnection(Module *Connection) {
	this->Connection = Connection;
}

void Module::ModuleTh() {
	this->Init();


	while (1) {
		this->RxMsg();

		if (this->number == 3)
		{
			cout << this->Name << endl;
			break;
		}
	}

}

void Module::Init()
{
	if (!this->Name.compare("Tic")) {
		this->Msg = 100;
		TxMsg(this->Msg);
	}
}

void Module::TxMsg(int Msg)
{
	//1. 커넥션이 어딘지 확인한다.   this->Connection
	//2. 커넥션 된 곳의 수신되고 있는 메시지를 바꾸어준다
	this->Connection->tempMsg = this->Msg;
	this->Connection->isMsg = true;
}

void Module::RxMsg()
{
	if (this->isMsg == true)
	{
		this->Msg = this->tempMsg;
		this->Msg++;
		this->isMsg = false;
		this->number++;

		cout << this->Name << "/RxMsg(Name)" << endl;
		cout << this->isMsg << "/RxMsg(isMsg)" << endl;
		cout << this->number << "/RxMsg(number)" << endl;
		cout << this->Msg << "/RxMsg(Msg)\r\n\r\n" << endl;

		TxMsg(this->Msg);
	}
}



int main() {
	//네트워크 모듈 및 노드 생성

	//#case 1
	//was Module Tic;
	//was Module Tock;

	//#case 2
	Module *Tic = new Module();
	Module *Tock = new Module();

	//네트워크 모델링

	//#case 1
	//was Tic.Name = "Tic";
	//was Tock.Name = "Tock";

	//#case 2
	Tic->Name = "Tic";
	Tock->Name = "Tock";

	//연결하자
	//Tic.Connection = &Tock;
	//Tock.Connection = &Tic;
	Tic->SetConnection(Tock);
	Tock->SetConnection(Tic);

	//쓰레드당
	thread th1(&Module::ModuleTh, Tic);
	thread th2(&Module::ModuleTh, Tock);

	th1.join();
	th2.join();

	return 0;
}
