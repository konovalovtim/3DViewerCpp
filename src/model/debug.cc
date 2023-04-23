#include "model.h"

int main() {
  s21::PartObject M;
  std::string path = "/Users/ikudr/github/3DViewerCpp/src/objs/logo_s21.obj";
  M.OpenObject(path);
  for (auto elem : M.vertexes_) {
    std::cout << elem;
  }
  return 0;
}