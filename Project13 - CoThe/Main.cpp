#include <iostream>
#include <vector>

using namespace std;

// Các lớp 
class Piece;		// Chứa thông tin về 1 quân cờ 
class Node;			// Chứa thông tin bàn cờ  
class Position;		// Chứa thông tin tọa độ 
class Step;			// Chúa thông tin về 1 nước đi 
class Rule;			// Chứa bộ luật di chuyển quân 
class Controller;	// Điều khiển hoạt động của chương trình 

// Hằng số và biến toàn cục 

// Hàm số 

// Chi tiết các lớp 
class Piece {
private:
	int type;
	int team;
public:
	Piece();
	Piece(int type, int team);

	// get, set
	void setType(int type);
	void setTeam(int team);
	int getType();
	int getTeam();

	// hàm khác 

	// hằng 
	static const int TUONGS = 1;
	static const int SI = 2;
	static const int TUONGJ = 3;
	static const int MA = 4;
	static const int XE = 5;
	static const int PHAO = 6;
	static const int TOT = 7;

	static const int NONE = -1;
	static const int NEUTRAL = 0;
	static const int RED_TEAM = 1;
	static const int BLUE_TEAM = 2;
};

class Node {
private:
	vector<vector<Piece>> matrix;
	int depth;
	int status;
	int dad;
	int numOfChild;
public:
	Node();

	// get, set
	void setMatrix(vector<vector<Piece>> matrix);
	void setDepth(int depth);
	void setStatus(int status);
	void setDad(int dad);
	void setNumOfChild(int numOfChild);
	vector<vector<Piece>> getMatrix();
	int getDepth();
	int getStatus();
	int getDad();
	int getNumOfChild();

	// Hàm khác 
	void input();												// Nhập 1 bàn cờ từ bàn phím 
	Piece getPiece(Position pos);								// Lấy 1 quân cờ dựa vào vị trí 
	int checkStatus();											// Kiểm tra thắng hay thua 
	static vector<Node> ext(Node node, int team, int index);	// Mở rộng 1 node với đội và vị trí hiện tại truyền vào 
	void newNode(Position pos, Position newPos, int index);	// Node mới dựa vào vị trí di chuyển

	// Hằng 
	static const int DEFEAT_STATUS = -1;
	static const int PENDING_STATUS = 0;
	static const int WIN_STATUS = 1;
};

class Position {
private:
	int x, y;
public:
	Position();
	Position(int x, int y);

	// get, set
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
};

class Step {
private:
	Position start, end;
public:
	Step();
	Step(Position start, Position end);

	// get, set
	void setStart(Position start);
	void setEnd(Position end);
	Position getStart();
	Position getEnd();
};

class Rule {
private:
	static bool square(Position pos, Piece pie, Piece newPie);					// Luật kẻ ô, tướng và sĩ không thể di chuyển ra ngoài phạm vi cố định 
	static bool square2(Position pos, Piece pie, Piece midPie, Piece newPie);	// Luật tượng di chuyển chéo, không được sang sông và có chặn 
	static bool charL(Position pos, Piece pie, Piece midPie, Piece newPie);		// Luật mã di chuyển thẳng rồi chéo, có chặn 
	static int straight(Position pos, Piece pie, Piece newPie);					// Luật xe di chuyển thẳng 
	static int fly(Position pos, Piece pie, Piece newPie, int mid);				// Luật pháo di chuyển thẳng, có thể bay 
	static bool one(Position pos, Piece pie, Piece newPie);						// Luật tốt di chuyển đơn 
public:
	static vector<Position> tuongsRule(Node node, Position start);
	static vector<Position> siRule(Node node, Position start);
	static vector<Position> tuongjRule(Node node, Position start);
	static vector<Position> maRule(Node node, Position start);
	static vector<Position> xeRule(Node node, Position start);
	static vector<Position> phaoRule(Node node, Position start);
	static vector<Position> totRule(Node node, Position start);
};

class Controller {
private:
	vector<Node> arr;
	int itr;
public:
	Controller();

	// get, set
	void setArr(vector<Node> arr);
	void setItr(int itr);
	vector<Node> getArr();
	int getItr();

	// hàm khác 
	void addNode(Node node);				// Thêm 1 node mới toanh vào mảng 
	void extOnce(int team);					// mở rộng một lớp 
	int getSize();							// lấy kích thước mảng 
};

