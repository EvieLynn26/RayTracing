#include <iostream>
#include <cmath>
#include <QPainter>
#include "ZM.h"


#define DEBUG
#ifdef DEBUG
    #define ON_DEBUG_PR(text) std::cout << text << '\n';
#else
    #define ON_DEBUG_PR(text)
#endif

std::vector<obj> objs;


ZM::ZM(QWidget *parent)
    : QWidget(parent)
{
    cnt = 0;
    param_n1 = 1;
    param_n2 = n_glass;
}

void ZM::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  QPainter qp(this);
  DrawTheScene(&qp);
}

void set_objs(double n1, double n2) {
    obj obj{PLANE, point{400, 0}, point{400, 1800}, n1, n2};
    objs.push_back(obj);

    return;
}

void draw_objs(QPainter *qp) {
    for (auto &obj: objs) {
        /*if (i%2)
            qp->setBrush(QBrush("#00000000"));
        else
            qp->setBrush(QBrush("#c56c00"));*/

        switch (obj.type) {
        case PLANE: {
            QPen pen(Qt::blue, 1, Qt::SolidLine);
            qp->setPen(pen);
            qp->drawLine(obj.param1.x, obj.param1.y, obj.param2.x, obj.param2.y);
            break;
        }
        case ROUND:
            break;
        default:
            break;
        }
    }
}

point compute_cross_dot(ray ray, obj obj) {
    point_t xi_start = ray.st_point.x, yi_start = ray.st_point.y;

    switch (obj.type) {
    case PLANE: {
        point A(obj.param1.x, obj.param1.y), B(obj.param2.x, obj.param2.y);
        vec n(A.y-B.y, B.x-A.x);

        int x1 = A.x, y1 = A.y, x2 = B.x, y2 = B.y;
        int t = (-x1*y2 + x2*y1 - n.b*yi_start - n.a*xi_start)/(n.a*ray.dest_vec.a + n.b*ray.dest_vec.b);

        point cross_dot (xi_start + ray.dest_vec.a * t, yi_start + ray.dest_vec.b * t);
        return cross_dot;
    }
    case ROUND:
        return {0, 0};
    default:
        return {0, 0};
    }
}

vec_t dot(vec u, vec v) {
    return (u.a*v.a + u.b*v.b);
}

vec compute_n(const obj &obj) {
    return {obj.param1.y - obj.param2.y, obj.param2.x - obj.param1.x};
}

vec compute_out_dest(vec v1, const obj  &obj) {
    vec n = compute_n(obj);

    vec_t v1n = dot(v1, n);
    double n1 = obj.n1, n2 = obj.n2;
    double coeff = n2*n2 - n1*n1;
    coeff /= (v1n*v1n);
    ++coeff;
    coeff = sqrt(coeff);
    --coeff;
    coeff *= v1n;

    vec v2 = v1 + n*coeff;
    return v2;
}

void one_ray_trace(size_t i, ray_vec_t &ray_pack) { // set fn_point for all ray's continuations
//TODO: more objs

    point cross_dot = compute_cross_dot(ray_pack[i], objs[0]);
    ray_pack[i].fn_point = cross_dot; // finish input ray
    ray_pack[i].processed = true;

    ON_DEBUG_PR("INPUT_RAY: st.x = " << ray_pack[i].st_point.x << "| st.y = " << ray_pack[i].st_point.y << "| fn.x = " << ray_pack[i].fn_point.x << "| y = " << ray_pack[i].fn_point.y)

    vec out_dest = compute_out_dest(ray_pack[i].dest_vec, objs[0]);// push_back output ray
    ray output_ray(cross_dot, out_dest);
    int t = 100;
    output_ray.fn_point = {output_ray.st_point.x + output_ray.dest_vec.a * t, output_ray.st_point.y + output_ray.dest_vec.b * t};
    ON_DEBUG_PR("OUTPUT: st.x = " << output_ray.st_point.x << "| st.y = " << output_ray.st_point.y << "|| fn.x = " << output_ray.fn_point.x << "| fn.y = " << output_ray.fn_point.y)
    ray_pack.push_back(output_ray);
    return;
}

