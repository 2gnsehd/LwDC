/*
 *	TODO:
 *   1. �����̸� �� �� �ִ� �ð��� �־���. ����, �����ٸ��� �����ؾ��Ѵ�.
 *   2. ��, ���� ó���� �ؾ��ϴ� ������ ����. ����μ�...
 */

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

enum isSchedule {
	NO = 0,
	YES = 1,
	PROCESS = 2
};

/*
* �ùķ��̼��� ���� ���� ����
*/

long long global_under_Sec = 0;
long long global_upper_Sec = 0;
int sizeModule = 0;;

/*
* Calss: �����ٷ��� ���� Ŭ����
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
	void addNode(long long upper_Sec, long long under_Sec);
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

void vScheduler::addNode(long long upper_Sec, long long under_Sec) {
	infoModule* node = new infoModule();
	if (length == 0)
	{
		this->head = node;
		this->tail = node;
		this->head->upper_Sec = upper_Sec;
		this->head->under_Sec = under_Sec;
		this->length++;
	}

	else
	{
		this->tail->next = node;
		this->tail = node;
		this->tail->upper_Sec = upper_Sec;
		this->tail->under_Sec = under_Sec;
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
	cout << "�Էµ� �ð� ��" << endl;
	while (head) {
		cout << "Node upper sec" << i << " - " << head->upper_Sec << endl;
		cout << "Node under sec" << i << " - " << head->under_Sec << endl;
		head = head->next;
		i++;
	}
	cout << endl;
}

// ���� ���� vTime Ŭ���� �� ���� ����(�������忡�� ����) �ð��� ���� Ŭ���� ����
// �׷����� ����ü�� �ʿ��ҵ�...
// �� vTime�� Ŭ������ �ּ� ���� �˰� �־�� �ҵ�!
void vScheduler::compareTime() {
	//1. ��ü vTime Ŭ���� �߿��� upper_Sec�� min ���� ���Ѵ�.
	//2. ��ü min ���� ���� vTime class���� �迭�� �����.
	//3. �߷��� �迭���� down_Sec�� min ���� ���Ѵ�.
	//4. �� �� �ϳ��� ó���Ѵ�.

	infoModule* tmpHead = new infoModule();
	infoModule* min_upper_Sec_Array;
	infoModule* min_under_Sec_Array;

	long long min_upper_Sec = 10000000000000;
	int size_min_upper_Sec = 0;

	long long min_under_Sec = 10000000000000;
	int size_min_under_Sec = 0;

	int tmpsize = 0;
	//upper Second �ּҰ� �˻�
	tmpHead = this->head;
	while (tmpHead)
	{
		if (min_upper_Sec > tmpHead->upper_Sec)
		{
			min_upper_Sec = tmpHead->upper_Sec;
		}
		tmpHead = tmpHead->next;
	}

	//upper Second �ּҰ��� ��� ���� ���
	tmpHead = this->head;
	while (tmpHead)
	{
		if (min_upper_Sec == tmpHead->upper_Sec)
		{
			size_min_upper_Sec++;
		}
		tmpHead = tmpHead->next;
	}

	//upper Second �ּҰ��� ��⸸ŭ �迭 �ٽ� ����
	//under Second ���� ���ÿ� ��������� ��.
	tmpHead = this->head;
	min_upper_Sec_Array = new infoModule[size_min_upper_Sec];
	tmpsize = 0;
	while (tmpHead)
	{
		if (min_upper_Sec == tmpHead->upper_Sec)
		{
			min_upper_Sec_Array[tmpsize].upper_Sec = tmpHead->upper_Sec;
			min_upper_Sec_Array[tmpsize].under_Sec = tmpHead->under_Sec;
			tmpsize++;
		}
		tmpHead = tmpHead->next;
	}

	// -----------------------------------------------------

	//under Second �ּҰ� �˻�
	for (int i = 0; i<size_min_upper_Sec; i++)
	{
		if (min_under_Sec > min_upper_Sec_Array[i].under_Sec)
		{
			min_under_Sec = min_upper_Sec_Array[i].under_Sec;
		}
	}

	//under Second �ּҰ��� ��� ���� ���
	for (int i = 0; i<size_min_upper_Sec; i++)
	{
		if (min_under_Sec == min_upper_Sec_Array[i].under_Sec)
		{
			size_min_under_Sec++;
		}
	}

	//under Second �ּҰ� �˻��ּҰ��� ��⸸ŭ �迭 �ٽ� ����
	min_under_Sec_Array = new infoModule[size_min_under_Sec];
	tmpsize = 0;
	for (int i = 0; i<size_min_upper_Sec; i++)
	{
		if (min_under_Sec == min_upper_Sec_Array[i].under_Sec)
		{
			/*
			min_under_Sec_Array[tmpsize].upper_Sec = min_upper_Sec_Array[i].upper_Sec;
			min_under_Sec_Array[tmpsize].under_Sec = min_upper_Sec_Array[i].under_Sec;
			tmpsize++;
			*/
		}
	}

	/*
	cout << "���� ���� �ð� ��" << endl;
	cout << "Minimum, upperSec - " << min_under_Sec_Array[0].upper_Sec << endl;
	cout << "Minimum, underSec - " << min_under_Sec_Array[0].under_Sec << endl;
	cout << "���� ���� �ð� ���� ���� ��ü ���� " << size_min_under_Sec << endl;
	cout << endl << endl;
	*/
};



