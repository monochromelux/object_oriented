#include <iostream>
using namespace std;

class Shape {
	Shape* next;
protected:
	virtual void draw() = 0; //순수 가상 함수 draw 
public:
	Shape() { next = NULL; } //값이 삽입되지 않았을 경우 다음 노드의 주소값을 NULL로 설정 
	virtual ~Shape() { }
	void paint() { draw(); } //오버라이딩된 draw함수 호출 
	Shape* add(Shape* p) {
		this->next = p; // 삽입된 값을 현재 값 다음의 주소값으로 설정 
		return p; //삽입된 값 리턴 
	}
	Shape* getNext() { return next; } //현재 값 다음의 주소값을 리턴 
};
class Circle : public Shape {
protected:
	virtual void draw() { //paint함수 작동 시 Circle이 출력되도록 함 
		cout << "Circle" << endl;
	}
};
class Rect : public Shape {
protected:
	virtual void draw() { //paint함수 작동 시 Rectangle이 출력되도록 함 
		cout << "Rectangle" << endl;
	}
}; 
class Line : public Shape {
protected:
	virtual void draw() { //paint함수 작동 시 Line이 출력되도록 함 
		cout << "Line" << endl;
	}
}; 

class UI {
protected:
	static void start() { //시작 문구 
		cout << " 그래픽 에디터입니다." << endl;
	}
	static void mainUI() { //메인 메뉴 항목 
		cout << " 삽입 : 1, 삭제 : 2, 모두보기 : 3, 종료 : 4 >> ";
	}
	static void figureUI() { //삽입할 도형을 선택 
		cout << " 선 : 1, 원 : 2, 사각형 : 3 >> ";
	}
	static void deleteUI() { //삭제할 도형의 인덱스 번호 입력 
		cout << " 삭제하고자 하는 도형의 인덱스 >> ";
	}
	static void notFound() { //현재 삽입된 도형이 없을 경우의 에러 메세지 
		cout << " 삽입된 도형이 없습니다. " << endl;
	}
	static void wrongIn() { //범위 외의 입력을 받았을 경우의 에러 메세지 
		cout << " 잘못된 입력입니다. " << endl;
	}
};
class GraphicEditer : public UI {
	int manu; //메뉴 선택 변수 
	Shape* pStart; //시작 노드 설정 
	Shape* pLast; //마지막 노드 설정 
public:
	GraphicEditer() {
		pStart = NULL; //pStart를 NULL로 초기화 
		pLast = pStart; //pLast를 NULL로 초기화 
		manu = 0;
		start(); //시작 문구 출력 
	}
	~GraphicEditer() { //클래스 소멸시 작동, 삽입된 값을 모두 delete시킴 (p.437) 
		Shape* p = pStart; //노드의 처음을 가리키는 포인터 p 
		while(p != NULL) { //p에서 NULL값이 나올때까지 반복 
			Shape* q = p->getNext(); //삭제할 도형 바로 앞의 주소로 설정된 포인터 q 
			delete p; //현재 도형 객체 소멸 
			p = q; //다음 도형의 주소를 p에 저장 
		}
	}
	void input() { //도형 삽입 함수 
		int fig = 0;
		figureUI(); //삽입할 도형 선택 화면 출력 
		cin >> fig; //삽입할 도형의 종류를 입력받음 
		switch (fig) {
			case 1: //선 삽입 
				if(pStart == NULL) { //값을 처음으로 입력받을 경우 처음 노드에 동적 할당하여 저장 
					pStart = new Line();
					pLast = pStart; //값이 하나밖에 없으므로 처음과 마지막의 값은 동일 
				}
				else {
					pLast = pLast->add(new Line()); 
					//값이 동적할당으로 추가되고 마지막 노드의 값이 바뀜 
				}
				break;
			case 2: //원 삽입 
				if(pStart == NULL) {
					pStart = new Circle();
					pLast = pStart;
				}
				else {
					pLast = pLast->add(new Circle());
				}
				break;
			case 3: //사각형 삽입 
				if(pStart == NULL) {
					pStart = new Rect();
					pLast = pStart;
				}
				else {
					pLast = pLast->add(new Rect());
				}
				break;
			default:
				wrongIn(); //항목 의외의 값이므로 에러 메세지 출력 
				break;
		}
	}
	bool delFigure() { //도형 삭제 함수 
		int del, i=0;
		Shape* p = pStart; //노드의 처음을 가리키는 포인터 p 
		deleteUI(); //삭제할 도형 입력 화면 출력 
		cin >> del; //삭제할 도형의 번호를 입력받음 
		
		if(del < i) { //입력받은 값이 음수일 경우  
			wrongIn(); //항목 의외의 값이므로 에러 메세지 출력 
			return false; //함수 실행 종료 
		}
		else if(del == 0) { //입력받은 값이 0인 경우, 즉 처음 삽입된 도형을 삭제하는 경우 
			Shape* q = p->getNext(); //삭제할 도형 바로 앞의 주소로 설정된 포인터 q 
			pStart = q; //q의 주소값을 처음 노드의 주소값으로 설정 
		}  
		else { //그 외의 경우 
			while(i < del-1) { //삭제할 도형 바로 전의 주소까지 이동하는 반복문 
				p = p->getNext(); //다음 주소로 이동 
				if (p == pLast || p == NULL) { //입력받은 값만큼 이동하지 않았음에도 p가 가리키는 주소가 
								  //마지막 노드의 주소와 같을 경우(저장된 값보다 입력된 값이 더 큼) 
					wrongIn(); 	  //항목 의외의 값이므로 에러 메세지 출력 
					return false; //함수 실행 종료 
				}
				i++;  //주소를 이동시킬떄마다 1씩 증가 
			}
			Shape* q = p; //삭제할 도형 바로 전의 주소로 설정된 포인터 q 
			p = p->getNext(); //다음 주소(삭제할 도형의 주소)로 이동 
			q->add(p->getNext()); //삭제할 도형 바로 전의 주소와 삭제할 도형 바로 다음의 주소를 연결 
		} 
		delete p; //현재 도형 객체 소멸 
		return true; //함수 실행 종료 
	}
	void allDraw() { //도형 전체 출력 함수 (p.437) 
		int count = 0; 
		Shape* p = pStart; //노드의 처음을 가리키는 변수 p 
		while(p != NULL) {
			cout << ' ' << count << ": "; //출력되는 순서를 표기 
			p->paint(); //p에 저장된 도형을 출력 
			p = p->getNext(); //p를 다음 값의 주소로 설정(다음 인덱스로 이동) 
			count++; //도형이 하나 출력될때마다 1씩 증가 
		}
	}
	int mainManu() { //메인 항목 함수 
		mainUI(); //항목 선택 화면 출력 
		cin >> manu; //항목 선택 
		switch(manu) {
			case 1: //삽입 
				input();
				return 1;
			case 2: //삭제 
				if(pStart == NULL) { //삽입된 도형이 없으므로 에러 메세지 출력 
					notFound();
				}
				else {
					delFigure();
				}
				return 2;
			case 3: //모두보기 
				if(pStart == NULL) { //삽입된 도형이 없으므로 에러 메세지 출력 
					notFound();
				}
				else {
					allDraw();
				}
				return 3;
			case 4: //종료 
				return 4;
			default:
				wrongIn(); //항목 의외의 값이므로 에러 메세지 출력 
				return -1;
		}
	}
};

int main(int argc, char** argv) {
	int num = 0; //mainManu함수의 리턴값을 저장할 변수 num 
	GraphicEditer Run;
	
	while (num != 4) { //mainManu함수에서 4가 리턴되기 전까지 반복 
		num = Run.mainManu(); //GraphicEditer클래스의 mainManu함수 실행 
	}
	
	return 0;
}
