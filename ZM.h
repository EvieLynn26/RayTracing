#ifndef ZM_H
#define ZM_H


#include <QWidget>

using point_t = double;
using vec_t = double;

enum surface_type {
    PLANE = 1,
    ROUND = 2
};

const double n_glass = 3.72;

struct point {
  point_t x, y;

  point(): x(0), y(0) {}
  point(point_t x, point_t y): x(x), y(y) {}
};

struct obj {
    surface_type type;
    point param1, param2; // PLANE = point A, point B; ROUND = point O, {R, R}
    double n1, n2; // enter, exit
};

class ZM : public QWidget {

public:
    ZM(QWidget *parent = 0);

    size_t cnt;
    double param_n1, param_n2;

    void paintEvent(QPaintEvent *event);
    void DrawTheScene(QPainter *qp);  
};

struct vec {
  vec_t a, b;

  vec(): a(0), b(0) {}
  vec(vec_t a, vec_t b): a(a), b(b) {}

  vec operator*(double len) {
      return {a*len, b*len};
  }

  vec operator+(vec v) {
      return {a + v.a, b + v.b};
  }
};

struct ray {
    point st_point, fn_point;
    vec dest_vec;
    bool processed;

    ray(): st_point(), fn_point(), dest_vec(), processed(false) {}
    ray(point p, vec v): st_point(p), fn_point(), dest_vec(v), processed(false) {}
};
using ray_vec_t = std::vector<ray>;

#endif // ZM_H
