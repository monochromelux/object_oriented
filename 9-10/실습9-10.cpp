#include <iostream>
using namespace std;

class Shape {
	Shape* next;
protected:
	virtual void draw() = 0; //���� ���� �Լ� draw 
public:
	Shape() { next = NULL; } //���� ���Ե��� �ʾ��� ��� ���� ����� �ּҰ��� NULL�� ���� 
	virtual ~Shape() { }
	void paint() { draw(); } //�������̵��� draw�Լ� ȣ�� 
	Shape* add(Shape* p) {
		this->next = p; // ���Ե� ���� ���� �� ������ �ּҰ����� ���� 
		return p; //���Ե� �� ���� 
	}
	Shape* getNext() { return next; } //���� �� ������ �ּҰ��� ���� 
};
class Circle : public Shape {
protected:
	virtual void draw() { //paint�Լ� �۵� �� Circle�� ��µǵ��� �� 
		cout << "Circle" << endl;
	}
};
class Rect : public Shape {
protected:
	virtual void draw() { //paint�Լ� �۵� �� Rectangle�� ��µǵ��� �� 
		cout << "Rectangle" << endl;
	}
}; 
class Line : public Shape {
protected:
	virtual void draw() { //paint�Լ� �۵� �� Line�� ��µǵ��� �� 
		cout << "Line" << endl;
	}
}; 

