#ifndef GRAVITONIUM_MAP_H
#define GRAVITONIUM_MAP_H

#include "BaseObject.h"

class Map : public BaseObject {
private:
    void update();

    std::string mName;
public:
    Map(b2World *);

    void setMap(const std::string &);

    std::string getMapName() const;
};

#endif //GRAVITONIUM_MAP_H