/*
* Calss: �޽����� ���� Ŭ����
*/

class Signal {
public:
	long long maked_under_Sec = 0;					//�޽����� ������� under_Sec / �ʱ⿡�� �ٲٰ� ���� �ٲ��� ����
	long long maked_upper_Sec = 0;					//�޽����� ������� upper_Sec / �ʱ⿡�� �ٲٰ� ���� �ٲ��� ����

	long long processed_under_Sec = 0;				//�޽����� ���� �ֱٿ� ó���� under_Sec / ��, ���� Hop�� ��ĥ������ ����
	long long processed_upper_Sec = 0;				//�޽����� ���� �ֱٿ� ó���� upper_Sec / ��, ���� Hop�� ��ĥ������ ����
};

class Msg : public Signal {
public:
	int tmpMsg;
};

/*
* Calss: ����� ���� Ŭ����
*/
class Module {
public:

	/*
	* �� Class�� ������ ����.
	*/
	string name;									//��� �̸�
	uint32_t number;								//��� ��ȣ
	bool isBusy = false;							//���� �ٻ۰�?
	bool isTask = true;								//���̻� ó���� ���� ���°�?
	isSchedule isTxSchedule = NO;						//�����ٸ� �����ΰ�?
	isSchedule isRxSchedule = NO;

	long long schedule_under_Sec = 0;				//ó���ؾ��� under_Sec
	long long schedule_upper_Sec = 0;				//ó���ؾ��� upper_Sec
	long long delay = 0;							//������ ���
	
	/*
	* �� Class�� ������ Class
	*/
	Module *Connection;								   //����� ��
	Msg *TxFIFO;									   //ũ�Ⱑ 1�� �۽ſ� FIFO
	Msg *RxFIFO;									   //ũ�Ⱑ 1�� ���ſ� FIFO