class UI {
protected:
	static void start() { //���� ���� 
		cout << " �׷��� �������Դϴ�." << endl;
	}
	static void mainUI() { //���� �޴� �׸� 
		cout << " ���� : 1, ���� : 2, ��κ��� : 3, ���� : 4 >> ";
	}
	static void figureUI() { //������ ������ ���� 
		cout << " �� : 1, �� : 2, �簢�� : 3 >> ";
	}
	static void deleteUI() { //������ ������ �ε��� ��ȣ �Է� 
		cout << " �����ϰ��� �ϴ� ������ �ε��� >> ";
	}
	static void notFound() { //���� ���Ե� ������ ���� ����� ���� �޼��� 
		cout << " ���Ե� ������ �����ϴ�. " << endl;
	}
	static void wrongIn() { //���� ���� �Է��� �޾��� ����� ���� �޼��� 
		cout << " �߸��� �Է��Դϴ�. " << endl;
	}
};
class GraphicEditer : public UI {
	int manu; //�޴� ���� ���� 
	Shape* pStart; //���� ��� ���� 
	Shape* pLast; //������ ��� ���� 
public:
	GraphicEditer() {
		pStart = NULL; //pStart�� NULL�� �ʱ�ȭ 
		pLast = pStart; //pLast�� NULL�� �ʱ�ȭ 
		manu = 0;
		start(); //���� ���� ��� 
	}
	~GraphicEditer() { //Ŭ���� �Ҹ�� �۵�, ���Ե� ���� ��� delete��Ŵ (p.437) 
		Shape* p = pStart; //����� ó���� ����Ű�� ������ p 
		while(p != NULL) { //p���� NULL���� ���ö����� �ݺ� 
			Shape* q = p->getNext(); //������ ���� �ٷ� ���� �ּҷ� ������ ������ q 
			delete p; //���� ���� ��ü �Ҹ� 
			p = q; //���� ������ �ּҸ� p�� ���� 
		}
	}
	void input() { //���� ���� �Լ� 
		int fig = 0;
		figureUI(); //������ ���� ���� ȭ�� ��� 
		cin >> fig; //������ ������ ������ �Է¹��� 
		switch (fig) {
			case 1: //�� ���� 
				if(pStart == NULL) { //���� ó������ �Է¹��� ��� ó�� ��忡 ���� �Ҵ��Ͽ� ���� 
					pStart = new Line();
					pLast = pStart; //���� �ϳ��ۿ� �����Ƿ� ó���� �������� ���� ���� 
				}
				else {
					pLast = pLast->add(new Line()); 
					//���� �����Ҵ����� �߰��ǰ� ������ ����� ���� �ٲ� 
				}
				break;
			case 2: //�� ���� 
				if(pStart == NULL) {
					pStart = new Circle();
					pLast = pStart;
				}
				else {
					pLast = pLast->add(new Circle());
				}
				break;
			case 3: //�簢�� ���� 
				if(pStart == NULL) {
					pStart = new Rect();
					pLast = pStart;
				}
				else {
					pLast = pLast->add(new Rect());
				}
				break;
			default:
				wrongIn(); //�׸� �ǿ��� ���̹Ƿ� ���� �޼��� ��� 
				break;
		}
	}
	bool delFigure() { //���� ���� �Լ� 
		int del, i=0;
		Shape* p = pStart; //����� ó���� ����Ű�� ������ p 
		deleteUI(); //������ ���� �Է� ȭ�� ��� 
		cin >> del; //������ ������ ��ȣ�� �Է¹��� 
		
		if(del < i) { //�Է¹��� ���� ������ ���  
			wrongIn(); //�׸� �ǿ��� ���̹Ƿ� ���� �޼��� ��� 
			return false; //�Լ� ���� ���� 
		}
		else if(del == 0) { //�Է¹��� ���� 0�� ���, �� ó�� ���Ե� ������ �����ϴ� ��� 
			Shape* q = p->getNext(); //������ ���� �ٷ� ���� �ּҷ� ������ ������ q 
			pStart = q; //q�� �ּҰ��� ó�� ����� �ּҰ����� ���� 
		}  
		else { //�� ���� ��� 
			while(i < del-1) { //������ ���� �ٷ� ���� �ּұ��� �̵��ϴ� �ݺ��� 
				p = p->getNext(); //���� �ּҷ� �̵� 
				if (p == pLast || p == NULL) { //�Է¹��� ����ŭ �̵����� �ʾ������� p�� ����Ű�� �ּҰ� 
								  //������ ����� �ּҿ� ���� ���(����� ������ �Էµ� ���� �� ŭ) 
					wrongIn(); 	  //�׸� �ǿ��� ���̹Ƿ� ���� �޼��� ��� 
					return false; //�Լ� ���� ���� 
				}
				i++;  //�ּҸ� �̵���ų������ 1�� ���� 
			}
			Shape* q = p; //������ ���� �ٷ� ���� �ּҷ� ������ ������ q 
			p = p->getNext(); //���� �ּ�(������ ������ �ּ�)�� �̵� 
			q->add(p->getNext()); //������ ���� �ٷ� ���� �ּҿ� ������ ���� �ٷ� ������ �ּҸ� ���� 
		} 
		delete p; //���� ���� ��ü �Ҹ� 
		return true; //�Լ� ���� ���� 
	}
	void allDraw() { //���� ��ü ��� �Լ� (p.437) 
		int count = 0; 
		Shape* p = pStart; //����� ó���� ����Ű�� ���� p 
		while(p != NULL) {
			cout << ' ' << count << ": "; //��µǴ� ������ ǥ�� 
			p->paint(); //p�� ����� ������ ��� 
			p = p->getNext(); //p�� ���� ���� �ּҷ� ����(���� �ε����� �̵�) 
			count++; //������ �ϳ� ��µɶ����� 1�� ���� 
		}
	}
	int mainManu() { //���� �׸� �Լ� 
		mainUI(); //�׸� ���� ȭ�� ��� 
		cin >> manu; //�׸� ���� 
		switch(manu) {
			case 1: //���� 
				input();
				return 1;
			case 2: //���� 
				if(pStart == NULL) { //���Ե� ������ �����Ƿ� ���� �޼��� ��� 
					notFound();
				}
				else {
					delFigure();
				}
				return 2;
			case 3: //��κ��� 
				if(pStart == NULL) { //���Ե� ������ �����Ƿ� ���� �޼��� ��� 
					notFound();
				}
				else {
					allDraw();
				}
				return 3;
			case 4: //���� 
				return 4;
			default:
				wrongIn(); //�׸� �ǿ��� ���̹Ƿ� ���� �޼��� ��� 
				return -1;
		}
	}
};

int main(int argc, char** argv) {
	int num = 0; //mainManu�Լ��� ���ϰ��� ������ ���� num 
	GraphicEditer Run;
	
	while (num != 4) { //mainManu�Լ����� 4�� ���ϵǱ� ������ �ݺ� 
		num = Run.mainManu(); //GraphicEditerŬ������ mainManu�Լ� ���� 
	}
	
	return 0;
}
