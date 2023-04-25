#include "glview.h"

#include "model/connect.h"

#define GL_SILENCE_DEPRECATION

glview ::glview(QWidget* parent) : QOpenGLWidget{parent} {}

void glview ::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LINE_STIPPLE);
}

void glview ::paintGL() {
  update();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //Блок отвечает за проекцию
  if (projection_type) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fov = 60.0 * M_PI / 180;  // 60 угол в градусах
    float heapHeight = 1 / (2 * tan(fov / 2));
    glFrustum(-1, 1, -1, 1, heapHeight, 4);
    glTranslated(0, 0, -heapHeight * 2);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0,
                    model.vertexes_.data());
  glClearColor(background_color[0], background_color[1], background_color[2],
               background_color[3]);  // цвет заднего фона

  glColor3d(edge_color[0], edge_color[1], edge_color[2]);
  for (auto& facet : model.facets_) {
    glDrawElements(GL_LINE_LOOP, facet.size(), GL_UNSIGNED_INT,
                   facet.data());
  }
  glLineWidth(edge_width);  // толщина ребра
  if (edge_type) {          //тип ребра
    glLineStipple(4, 0x1111);
  } else {
    glLineStipple(4, 0xFFFF);
  }
  if (vertex_type) {  // тип вершины
    if (vertex_type == 1) {
      glEnable(GL_POINT_SMOOTH);
      glColor3d(vertex_color[0], vertex_color[1], vertex_color[2]);
      glDrawArrays(GL_POINTS, 0, model.vertexes_.size() / 3);
      glPointSize(vertex_width);  // толщина вершины
      glDisable(GL_POINT_SMOOTH);
    } else {
      glColor3d(vertex_color[0], vertex_color[1], vertex_color[2]);
      glDrawArrays(GL_POINTS, 0, model.vertexes_.size() / 3);
      glPointSize(vertex_width);  // толщина вершины
    }
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}




//void glview::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

//void glview::mouseMoveEvent(QMouseEvent* mo) {
//  rotation_object_t(&object, (0.001 / M_PI * (mo->pos().y() - mPos.y())) * -1,
//                    xAxis);
//  rotation_object_t(&object, (0.001 / M_PI * (mo->pos().x() - mPos.x())) * -1,
//                    yAxis);
//  update();
//}

//void glview::wheelEvent(QWheelEvent* event) {
//  if (event->angleDelta().y() > 0) {
//    zoom_object_t(&object, 0.9);
//  } else {
//    zoom_object_t(&object, 1.1);
//  }
//  update();
//}

void glview::mousePressEvent(QMouseEvent* mouse) {
  mPos = mouse->pos();
}

void glview::mouseMoveEvent(QMouseEvent* mouse) {
  double val_x = 0.013 / M_PI * (mouse->pos().y() - mPos.y());
  model.Rotate(val_x, s21::Model::xAxis);
  double val_y = 0.013 / M_PI * (mouse->pos().x() - mPos.x());
  model.Rotate(val_y, s21::Model::yAxis);
  mPos = mouse->pos();
  update();
}

void glview::wheelEvent(QWheelEvent* mouse) {
  if (mouse->angleDelta().y() > 0) {
    model.Scale(103);
  } else {
    model.Scale(97);
  }
  update();
}
