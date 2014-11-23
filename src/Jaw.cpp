#include "Jaw.h"

Jaw::Jaw(std::string config, std::string texture):Actor::Actor(){
    objectType="Jaw";
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node jawnode = doc.child("root").find_child_by_attribute("Actor", "name", "Jaw");
    
    if (jawnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    //  std::cout << "start preparing frames" << std::endl;
    prepareFrameInfo(jawnode);
    // std::cout << "Finish preparing frames" << std::endl;
    Load(texture);
    sf::Image *img = new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
    type = VisibleGameObject::JAWS;
}

void Jaw::attack(Actor& actor){
    if (actor.type==VisibleGameObject::BOND &&closeContact(actor)) {
        Actor::attack();
    }
}
