#include <bangtal>
#include <iostream>
using namespace std;
using namespace bangtal;

int studentX = 0, studentY = 570;
int pick_num = 0;


class Item : public Object
{
public:
	static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0,
		bool shown = true) {
		auto object = ObjectPtr(new Item(image, scene, x, y, shown));
		Object::add(object);
		return object;
	}

protected:
	Item(const string& image, ScenePtr scene, int x, int y, bool shown) : 
		Object(image, scene, x, y, shown) {}

public:
	virtual bool onMouse(int x, int y, MouseAction action) {
		if (!Object::onMouse(x, y, action)) {
			if (pick_num >= 2) {
				showMessage("F학점입니다! 다음 학기에 재수강하세요^_^");
			}
			else {
				pick();
				pick_num++;
			}
		}
	return true;
	}
};

class Move : public Object
{
public:
	static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0,
		bool shown = true) {
		auto object = ObjectPtr(new Move(image, scene, x, y, shown));
		Object::add(object);
		return object;
	}

protected:
	Move(const string& image, ScenePtr scene, int x, int y, bool shown) :
		Object(image, scene, x, y, shown) {}

public:
	virtual bool onMouse(int x, int y, MouseAction action) {
		if (Object::onMouse(x, y, action)) {
			if (studentX >= 1000 && studentY <= 100) {
				showMessage("휴~ 과제 제출 성공!");
			}
			else if (((studentX>=50) && (studentX <= 350) && (studentY <= 250) && (studentY >= -50))||
				((studentX >= 200) && (studentX <= 500) && (studentY <= 650) && (studentY >= 350)) ||
				((studentX >= 550) && (studentX <= 850) && (studentY <= 450) && (studentY >= 150)) ||
				((studentX >= 800) && (studentX <= 1100) && (studentY <= 800) && (studentY >= 450)))
			{
				showMessage("바이러스 감염! 과제 제출에 실패했습니다!");
			};
		};
			return true;
	}
};


int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	auto scene1 = Scene::create("VirusWorld", "images/table.png");
	auto scene2 = Scene::create("VirusWorld", "images/map.png");

	auto student = Object::create("images/student.png", scene2, studentX, studentY);
	student->setScale(0.3f);
	auto desktop = Object::create("images/desktop.png", scene1, 150, 240);
	desktop->setScale(0.8f);
	auto error = Item::create("images/error.png", scene1, 270, 440);
	error->setScale(0.3f);
	error->hide();
	auto usb = Object::create("images/usb.png", scene1, 670, 220);
	usb->setScale(0.2f);
	auto pencilcase = Item::create("images/pencilcase.png", scene1, 570, 130);
	auto clock = Item::create("images/clock.png", scene1, 720, 190);
	auto book = Item::create("images/book.png", scene1, 930, 170);
	auto cup = Item::create("images/cup.png", scene1, 380, 170);
	auto text1 = Object::create("images/text1.png", scene1, -10, 200);
	text1->hide();
	text1->setScale(0.7f);

	auto professor = Object::create("images/professor.png", scene2, 1130, 0);
	auto virus1 = Object::create("images/virus1.png", scene2, 200, 100);
	auto virus2 = Object::create("images/virus2.png", scene2, 350, 500);
	auto virus3 = Object::create("images/virus3.png", scene2, 700, 300);
	auto virus4 = Object::create("images/virus4.png", scene2, 950, 600);


	auto right = Move::create("images/right.png", scene2, 10, 0);
	right->setScale(0.15f);
    auto left = Move::create("images/left.png", scene2, 140, 0);
	left->setScale(0.15f);
	auto up = Move::create("images/up.png", scene2, 220, 0);
	up->setScale(0.15f);
	auto down = Move::create("images/down.png", scene2, 90, 0);
	down->setScale(0.15f);

	showMessage("방탈출 과제 끝!^-^ 컴퓨터를 눌러 과제를 제출하세요");


	desktop->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		error->show();
		showMessage("파일을 전송할 수 없습니다! ***에러***를 클릭하세요");
		return true;
		});

	error->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("물건들 사이 usb를 찾아 교수님께 직접 전달하세요. 물건을 누르면 물건을 치울 수 있습니다.");
		error->hide();
		text1->show();
		
		return true;
		});
	
	text1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		text1->hide();
		return true;
		});

	usb->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		showMessage("바이러스를 피해 교수님께 과제를 제출하세요(화살표를 클릭하면 이동)");
		return true;
		});



	right -> setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		studentX += 20;
		student->locate(scene2, studentX, studentY);
		return true;
		});

	left->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		studentX -= 20;
		student->locate(scene2, studentX, studentY);
		return true;
		});

	up->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		studentY += 20;
		student->locate(scene2, studentX, studentY);
		return true;
		});

	down->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		studentY -= 20;
		student->locate(scene2, studentX, studentY);
		return true;
		});


	startGame(scene1);

}