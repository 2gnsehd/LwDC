
/*
 *	TODO:
 *   1. �ð� ���� ����� -> 
 *   2. �����ٷ� �����  -> 
 *	 3. ����.,.? ����..?
 */

#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

class Signal {
public:
	unsigned int TxModulecount;
	unsigned int RouteModulecount;
	unsigned int RxModulecount;
};

class Msg : public Signal {
public:
	int tmpMsg;
	int tmpMsg2;
};

class Module {
public:

	/*
	* �� Class�� ������ ����.
	*/
	string name;									//��� �̸�
	uint32_t number;								//��� ��ȣ
	bool isBusy = false;							//���� �ٻ۰�?
	bool isTask = true;								//���̻� ó���� ���� ���°�?
	
	/*
	* �� Class�� ������ Class
	*/
	Module *Connection;								   //����� ��
	Msg *TxFIFO;									   //ũ�Ⱑ 1�� �۽ſ� FIFO
	Msg *RxFIFO;									   //ũ�Ⱑ 1�� ���ſ� FIFO

	/*
	* �ٸ� Class�� ������ ����.
	*/
	bool isTxIRQ = false;							    //�̺�Ʈ�� �Ͼ���� üũ
	bool isRxIRQ = false;

	/*
	* �ٸ� Class�� ������ Class
	*/
	Msg *IRQMsg;									 //�̺�Ʈ�� �Ͼ �ӽ� �޽���

	/*
	* ���ø����̼ǿ� ����
	*/
	int count = 0;									//���� Ƚ��

	/*
	 * Modul ���� �Լ���
	 */
	Module();
	void Init();									//������
	void txMsg(Msg *TxFIFO);						//�޼��� �۽�
	void rxMsg(Msg *RxFIFO);						//�޼��� ����
	void setConnection(Module *Connection);			//��� ����

	void vTask();									//���μ��� ������ �ϴ� �׽�ũ
	void vTaskOver();								//���� �׽�ũ ���� �˸�
	bool getIsTask();								//���� �׽�ũ�� ��Ȳ�� Ȯ��

};

Module::Module() {
	this->TxFIFO = new Msg();
	this->RxFIFO = new Msg();
	this->IRQMsg = new Msg();
}

void Module::vTask() {
	//thraed�� �ϸ� Ǯ�������..
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
		this->TxFIFO->tmpMsg = 100;
		this->txMsg(this->TxFIFO);
	}
}

void Module::txMsg(Msg *TxFIFO)
{
	//1. Ŀ�ؼ��� ����� Ȯ���Ѵ�.   this->Connection
	//2. Ŀ�ؼ� �� ���� ���ŵǰ� �ִ� �޽����� �ٲپ��ش�.
	this->Connection->IRQMsg = TxFIFO;
	this->Connection->isRxIRQ = true;
}

void Module::rxMsg(Msg *IRQMsg)
{
	if (this->isRxIRQ == true)
	{
		this->RxFIFO = IRQMsg;           //�޽��� ����
		this->RxFIFO->tmpMsg++;
		this->isRxIRQ = false;
		this->count++;

		cout << this->name << "/rxMsg(name)" << endl;
		cout << this->isRxIRQ << "/rxMsg(isRxIRQ)" << endl;
		cout << this->count << "/rxMsg(count)" << endl;
		cout << this->RxFIFO->tmpMsg << "/rxMsg(Msg)\r\n\r\n" << endl;

		this->TxFIFO = this->RxFIFO;
		txMsg(this->TxFIFO);
	}
}

void Module::setConnection(Module *Connection) {
	this->Connection = Connection;
}


int main() {
	//0. �ùķ��̼��� ���� Ȯ���ϱ� ���Ѱ�, Task�� �� �ϳ��� ����ִ��� �ƴ��� Ȯ��.
	bool isOneTask = true;

	//1. ��� ����, ��� ��ü�� ���� �ʱ�ȭ�� Class �����ڿ��� ���
	Module *Module1 = new Module();
	Module *Module2 = new Module();

	//2. ��⿡ ���� �̸���? �̰��� 1�� �Űܾ� �ҵ�
	Module1->name = "Module1";
	Module2->name = "Module2";

	//3. ��Ʈ��ũ�� �𵨸�. ��, ���̾
	Module1->setConnection(Module2);
	Module2->setConnection(Module1);

	//4. �ùķ��̼��� ���� �ʱ�ȭ
	Module1->Init();
	Module2->Init();



	//�ܼ� ����
	int i = 0;

	//�ùķ��̼� ����
	while (isOneTask) {
		i = 0;

		Module1->vTask();
		Module2->vTask();

		// �Ź�, i�� 0�� �ȴ�. �׸��� Task�� ó���� ��, �ڽ��� ó���� ���� ���ٸ� Task�� ���� ������ �Ǵ�!
		// ����, Ŭ������ ���Ե� Taskover�� ������ ����ؾ���
		// ���� �̰��� �����ٷ� Ŭ������ ���� �� �����ؾ� �ҵ�.
		i += Module1->getIsTask();
		i += Module2->getIsTask();
		if (i == 0) isOneTask = false;
	}

	//�ӽ÷� ���ܵ�����. ������� ������ �ҵ�, �̺�Ʈ ����� �ùķ��̼ǿ� ���� �ʿ䰡 �����..., ����뵵 �ſ� ����
	//�ùķ��̼� ����(������ ����)
	//thread th1(&Module::vTask, Module1);
	//thread th2(&Module::vTask, Module2);

	//���� �Լ��� ������ ������, ������ ���Ḧ ��ٸ���.
	//th1.join();
	//th2.join();

	return 0;
}
