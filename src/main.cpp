#include <iostream>

#include "mathematics/complex.hpp"

#include "lua/LuaScript.h"

#include "utils/types.h"

#include "utils/FileSystem.hpp"

#include "entities/Entity.h"

#include "events/Events.h"
#include "events/EventSubscriber.h"

class Scene
{
public:
    Scene() {}
};

/// Main program function
int main(int argc, char **argv)
{
    Scene *scene = new Scene();
    Entity e = Entity("e1", 1);
    events::Events *ev = new events::Events(scene);
    auto path = utils::filesystem::get_current_path();
    std::cout << "Current main path: " << path << std::endl;

    utils::filesystem::print_directory_entries(path);

    auto a = utils::filesystem::get_entry(path + "\\DreamInEngine.exe");

//    utils::filesystem::print_directory_entries("");

    auto t_index = getTypeIndex<int>();

    utils::filesystem::get_tree(path);

    std::cout << "Setup status: SUCCESS !" << std::endl;
    // std::cin.get();

    return 0;
}
