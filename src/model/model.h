#ifndef CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_
#define CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

#include <stdexcept>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

struct PartObject {
  std::vector<std::vector<unsigned>> facets{};
  std::vector<double> vertexes{};
    void ParsingVertex(std::string &line);
    void ParsingFacet(std::string &line, std::size_t &position_old_vertexes);
    void OpenObject(std::string line);
};

#endif //CPP4_3DVIEWER_V2_0_1_OBJECTMODEL_H_

//class ObjectModel {
//    struct PartObject {
//      PartObject() = default;
//      ~PartObject() = default;
//      std::vector<std::tuple<double, double, double>> vertexes;
//      std::vector<std::vector<std::tuple<int, int, int>>> facets;
//    };
//  public:
//    static ObjectModel* GetInstance();
//
//    PartObject &operator[](const std::size_t &);
//    void OpenObject(std::string file_name);
//    std::size_t size();
//    bool empty();
//    void clear();
//
//  private:
//    static ObjectModel *instance;
//
//    ObjectModel();
//    ~ObjectModel();
//
//    std::vector<PartObject> models{};
//};
