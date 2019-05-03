#include <iostream>

#include "mathematics/complex.hpp"

#include "lua/LuaScript.h"

#include "utils/types.h"

#include "utils/FileSystem.h"

/// Main program function
int main(int argc, char **argv)
{
    auto path = utils::filesystem::get_current_path();
    std::cout << "Current main path: " << path << std::endl;

    utils::filesystem::print_directory_entries(path);

    auto a = utils::filesystem::get_entry(path + "\\DreamInEngine.exe");

    std::cout << "External number's value: " << utils::filesystem::external_number << std::endl;
    utils::filesystem::print_directory_entries("");
    std::cout << "External number's value: "  << utils::filesystem::external_number << std::endl;

    auto t_index = getTypeIndex<int>();

    utils::filesystem::get_tree(path);

    std::cout << "Setup status: SUCCESS !" << std::endl;
    // std::cin.get();

    return 0;
}