void process_rays(ray_vec_t &ray_pack, size_t cnt) {
    for (size_t i = 0; i < cnt; ++i) {
        one_ray_trace(i, ray_pack);    }

    for (size_t i = 0; i < ray_pack.size(); ++i) {
        ON_DEBUG_PR("CHECK_PACK(in func): [" << i + 1 << "] fn.x = " << ray_pack[i].fn_point.x)
    }

    return;
}

ray_vec_t emit_rays(point st_p, size_t cnt) {
    ray_vec_t ray_pack{};
    for (size_t i = 0; i < cnt; ++i) {
        ray r_i{};
        r_i.st_point = st_p;
        double angle = M_PI_2/4 + M_PI_2 + ((M_PI-M_PI_2/2) / (cnt + 1))*(i + 1);
        ON_DEBUG_PR("angle = " << angle)

        r_i.dest_vec = {-cos(angle), -sin(angle)};
        ON_DEBUG_PR("ADD RAY: st.x = " << r_i.st_point.x << "| a = " << r_i.dest_vec.a << "| b = " << r_i.dest_vec.b)
        ray_pack.push_back(r_i);
    }

    return ray_pack;
}

void draw_rays(ray_vec_t &ray_pack, QPainter *qp) {
    QPen pen(Qt::black, 1, Qt::SolidLine);
    qp->setPen(pen);

    for (auto &ray: ray_pack) {
        //if (ray.processed)
            //ON_DEBUG_PR("SIZE = " << ray_pack.size())
            ON_DEBUG_PR("DRAW RAY: st.x = " << ray.st_point.x << "| st.y = " << ray.st_point.y << "|| fn.x = " << ray.fn_point.x << "| fn.y = " << ray.fn_point.y)
            qp->drawLine(ray.st_point.x, ray.st_point.y, ray.fn_point.x, ray.fn_point.y);
    }

    return;
}

void ZM::DrawTheScene(QPainter *qp) {
    set_objs(param_n1, param_n2);
    draw_objs(qp);

    point st_point(100, 250);
    if (0 == cnt)
        return;

    size_t ray_cnt = cnt;
    ray_vec_t ray_pack = emit_rays(st_point, ray_cnt); //  emit rays and put into vec
    process_rays(ray_pack, ray_cnt); // ray-tracing, adding continuations of rays into vec

    for (auto &r: ray_pack) {
        ON_DEBUG_PR("CHECK_PACK(in func): fn.x = " << r.fn_point.x)
    }

    draw_rays(ray_pack, qp); // draw all rays

    return;
}

/*
  //dot start()

  QPen pen(Qt::black, 2, Qt::SolidLine);
  //qp->setPen(pen);
  //qp->drawLine(start.x, start.y, compute_cross_dot(start, v1), , 40);

  //pen.setStyle(Qt::DashLine);
  qp->setPen(pen);

  dot A(120, 10), B(120, 200);

  qp->drawLine(A.x, A.y, B.x, B.y); // set lens

  dot S(30, 95); //light source

  int ray_cnt = 3;
  for (int i = 0; i < ray_cnt; ++i) {
    vec direction; // = emit_ray(i, ray_cnt, A.y, B.y); // vec of ray direction

    dot CD(A.x, A.y + (B.y - A.y)/(ray_cnt - 1)*(i)); // cross dot

    qp->drawLine(S.x, S.y, CD.x, CD.y);
  }

  pen.setStyle(Qt::DashDotLine);
  qp->setPen(pen);
  qp->drawLine(20, 120, 250, 120);

  pen.setStyle(Qt::DotLine);
  qp->setPen(pen);
  qp->drawLine(20, 160, 250, 160);

  pen.setStyle(Qt::DashDotDotLine);
  qp->setPen(pen);
  qp->drawLine(20, 200, 250, 200);

  QVector<qreal> dashes;
  qreal space = 4;

  dashes << 1 << space << 5 << space;

  pen.setStyle(Qt::CustomDashLine);
  pen.setDashPattern(dashes);

  qp->setPen(pen);
  qp->drawLine(20, 240, 250, 240);
}
*/