int main() {
	Node start = Node();
	Controller controller = Controller();

	cout << "Nhap mang: ";
	start.input();
	controller.addNode(start);

	cout << "Kich thuoc dau: " << controller.getSize() << "\n";
	bool turn = true;
	for (int i = 0; i < 3; ++i) {
		if (turn) {
			controller.extOnce(Piece::RED_TEAM);
		}
		else {
			controller.extOnce(Piece::BLUE_TEAM);
		}
		turn = !turn;
	}
	cout << "Kich thuoc sau: " << controller.getSize() << "\n";
	return 0;
}

// Định nghĩa hàm và các lớp

Piece::Piece() {
	this->type = Piece::NEUTRAL;
	this->team = Piece::NEUTRAL;
}

Piece::Piece(int type, int team) {
	this->type = type;
	this->team = team;
}

void Piece::setType(int type) {
	this->type = type;
}

void Piece::setTeam(int team) {
	this->team = team;
}

int Piece::getType() {
	return type;
}

int Piece::getTeam() {
	return team;
}

Node::Node() {
	this->depth = 0;
	this->status = Node::PENDING_STATUS;
	this->dad = -1;
	this->numOfChild = 0;
}

void Node::setMatrix(vector<vector<Piece>> matrix) {
	this->matrix = matrix;
}

void Node::setDepth(int depth) {
	this->depth = depth;
}

void Node::setStatus(int status) {
	this->status = status;
}

void Node::setDad(int dad) {
	this->dad = dad;
}

void Node::setNumOfChild(int numOfChild) {
	this->numOfChild = numOfChild;
}

vector<vector<Piece>> Node::getMatrix()
{
	return matrix;
}

int Node::getDepth() {
	return depth;
}

int Node::getStatus() {
	return status;
}

int Node::getDad() {
	return dad;
}

int Node::getNumOfChild() {
	return numOfChild;
}

void Node::input() {
	matrix.resize(10);
	for (int i = 0; i < 10; ++i) {
		matrix.at(i).resize(9);
		for (int j = 0; j < 9; ++j) {
			char c;
			cin >> c;
			
			// trống
			if (c == '.') {
				matrix.at(i).at(j) = Piece(Piece::NEUTRAL, Piece::NEUTRAL);
			}
			// đội đỏ 
			else if (c >= 'a' && c <= 'g') {
				matrix.at(i).at(j) = Piece(c - 'a' + 1, Piece::RED_TEAM);
			}
			// đội xanh 
			else if (c >= 'A' && c <= 'G') {
				matrix.at(i).at(j) = Piece(c - 'A' + 1, Piece::BLUE_TEAM);
			}
			else {
				--j;
			}
		}
	}
}

Piece Node::getPiece(Position pos) {
	if (pos.getX() >= 0 && pos.getX() <= 8 && pos.getY() >= 0 && pos.getY() <= 9) {
		return matrix.at(pos.getY()).at(pos.getX());
	}
	return Piece(Piece::NONE, Piece::NONE);
}

int Node::checkStatus() {
	bool red = false, blue = false;
	for (int i = 0; i <= 2 && !red; ++i) {
		for (int j = 3; j <= 5; ++j) {
			if (matrix.at(i).at(j).getType() == Piece::TUONGS) {
				red = true;
				break;
			}
		}
	}
	for (int i = 7; i <= 9 && !blue; ++i) {
		for (int j = 3; j <= 5; ++j) {
			if (matrix.at(i).at(j).getType() == Piece::TUONGS) {
				blue = true;
				break;
			}
		}
	}

	if (red) {
		if (blue) {
			return Node::PENDING_STATUS;
		}
		return Node::WIN_STATUS;
	}
	return Node::DEFEAT_STATUS;
}

