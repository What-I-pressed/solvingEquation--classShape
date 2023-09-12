#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Equation {
	int a;
	int b;
	int c;
public:
	Equation(int a, int b, int c) : a(a), b(b), c(c) {};

	virtual float Solve()const = 0;

	virtual void Show()const = 0;

	int getA()const {
		return a;
	}

	int getB()const {
		return b;
	}

	int getC()const {
		return c;
	}
};

class LinearEquation: public Equation{
public:
	LinearEquation(int a, int b, int c) : Equation(a, b, c) {};

	float Solve()const override {
		return (getC() - getB()) / getA();
	}

	void Show()const override {
		cout << getA() << "x + (" << getB() << ") = " << getC() << endl;
	}
};

class QuadraticEquation : public Equation {
public:
	QuadraticEquation(int a, int b, int c) : Equation(a, b, c) {};

	float Solve()const override {
		float D = getB() * getB() - 4 * getA() * getC();
		if (D > 0) {
			cout << "This equation has two solutions.\nThe largest value will be returned" << endl;
			return (-getB() + sqrt(D))/ (2* getA());
		}
		if (D == 0) {
			cout << "This equation has one solution" << endl;
			return -getB() / (2 * getA());
		}
		else {
			cout << "This equation don't has solutions" << endl;
			return 0;
		}
	}

	void Show()const override {
		cout << getA() << "x^2 + (" << getB() << "x) + (" << getC() << ") = 0" << endl;
 	}
};

class Shape {
	string path;
public:
	Shape(string p) : path(p) {};

	void ClearFile()const {
		ofstream file(this->path, ios::trunc);
		file.close();
	}

	virtual void Show()const = 0;

	virtual string Draw()const = 0;

	virtual void Save()const = 0;

	virtual string Load()const = 0;
	
	string GetPath()const {
		return path;
	}
};

class Square: public Shape {
	int side;
	int x;
	int y;
public:
	Square(int side, int x, int y, string p) : side(side), x(x), y(y), Shape(p) {};

	void Show()const override {
		cout << "Area : " << side * side << endl;
	}

	string Draw()const override {
		string square = "";
		string space = "";
		for (int i = 0; i < this->side - 2; i++) {			//щоб не запускати постійно цикл який буде додавати пусти простір, зробив змінну з необхідною кількістю пробілів
			space += "  ";
		}
		for (int i = 0; i < this->side; i++, square += '\n') {
			for (int j = 0; j < this->x; j++) {
				square += "  ";
			};
			if (i == 0 || i == this->side - 1) {
				for (int j = 0; j < this->side; j++) {
					square += "# ";
				}
				continue;
			}
			square += "# " + space + '#';
		}
		return square;
	}

	void Save()const override {
		ofstream file(GetPath(), ios::app);
		for (int i = 0; i < this->y; i++) {
			file << '\n';
		}
		file << Draw();
		file.close();
	}

	string Load()const override{
		ifstream file(GetPath());
		string square = "";
		string temp;
		while (!file.eof()) {
			getline(file, temp);
			square += temp + '\n';
		}
		file.close();
		return square;
	}
};

class Rectangle : public Shape {
	int side1;
	int side2;
	int x;
	int y;
public:
	Rectangle(int side1, int side2, int x, int y, string p) : side1(side1), side2(side2), x(x), y(y), Shape(p) {};

	void Show()const override {
		cout << "Area : " << side1 * side2 << endl;
	}

	string Draw()const override {
		string rectangle = "";
		string space = "";
		for (int i = 0; i < this->side1 - 2; i++) {			//щоб не запускати постійно цикл який буде додавати пусти простір, зробив змінну з необхідною кількістю пробілів
			space += "  ";
		}
		for (int i = 0; i < this->side2; i++, rectangle += '\n') {
			for (int j = 0; j < this->x; j++) {
				rectangle += "  ";
			};
			if (i == 0 || i == this->side2 - 1) {
				for (int j = 0; j < this->side1; j++) {
					rectangle += "# ";
				}
				continue;
			}
			rectangle += "# " + space + '#';
		}
		return rectangle;
	}

	void Save()const override {
		ofstream file(GetPath(), ios::app);
		for (int i = 0; i < this->y; i++) {
			file << '\n';
		}
		file << Draw();
		file.close();
	}

	string Load()const override {
		ifstream file(GetPath());
		string rectangle = "";
		string temp;
		while (!file.eof()) {
			getline(file, temp);
			rectangle += temp + '\n';
		}
		file.close();
		return rectangle;
	}
};

