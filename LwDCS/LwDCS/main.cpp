/*
*	TODO:
*   1. �����̸� �� �� �ִ� �ð��� �־���. ����, �����ٸ��� �����ؾ��Ѵ�.
*   2. ��, ���� ó���� �ؾ��ϴ� ������ ����. ����μ�...
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
* �ùķ��̼��� ���� ���� ����
*/

long long global_under_Sec = 0;
long long global_upper_Sec = 0;
int sizeModule = 0;;
int nowSechduleNumber = 0;
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
			min_upper_Sec_Array[tmpsize].number = tmpHead->number;
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
	// �ʱ�ȭ

	delete tmpHead;
	delete[]min_upper_Sec_Array;
	delete[]min_under_Sec_Array;
	this->deleteList();
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
	int RxCount = 0;									//���� Ƚ��

													/*
													* Modul ���� �Լ���
													*/
	Module(string name, int number);
	void Init();															//������
	void txMsg(Msg *TxFIFO, long long delay);												//�޼��� �۽�
	void rxMsg(Msg *RxFIFO);												//�޼��� ����
	void setConnection(Module *Connection);									//��� ����
	void setScheduleTime(long long upper_Sec, long long under_Sec);				//���� ���� ������ �ð�
	long long getScheduleTime(bool under_upper_Sec);
	void vTask();															//���μ��� ������ �ϴ� �׽�ũ
	void vTaskOver();														//���� �׽�ũ ���� �˸�
	bool getIsTask();														//���� �׽�ũ�� ��Ȳ�� Ȯ��
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
		//������ �ð��� �����Ѵ�.
		this->TxFIFO->tmpMsg = 100;
		this->TxFIFO->maked_under_Sec = 500;
		this->TxFIFO->maked_upper_Sec = 0;
		this->TxFIFO->processed_under_Sec = this->TxFIFO->maked_under_Sec;
		this->TxFIFO->processed_upper_Sec = this->TxFIFO->maked_upper_Sec;

		isTxIRQ = true;
		this->txMsg(this->TxFIFO, 500);
	}

	if (!this->name.compare("Module3")) {
		//������ �ð��� �����Ѵ�.
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
	1. �۽��� �޽����� �ִ��� �Ǵ��Ѵ�.
	2. �޽����� �۽��� �ð��� ������ �ִ��� �Ǵ��Ѵ�.
		NO : �޽����� �۽��� �ð��� ������ ���� �ʴ� ����̴�.
		YES : �޽����� �۽��� �ð��� ������ ����̴�.
			  �����ٷ��� �̺�Ʈ�� �߻��� ����� ��ȣ�� �Բ� ����� ��, �̰� �ڽ��� ���� ��ġ�ϰ�
			  ������ ���°� YES�̸� PROCESS ���·� �ٲ۴�.
		PROCESS : �۽��� �޽����� ó���Ѵ�.
	3. Ŀ�׼��� �������� Ȯ���ϰ� �����̸� ����Ѵ�. ����� 1ns�� �߰��� ��
	4. Ŀ�ؼ��� ����� Ȯ���Ѵ�.   this->Connection
	5. Ŀ�ؼ� �� ���� ���ŵǰ� �ִ� �޽����� �ٲپ��ش�.
*/
void Module::txMsg(Msg *TxFIFO, long long delay)
{
	if (isTxIRQ)
	{
		if (isTxSchedule == NO)
		{
			this->schedule_under_Sec = global_under_Sec + delay;			//���� ������
			this->schedule_upper_Sec = global_upper_Sec;
			isTxSchedule = YES;
		}

		else if (isTxSchedule == PROCESS && schedule_under_Sec == global_under_Sec && schedule_upper_Sec == schedule_upper_Sec)
		{
			//cout << this->name << "/TxMsg(name)" << endl << endl;
			this->Connection->IRQMsg = TxFIFO;
			this->Connection->IRQMsg->processed_under_Sec += 1000;			//���� ������
			this->Connection->isRxIRQ = true;
			isTxIRQ = false;
			isTxSchedule = NO;
		}
	}

}

/*
	Module::rxMsg
	1. �۽��� �޽����� �ִ��� �Ǵ��Ѵ�.
	2. �޽����� �۽��� �ð��� ������ �ִ��� �Ǵ��Ѵ�.
		NO : �޽����� �۽��� �ð��� ������ ���� �ʴ� ����̴�.
		YES : �޽����� �۽��� �ð��� ������ ����̴�.
		�����ٷ��� �̺�Ʈ�� �߻��� ����� ��ȣ�� �Բ� ����� ��, �̰� �ڽ��� ���� ��ġ�ϰ�
		������ ���°� YES�̸� PROCESS ���·� �ٲ۴�.
		PROCESS : �۽��� �޽����� ó���Ѵ�.
*/
void Module::rxMsg(Msg *IRQMsg)
{
	if (this->isRxIRQ)
	{
		//�ð��� �����ߴٸ�, �ð��� ���Ѵ�.
		//�ð��� ������ �ִٸ�, �����ٷ��� �˻��� ���̴�. YES�� ��츦!
		//PROCESS�� �Ǹ� ���� ó���� ������� ���̴�.
		if (isRxSchedule == NO)
		{
			this->schedule_under_Sec = IRQMsg->processed_under_Sec;
			this->schedule_upper_Sec = IRQMsg->processed_upper_Sec;
			isRxSchedule = YES;
		}

		else if (isRxSchedule == PROCESS && schedule_under_Sec == global_under_Sec && schedule_upper_Sec == schedule_upper_Sec)
		{
			this->RxFIFO = IRQMsg;										/* �޽��� ���� */
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
	1. ����� �̺�Ʈ�� �߻��ص� �Ǵ��� �Ǵ��Ѵ�.
	2. txMsg�� rxMsg�� ����, �۽� �� ���� ������ �ð��� ���Ѵ�.
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
	
	//�׽�ũ ���� ���ǿ� �����ϸ�, return!
	if (this->RxCount == 1)
	{
		vTaskOver();
		return;
	}
}




//---------------------------
//|			Main ����		|
//---------------------------



/*
* Main
*/
int main() {
	

	time_t start = time(NULL);
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

		//�� ��� ��ü�� �ѱ�� ���� ���� ������ �Ǵ�...
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


		// �Ź�, i�� 0�� �ȴ�. �׸��� Task�� ó���� ��, �ڽ��� ó���� ���� ���ٸ� Task�� ���� ������ �Ǵ�!
		// ����, Ŭ������ ���Ե� Taskover�� ������ ����ؾ���
		// ���� �̰��� �����ٷ� Ŭ������ ���� �� �����ؾ� �ҵ�.
		i += Module1->getIsTask();
		i += Module2->getIsTask();

		i += Module3->getIsTask();
		i += Module4->getIsTask();
		if (i == 0) isOneTask = false;
	}

	time_t end = time(NULL);
	printf("����ð�1(time�Լ� ���): %lf ��\n", (double)(end - start));

	return 0;
}
