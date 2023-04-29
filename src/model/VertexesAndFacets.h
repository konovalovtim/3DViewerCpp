#ifndef CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
#define CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H

#include <list>
#include <vector>

namespace s21 {
/**
 * @brief Класс для хранения данных об Объекте
 */
class VertexesAndFacets {
 public:
  std::vector<std::vector<unsigned>> facets{};  // Вектор фигур
  std::vector<double> vertexes{};               // Вектор вершин
};

class Mediator {
  public:
  VertexesAndFacets model;
  std::vector<Mediator *> mediator;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
