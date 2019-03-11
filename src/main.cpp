#include "utilmathex.h"

int main() {
	using namespace  util::math;
	vec4 a(1,2,3,4);
	vec4 b(1,2,3,4);
	mat4 view;
	mat4 proj;
	vec4 pos(5, 6, -5, 1);
	vec4 at(0, 0, 0, 1);
	vec4 up(0, 1, 0, 1);
	
	view.lookat(pos, at, up);
	proj.projection(45, 1.0, 0.1, 100);
	(a + b).print();
	(a - b).print();
	(a * b).print();
	(a / b).print();
	a += b;
	a.print();
	a -= b;
	a.print();
	a *= b;
	a.print();
	a /= b;
	a.print();
	auto c = view * a;
	auto d = proj * a;
	c.print();
	d.print();
	auto m = proj * view;
	auto e = m * a;
	e.print();
	e /= e.w;
	e.print();
	return 0;

}
