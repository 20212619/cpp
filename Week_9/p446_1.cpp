#include <iostream>
using namespace std;

class Point {
protected:
    int x, y;
public:
    Point(int x0, int y0) : x(x0), y(y0) {}
    virtual void draw() {  // virtual 키워드 추가
        cout << "x < " << x << ", y < " << y << " 에 점을 그려라.\n";
    }
};

class Rectangle : public Point {
private:
    int width, height;
public:
    Rectangle(int x0, int y0, int w, int h) : Point(x0, y0), width(w), height(h) {}
    void draw() override {  // 이제 override가 정상적으로 동작
        cout << x << "," << y << "에 가로 " << width << " 세로 " << height << "인 사각형을 그려라.\n";
    }
};

int main() {
    Point p(1, 2);
    p.draw();

    Rectangle r(2, 3, 100, 200);
    r.draw();

    return 0;
}