vector<Node> Node::ext(Node node, int team, int index) {
	vector<Node> result;

	Position pos = Position();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j) {
			pos.setX(j);
			pos.setY(i);
			Piece p = node.getPiece(pos);
			vector<Position> posArr;

			if (p.getTeam() == team) {
				switch (p.getType()) {
				case Piece::TUONGS: {
					posArr = Rule::tuongsRule(node, pos);
					break;
				}
				case Piece::SI: {
					posArr = Rule::siRule(node, pos);
					break;
				}
				case Piece::TUONGJ: {
					posArr = Rule::tuongjRule(node, pos);
					break;
				}
				case Piece::MA: {
					posArr = Rule::maRule(node, pos);
					break;
				}
				case Piece::XE: {
					posArr = Rule::xeRule(node, pos);
					break;
				}
				case Piece::PHAO: {
					posArr = Rule::phaoRule(node, pos);
					break;
				}
				case Piece::TOT: {
					posArr = Rule::totRule(node, pos);
					break;
				}
				}
			}

			for (int k = 0; k < posArr.size(); ++k) {
				Node newNode = node;
				newNode.newNode(pos, posArr.at(k), index);
				result.push_back(newNode);
			}
		}
	}

	return result;
}

void Node::newNode(Position pos, Position newPos, int index) {
	Piece p = getPiece(pos);
	matrix.at(newPos.getY()).at(newPos.getX()) = p;
	matrix.at(pos.getY()).at(pos.getX()) = Piece(Piece::NEUTRAL, Piece::NEUTRAL);

	++depth;
	status = checkStatus();
	dad = index;
	numOfChild = 0;
}

Position::Position() {
	this->x = -1;
	this->y = -1;
}

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

void Position::setX(int x) {
	this->x = x;
}

void Position::setY(int y) {
	this->y = y;
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}

Step::Step() {
	this->start = Position();
	this->end = Position();
}

Step::Step(Position start, Position end) {
	this->start = start;
	this->end = end;
}

void Step::setStart(Position start) {
	this->start = start;
}

void Step::setEnd(Position end) {
	this->end = end;
}

Position Step::getStart() {
	return start;
}

Position Step::getEnd() {
	return end;
}

bool Rule::square(Position pos, Piece pie, Piece newPie) {
	if (newPie.getTeam() < 0 || pie.getTeam() == newPie.getTeam()) {
		return false;
	}
	if (pos.getX() >= 3 && pos.getX() <= 5 && ((pos.getY() >= 0 && pos.getY() <= 2)
		|| (pos.getY() >= 7 && pos.getY() <= 9))) {
		return true;
	}
	return false;
}

bool Rule::square2(Position pos, Piece pie, Piece midPie, Piece newPie) {
	if (newPie.getTeam() < 0 || pie.getTeam() == newPie.getTeam() || midPie.getTeam() != Piece::NEUTRAL) {
		return false;
	}
	if (pos.getY() == 0 || pos.getY() == 2 || pos.getY() == 4 || pos.getY() == 5 || pos.getY() == 7 || pos.getY() == 9) {
		return true;
	}
	return false;
}

bool Rule::charL(Position pos, Piece pie, Piece midPie, Piece newPie) {
	if (newPie.getTeam() < 0 || pie.getTeam() == newPie.getTeam() || midPie.getTeam() != Piece::NEUTRAL) {
		return false;
	}
	return true;
}

int Rule::straight(Position pos, Piece pie, Piece newPie) {
	// 1 có thể đi
	// 0 có thể đi nhưng phải dừng lại sau đó 
	// -1 không thể đi 
	if (newPie.getTeam() < 0 || pie.getTeam() == newPie.getTeam()) {
		return -1;
	}
	if (newPie.getTeam() > 0 && pie.getTeam() != newPie.getTeam()) {
		return 0;
	}
	return 1;
}

int Rule::fly(Position pos, Piece pie, Piece newPie, int mid) {
	// 2 có thể bay 
	// 1 có thể đi
	// 0 không thể đi nhưng có thể bay về sau
	// -1 không thể đi và không thể bay 
	if (newPie.getTeam() < 0) {
		return -1;
	}
	if (mid == 1) {
		if (newPie.getTeam() == Piece::NEUTRAL) {
			return 1;
		}
		return 0;
	}
	if (mid == 0) {
		if (newPie.getTeam() > 0 && pie.getTeam() != newPie.getTeam()) {
			return 2;
		}
		if (pie.getTeam() == newPie.getTeam()) {
			return -1;
		}
		return 0;
	}
	return -1;
}

bool Rule::one(Position pos, Piece pie, Piece newPie) {
	if (newPie.getTeam() < 0 || pie.getTeam() == newPie.getTeam()) {
		return false;
	}
	return true;
}

