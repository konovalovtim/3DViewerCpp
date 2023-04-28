#ifndef CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
#define CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H

#include <vector>

namespace s21 {
/**
 * @brief Класс для хранения данных об Объекте
 */
// class VertexesAndFacets {
// public:
//   std::vector<std::vector<unsigned>> facets{}; ///< Вектор фигур
//   std::vector<double> vertexes{};              ///< Вектор вершин
// };

// class Mediator {
//   VertexesAndFacets *vertexesAndFacets;
// };

// class VertexesAndFacets;
class VertexesAndFacets {
 public:
  std::vector<std::vector<unsigned>> facets{}; ///< Вектор фигур
  std::vector<double> vertexes{};              ///< Вектор вершин
};

/**
 * Базовый Компонент обеспечивает базовую функциональность хранения экземпляра
 * посредника внутри объектов компонентов.
 */
class Mediator {
 protected:
  VertexesAndFacets *vertexesAndFacets_;

 public:
  Mediator(VertexesAndFacets *vertexesAndFacets = nullptr) : vertexesAndFacets_(vertexesAndFacets) {
  }
  void set_mediator(VertexesAndFacets *vertexesAndFacets) {
    this->vertexesAndFacets_ = vertexesAndFacets;
  }
};

} // namespace s21

#endif // CPP4_3DVIEWER_V2_0_1_PART_OBJECT_H
