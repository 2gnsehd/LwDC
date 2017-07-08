#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

class Module {
public:
	string Name;                        //��� �̸�
	bool busy = false;                  //����, �ٻ��� üũ
	volatile bool isMsg = false;                 //�޽��� �ִ��� üũ

	int Msg = -1;                       //�޽���
	volatile int tempMsg = -1;                     //���ŵǰ� �ִ� �޽���
	int check = 0;

	Module *Connection;
	int number = 0;                     //���� Ƚ��

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
	//1. Ŀ�ؼ��� ����� Ȯ���Ѵ�.   this->Connection
	//2. Ŀ�ؼ� �� ���� ���ŵǰ� �ִ� �޽����� �ٲپ��ش�
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
	//��Ʈ��ũ ��� �� ��� ����

	//#case 1
	//was Module Tic;
	//was Module Tock;

	//#case 2
	Module *Tic = new Module();
	Module *Tock = new Module();

	//��Ʈ��ũ �𵨸�

	//#case 1
	//was Tic.Name = "Tic";
	//was Tock.Name = "Tock";

	//#case 2
	Tic->Name = "Tic";
	Tock->Name = "Tock";

	//��������
	//Tic.Connection = &Tock;
	//Tock.Connection = &Tic;
	Tic->SetConnection(Tock);
	Tock->SetConnection(Tic);

	//�������
	thread th1(&Module::ModuleTh, Tic);
	thread th2(&Module::ModuleTh, Tock);

	th1.join();
	th2.join();

	return 0;
}