class Circle : public Shape {
	int radius;
	int x;
	int y;
public:
	Circle(int radius, int x, int y, string p) : radius(radius), x(x), y(y), Shape(p) {};

	void Show()const override {
		cout << "Area : " << radius * radius * 3.14 << endl;
	}

	string Draw()const override {
		string circle = "";
		for (int y = 0; y <= this->y + this->radius + 3; y++, circle += '\n') {
			for (int x = 0; x <= this->radius + this->x + 3; x++) {
				if (radius + 2 >= sqrt((x - this->x) * (x - this->x) + (y - this->y) * (y - this->y))  &&
					sqrt((x - this->x) * (x - this->x) + (y - this->y) * (y - this->y)) >= radius) {
					circle += "# ";
				}
				else circle += "  ";
			}
		}
		return circle;
	}

	void Save()const override {
		ofstream file(GetPath(), ios::app);
		file << Draw();
		file.close();
	}

	string Load()const override {
		ifstream file(GetPath());
		string circle = "";
		string temp;
		while (!file.eof()) {
			getline(file, temp);
			circle += temp + '\n';
		}
		file.close();
		return circle;
	}
};

class Ellipse : public Shape {
	int side1;
	int side2;
	int x;
	int y;
public:
	Ellipse(int side1,int side2, int x, int y, string p) : side1(side1), side2(side2), x(x), y(y), Shape(p) {};

	void Show()const override {
		cout << "Area : i don't want to calculate" << endl;
	}

	string Draw()const override {
		string ellipse = "";
		string space = "";
		double largerSide = side1 > side2 ? this->side1 : this->side2;
		double smallerSide = largerSide == side1 ? this->side2 : this->side1;
		double ratio = (largerSide - smallerSide) / 1000;
		for (int i = 0; i < this->x; i++) {			//щоб не запускати постійно цикл який буде додавати пусти простір, зробив змінну з необхідною кількістю пробілів
			space += "  ";
		}
		int xCenter = this->side1 / 2 , yCenter = this->side2 / 2;
		for (double y = -1; y < side2 + 2; y++, ellipse += '\n') {
			ellipse += space;
			for (double x = -1; x < side1 + 2; x++) {
				if (1.3 + ratio>= ((x - xCenter) * (x - xCenter)) / (xCenter * xCenter) + ((y - yCenter) * (y - yCenter)) / (yCenter * yCenter) &&
					((x - xCenter) * (x - xCenter)) / (xCenter * xCenter) + ((y- yCenter) * (y - yCenter)) / (yCenter * yCenter) >= 1) {
					ellipse += "# ";
				}
				else ellipse += "  ";
			}
		}
		return ellipse;
	}

	void Save()const override {
		ofstream file(GetPath(), ios::app);
		for (int i = 0; i < this->y; i++) {
			file << '\n';
		}
		file << Draw();
		file.close();
	}

	string Load()const override {
		ifstream file(GetPath());
		string ellipse = "";
		string temp;
		while (!file.eof()) {
			getline(file, temp);
			ellipse += temp + '\n';
		}
		file.close();
		return ellipse;
	}
};

void main() {
	int i = 0;
	cout << "Select an equation type:\n" <<
		"linear equation(ax + b = c) - [1]\nquadratic equation(ax^2 + bx + c = 0) - [2]:\n";
	cin >> i;
	Equation* equat;
	int a, b, c;
	float x;
	switch (i) {
	case 1:
		cout << "Enter values a, b, c in this order" << endl;
		cin >> a;
		cin >> b;
		cin >> c;
		equat = new LinearEquation(a, b, c);
		equat->Show();
		x = equat->Solve();
		cout << "x = " << x << endl;
		break;
	case 2:
		cout << "Enter values a, b, c in this order" << endl;
		cin >> a;
		cin >> b;
		cin >> c;
		equat = new QuadraticEquation(a, b, c);
		equat->Show();
		x = equat->Solve();
		cout << "x = " << x << endl;
	}
	cout << "############################### shapes ###################################\n\n";
	cout << "0 1 2 3 4 5 6 7 8 9 10" << endl;
	string path("shapes.txt");
	vector<Shape*> shapes;
	shapes.push_back(new Square(13, 1, 2, path));
	shapes.push_back(new Rectangle(20, 12, 2, 2, path));
	shapes.push_back(new Circle(20, 25, 23, path));
	shapes.push_back(new Ellipse(50, 25, 5, 6, path));
	shapes[0]->ClearFile();
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->Save();
	}
	cout << shapes[0]->Load() << endl;
}