vector<Position> Rule::tuongsRule(Node node, Position start) {
	// Xét thứ tự lên, phải, xuống, trái 
	vector<Position> result;

	Position pos = Position(start.getX(), start.getY() + 1);
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() + 1, start.getY());
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX(), start.getY() - 1);
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() - 1, start.getY());
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	//cout << "Tuongs: " << result.size();

	return result;
}

vector<Position> Rule::siRule(Node node, Position start) {
	// Xét thứ tự trên phải, dưới phải, dưới trái, trên trái 
	vector<Position> result;

	Position pos = Position(start.getX() + 1, start.getY() + 1);
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() + 1, start.getY() - 1);
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() - 1, start.getY() - 1);
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() - 1, start.getY() - 1);
	if (Rule::square(pos, node.getPiece(start), node.getPiece(pos))) {
		result.push_back(pos);
	}

	//cout << "Si: " << result.size();

	return result;
}

vector<Position> Rule::tuongjRule(Node node, Position start) {
	// Xét thứ tự trên phải, dưới phải, dưới trái, trên trái 
	vector<Position> result;

	Position pos = Position(start.getX() + 2, start.getY() + 2);
	Position midPos = Position(start.getX() + 1, start.getY() + 1);
	if (Rule::square2(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() + 2, start.getY() - 2);
	midPos = Position(start.getX() + 1, start.getY() - 1);
	if (Rule::square2(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() - 2, start.getY() - 2);
	midPos = Position(start.getX() - 1, start.getY() - 1);
	if (Rule::square2(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	pos = Position(start.getX() - 2, start.getY() + 2);
	midPos = Position(start.getX() - 1, start.getY() + 1);
	if (Rule::square2(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	//cout << "Tuongj: " << result.size();

	return result;
}

vector<Position> Rule::maRule(Node node, Position start) {
	// Xét thứ tự theo chiều kim đồng hồ tính từ hướng 11h.
	vector<Position> result;

	// 11h
	Position pos = Position(start.getX() - 1, start.getY() + 2);
	Position midPos = Position(start.getX(), start.getY() + 1);
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 1h
	pos = Position(start.getX() + 1, start.getY() + 2);
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 2h
	pos = Position(start.getX() + 2, start.getY() + 1);
	midPos = Position(start.getX() + 1, start.getY());
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 4h
	pos = Position(start.getX() + 2, start.getY() - 1);
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 5h
	pos = Position(start.getX() + 1, start.getY() - 2);
	midPos = Position(start.getX(), start.getY() - 1);
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 7h
	pos = Position(start.getX() - 1, start.getY() - 2);
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 8h
	pos = Position(start.getX() - 2, start.getY() - 1);
	midPos = Position(start.getX() - 1, start.getY());
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	// 10h
	pos = Position(start.getX() - 2, start.getY() + 1);
	if (Rule::charL(pos, node.getPiece(start), node.getPiece(midPos), node.getPiece(pos))) {
		result.push_back(pos);
	}

	//cout << "Ma: " << result.size();

	return result;
}

vector<Position> Rule::xeRule(Node node, Position start) {
	// Xét thứ tự trên, phải, dưới, trái 
	vector<Position> result;

	// trên 
	int i = 1;
	Position pos = Position(start.getX(), start.getY() + i);
	int re = straight(pos, node.getPiece(start), node.getPiece(pos));
	for (; re > 0; ++i, pos = Position(start.getX(), start.getY() + i), re = straight(pos, node.getPiece(start), node.getPiece(pos))) {
		if (re >= 0) {
			result.push_back(pos);
		}
	}

	// phải  
	i = 1;
	pos = Position(start.getX() + i, start.getY());
	re = straight(pos, node.getPiece(start), node.getPiece(pos));
	for (; re > 0; ++i, pos = Position(start.getX() + i, start.getY()), re = straight(pos, node.getPiece(start), node.getPiece(pos))) {
		if (re >= 0) {
			result.push_back(pos);
		}
	}

	// dưới   
	i = 1;
	pos = Position(start.getX(), start.getY() - i);
	re = straight(pos, node.getPiece(start), node.getPiece(pos));
	for (; re > 0; ++i, pos = Position(start.getX(), start.getY() - i), re = straight(pos, node.getPiece(start), node.getPiece(pos))) {
		if (re >= 0) {
			result.push_back(pos);
		}
	}

	// trái   
	i = 1;
	pos = Position(start.getX() - i, start.getY());
	re = straight(pos, node.getPiece(start), node.getPiece(pos));
	for (; re > 0; ++i, pos = Position(start.getX() - i, start.getY()), re = straight(pos, node.getPiece(start), node.getPiece(pos))) {
		if (re >= 0) {
			result.push_back(pos);
		}
	}

	//cout << "Xe: " << result.size();

	return result;
}

vector<Position> Rule::phaoRule(Node node, Position start) {
	// Xét thứ tự trên, phải, dưới, trái 
	vector<Position> result;

	// trên 
	int i = 1;
	Position pos = Position(start.getX(), start.getY() + i);
	int re = fly(pos, node.getPiece(start), node.getPiece(pos), 1);
	for (; re >= 0; ++i, pos = Position(start.getX(), start.getY() + i), re = fly(pos, node.getPiece(start), node.getPiece(pos), re)) {
		if (re > 0) {
			result.push_back(pos);
		}
	}
	//cout << "\nTren: " << result.size();

	// phải 
	i = 1;
	pos = Position(start.getX() + i, start.getY());
	re = fly(pos, node.getPiece(start), node.getPiece(pos), 1);
	for (; re >= 0; ++i, pos = Position(start.getX() + i, start.getY()), re = fly(pos, node.getPiece(start), node.getPiece(pos), re)) {
		if (re > 0) {
			result.push_back(pos);
		}
	}

	//cout << "\nPhai: " << result.size();

	// dưới   
	i = 1;
	pos = Position(start.getX(), start.getY() - i);
	re = fly(pos, node.getPiece(start), node.getPiece(pos), 1);
	for (; re >= 0; ++i, pos = Position(start.getX(), start.getY() - i), re = fly(pos, node.getPiece(start), node.getPiece(pos), re)) {
		if (re > 0) {
			result.push_back(pos);
		}
	}

	//cout << "\nDuoi: " << result.size();

	// trái   
	i = 1;
	pos = Position(start.getX() - i, start.getY());
	re = fly(pos, node.getPiece(start), node.getPiece(pos), 1);
	for (; re > 0; ++i, pos = Position(start.getX() - i, start.getY()), re = fly(pos, node.getPiece(start), node.getPiece(pos), re)) {
		if (re >= 0) {
			result.push_back(pos);
		}
	}

	//cout << "\nTrai: " << result.size();

	return result;
}

vector<Position> Rule::totRule(Node node, Position start) {
	// Xét thứ tự trên, phải, trái 
	vector<Position> result;

	Piece t = node.getPiece(start);
	int i, min, max;
	if (t.getTeam() == Piece::RED_TEAM) {
		i = 1;
		min = 5;
		max = 9;
	}
	else {
		i = -1;
		min = 0;
		max = 4;
	}

	// trên 
	Position pos = Position(start.getX(), start.getY() + i);
	if (one(pos, t, node.getPiece(pos))) {
		result.push_back(pos);
	}

	// phải
	pos = Position(start.getX() + 1, start.getY());
	if (one(pos, t, node.getPiece(pos))) {
		result.push_back(pos);
	}

	// trái 
	pos = Position(start.getX() - 1, start.getY());
	if (one(pos, t, node.getPiece(pos))) {
		result.push_back(pos);
	}

	//cout << "Tot: " << result.size();

	return result;
}

Controller::Controller() {
	itr = 0;
}

void Controller::setArr(vector<Node> arr) {
	this->arr = arr;
}

void Controller::setItr(int itr) {
	this->itr = itr;
}

vector<Node> Controller::getArr() {
	return arr;
}

int Controller::getItr() {
	return itr;
}

void Controller::addNode(Node node) {
	arr.push_back(node);
}

void Controller::extOnce(int team) {
	int depth = arr.at(itr).getDepth();

	Node node = arr.at(itr);
	for (; depth == node.getDepth(); ++itr, node = arr.at(itr)) {
		if (node.getStatus() == Node::PENDING_STATUS) {
			vector<Node> newArr = Node::ext(node, team, itr);
			arr.insert(arr.end(), newArr.begin(), newArr.end());
			arr.at(itr).setNumOfChild(newArr.size());
			cout << "Search index = " << itr << " have " << newArr.size() << "child!\n";
		}
	}
}

int Controller::getSize() {
	return arr.size();
}
