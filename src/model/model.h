#ifndef CPP4_3DVIEWER_V2_0_1_Model_H_
#define CPP4_3DVIEWER_V2_0_1_Model_H_

#include <float.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>

#include "VertexesAndFacets.h"

namespace s21 {
/**
 * @brief Класс предоставляющий работу объекта с программой
 */
class Model {
 public:
  /**
   * @brief Enum для обозначения осей
   */
  typedef enum Axis {
    xAxis,  ///< Ось X
    yAxis,  ///< Ось Y
    zAxis   ///< Ось Z
  } AxisPoints;

  /**
   * @brief Функция получения единственного объекта(SingleTon)
   * @return shared указатель на объект
   */
  static std::shared_ptr<Model> GetInstance();

  /**
   * @brief Функция открытия и обработки параметров объекта из заданного файла
   * @param line Путь до файла
   */
  void OpenObject(std::string line);

  /**
   * @brief Функция фиктивного перемещения
   * @details Объект перемещается только после GetVertexes()
   * @param coordinate
   * @param axis
   */
  void Move(double coordinate, Model::AxisPoints axis);
  /**
   * @brief Поворот всех точек относительно заданной оси
   * @param angle число для поворота
   * @param axis заданная ось
   */
  void Rotate(double angle, Model::Axis axis);
  /**
   * @brief Умножить каждую ось каждой точки на заданное число
   * @param coordinate число для умножения
   */
  void Scale(double coordinate);
  /**
   * @brief Сброс переменной отвечающую за перемещение объекта в пространстве
   */
  void CentralizeAfterMove();
  /**
   * @brief Перевод вершин объекта в объем 1x1x1 установка в центр координат
   */
  void NormalizationAndCentralize();

  /**
   * @brief Функция проверяет объект на пустоту
   * @return true если пуст, false в обратном
   */
  bool empty();
  /**
   * @brief Очистка векторов вершин и faсets.
   */
  void clear();
  /**
   * @brief Функция возвращает количество вершин и fasets
   * @return пара <размер вершин, размер faсets>
   */
  std::pair<std::size_t, std::size_t> size();

  /**
   * @brief Функция подготавливает данные вершин для OpenGL
   * @details Функция берет исходные данные вершин, изменяет все вершины под
   * Move так как он переносить только фиктивно и масштабирует под размер
   * экрана. Масштабирование сделано из-за виджета OpenGL, который адаптируется
   * под размер экрана только один раз. Функция занимает сложность прохождения
   * по всему массиву вершин.
   * @param width ширина экрана
   * @param height высота экрана
   * @return вектор вершин правильной ориентации в пространстве
   */
  const std::vector<double> &GetVertexes(double width = 1, double height = 1);
  /**
   * @brief Функция геттер faсets
   * @return const std::vector<std::vector<unsigned>>&
   */
  const std::vector<std::vector<unsigned>> &GetFacets();

  Model(const Model &) = delete;  ///< Удаление конструктора копирования
  Model(Model &&) = delete;  ///< Удаление конструктора переноса

  Model &operator=(const Model &) = delete;  ///< Удаление оператора копирования
  Model &operator=(Model &&) = delete;  ///< Удаление оператора переноса
  /**
   * @brief Класс Хранитель (memento) Не нарушая инкапсуляции,
   * фиксирует и выносит за пределы объекта его внутреннее состояние,
   * так чтобы позднее можно было восстановить в нем объект.
   * @return const std::vector<std::vector<unsigned>>&
   */
  class Memento {
   public:
    Memento() = default;
    /**
     * @brief Функция для взятия на хранение состояния класса Model.
     * @param объект из которого хотим сохранить текущее состояние
     */
    void takeFortune(Model &other);
    /**
     * @brief Функция для востановления состояния класса Model
     * на момент взятия(вызова метода take).
     * @param объект состояние которого хотим откатить до состояние вызова
     * метода take.
     */
    void recovery(Model &other);
    void clear();

   private:
    VertexesAndFacets Memento_model{};
    std::vector<double> Memento_vertexesAfterGetVertexes{};
    double Memento_axisMovement[3]{};
  };

 private:
  Model() = default;  ///< Дефолтный конструктор, приватный для SingleTon

  VertexesAndFacets model{};  ///< Все исходные данные об объекте
  std::vector<double>
      vertexesAfterGetVertexes{};  ///< Переменная хранящая вершины после вызова
                                   ///< GetVertexes
  double axisMovement[3]{};  ///< Переменная для хранения перемещений
                             ///< задаваемых во время работы с объектом

  /**
   * @brief Функция для обработки линии facet
   * @param models объект для сохранения преобразованной строки
   * @param line строка для обработки
   * @param position_old_vertexes количество обработанных вершин для
   * синхронизации с относительными индексами в facet
   */
  void ParsingFacet(std::vector<VertexesAndFacets> &models, std::string &line,
                    std::size_t &position_old_vertexes);
  /**
   * @brief Функция для обработки линии вершины
   * @param models объект для сохранения преобразованной строки
   * @param line строка для обработки
   */
  void ParsingVertex(std::vector<VertexesAndFacets> &models, std::string &line);
  /**
   * @brief Функция поворота объекта
   * @details Функция перемешает объект в исходных данных
   * Используется для централизации
   * @param coordinate количество перемещения объекта
   * @param axis выбранная координата для перемещения
   */
  void MoveReal(double coordinate, Model::AxisPoints axis);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_Model_H_
