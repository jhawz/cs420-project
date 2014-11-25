
#include "Co.h"

Co::Co(std::string config, sf::Texture& t) : Actor::Actor() {
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
//    pugi::xml_node enemynode = doc.child("root").find_child_by_attribute("Actor"
//            ,"name", "Co");
    
  //  prepareFrameInfo(enemynode);
    Load(t, sf::Vector2i(0, 960), sf::Vector2i(32, 64));
    alive = true;
    type = VisibleGameObject::CO;
}

void Co::Update(float elapsedTime) {
    //animReq("stand", false);
 
}