	/*
	* �ٸ� Class�� ������ ����.
	*/
	bool isTxIRQ = false;
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
	Module(string name, int number);
	void Init();															//������
	void txMsg(Msg *TxFIFO);												//�޼��� �۽�
	void rxMsg(Msg *RxFIFO);												//�޼��� ����
	void setConnection(Module *Connection);									//��� ����
	void setScheduleTime(long long upper_Sec, long long under_Sec);				//���� ���� ������ �ð�
	long long getScheduleTime(bool under_upper_Sec);
	void vTask();															//���μ��� ������ �ϴ� �׽�ũ
	void vTaskOver();														//���� �׽�ũ ���� �˸�
	bool getIsTask();														//���� �׽�ũ�� ��Ȳ�� Ȯ��

};

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
		//������ �ð��� �����Ѵ�.
		this->TxFIFO->tmpMsg = 100;
		this->TxFIFO->maked_under_Sec = 1000;
		this->TxFIFO->maked_upper_Sec = 0;
		this->TxFIFO->processed_under_Sec = this->TxFIFO->maked_under_Sec;
		this->TxFIFO->processed_upper_Sec = this->TxFIFO->maked_upper_Sec;

		isTxIRQ = true;
		this->txMsg(this->TxFIFO);
	}

	if (!this->name.compare("Module3")) {
		//������ �ð��� �����Ѵ�.
		this->TxFIFO->tmpMsg = 200;
		this->TxFIFO->maked_under_Sec = 0;
		this->TxFIFO->maked_upper_Sec = 0;
		this->TxFIFO->processed_under_Sec = 0;
		this->TxFIFO->processed_under_Sec = 0;
		this->txMsg(this->TxFIFO);
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

void Module::txMsg(Msg *TxFIFO)
{
	//1. Ŀ�׼��� �������� Ȯ���ϰ� �����̸� ����Ѵ�. ����� 1ns�� �߰��� ��
	//1. Ŀ�ؼ��� ����� Ȯ���Ѵ�.   this->Connection
	//2. Ŀ�ؼ� �� ���� ���ŵǰ� �ִ� �޽����� �ٲپ��ش�.
	if (isTxIRQ)
	{
		if (isTxSchedule == NO)
		{
			this->schedule_under_Sec = global_under_Sec;
			this->schedule_upper_Sec = global_upper_Sec;
			isTxSchedule = YES;
		}

		else if(isTxSchedule == PROCESS)
		{
			this->Connection->IRQMsg = TxFIFO;
			this->Connection->IRQMsg->processed_under_Sec += 1000;
			this->Connection->isRxIRQ = true;
			isTxIRQ = false;
			isTxSchedule = NO;
		}
	}
	
}

void Module::rxMsg(Msg *IRQMsg)
{
	if (this->isRxIRQ)
	{
		//�ð��� �����ߴٸ�, �ð��� ���Ѵ�.
		//�ð��� ������ �ִٸ�, �����ٷ��� �˻��� ���̴�. YES�� ��츦!
		//PROCESS�� �Ǹ� ���� ó���� ������� ���̴�.
		if(isRxSchedule == NO)
		{
			this->schedule_under_Sec = global_under_Sec + 1000;
			this->schedule_upper_Sec = global_upper_Sec;
			isRxSchedule = YES;
		}

		else if (isRxSchedule == PROCESS)
		{
			this->RxFIFO = IRQMsg;           //�޽��� ����
			this->RxFIFO->tmpMsg++;
			this->isRxIRQ = false;
			this->count++;

			cout << this->name << "/rxMsg(name)" << endl;
			cout << this->isRxIRQ << "/rxMsg(isRxIRQ)" << endl;
			cout << this->count << "/rxMsg(count)" << endl;
			cout << this->RxFIFO->tmpMsg << "/rxMsg(Msg)" << endl;
			cout << this->RxFIFO->processed_under_Sec << "/rxSecond(pSec)\r\n\r\n" << endl;

			this->TxFIFO = this->RxFIFO;

			isTxIRQ = true;
			txMsg(this->TxFIFO);
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

void Module::vTask() {
	// �����ٸ��� �Ǿ� �ִ��� Ȯ��

	//�����ٸ��� �Ǿ� �ִٸ� ���� �۾��� ó���ؾ� ��!
	if (isTask)
	{
		this->rxMsg(this->IRQMsg);
	}

	if (this->count == 3)
	{
		vTaskOver();
	}
}




//---------------------------
//|			Main ����		|
//---------------------------



/*
* Main
*/
int main() {
	//0. �ùķ��̼��� ���� Ȯ���ϱ� ���Ѱ�, Task�� �� �ϳ��� ����ִ��� �ƴ��� Ȯ��.
	bool isOneTask = true;

	//1. ��� ����, ��� ��ü�� ���� �ʱ�ȭ�� Class �����ڿ��� ���
	Module *Module1 = new Module("Module1", ++sizeModule);
	Module *Module2 = new Module("Module2", ++sizeModule);

	Module *Module3 = new Module("Module3", ++sizeModule);
	Module *Module4 = new Module("Module4", ++sizeModule);
	vScheduler* myScheduler = new vScheduler();

	

	//2. ��Ʈ��ũ�� �𵨸�. ��, ���̾
	Module1->setConnection(Module2);
	Module2->setConnection(Module1);

	Module3->setConnection(Module4);
	Module4->setConnection(Module3);

	//3. �ùķ��̼��� ���� �ʱ�ȭ
	Module1->Init();
	Module2->Init();

	Module3->Init();
	Module4->Init();


	//ó���� �� �ִ� Task �����ϴ����� �˻��ϱ� ���� ����
	int i = 0;

	//�ùķ��̼� ����
	while (isOneTask) {
		i = 0;

		Module1->vTask();
		Module2->vTask();

		Module3->vTask();
		Module4->vTask();

		myScheduler->addNode(Module1->getScheduleTime(1), Module1->getScheduleTime(0));
		myScheduler->addNode(Module2->getScheduleTime(1), Module2->getScheduleTime(0));
		myScheduler->addNode(Module3->getScheduleTime(1), Module3->getScheduleTime(0));
		myScheduler->addNode(Module4->getScheduleTime(1), Module4->getScheduleTime(0));



		// �Ź�, i�� 0�� �ȴ�. �׸��� Task�� ó���� ��, �ڽ��� ó���� ���� ���ٸ� Task�� ���� ������ �Ǵ�!
		// ����, Ŭ������ ���Ե� Taskover�� ������ ����ؾ���
		// ���� �̰��� �����ٷ� Ŭ������ ���� �� �����ؾ� �ҵ�.
		i += Module1->getIsTask();
		i += Module2->getIsTask();

		i += Module3->getIsTask();
		i += Module4->getIsTask();
		if (i == 0) isOneTask = false;
	}

	return 0;
}
