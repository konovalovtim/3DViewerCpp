#include "model.h"

using namespace s21;

std::shared_ptr<Model> Model::GetInstance() {
  static std::shared_ptr<Model> instance(new Model());
  return instance;
}
