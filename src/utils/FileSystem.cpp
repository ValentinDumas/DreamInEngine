//
// Created by Spark on 01/05/2019.
//

#include <cppfs/fs.h>
#include <cppfs/FilePath.h>

#include "FileSystem.hpp"

#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef MSVC_PLATFORM
#include <direct.h>
#define GetCurrentDir _getcwd
#else

#include <unistd.h>

#define GetCurrentDir getcwd
#endif

// TODO: Keep track of current/ old(s) selected paths in private (static) values ?

static std::string current_working_path = "";
//static cppfs::FileHandle current_working_dir; // private scope

std::vector<std::string> selected_paths; // Note: stores all the previous (and the current ?) selected path

// TODO: watch the behavior of this function when path does not exists in owner's FileSystem
std::string utils::filesystem::get_filename(const std::string &path) {
    cppfs::FilePath filePath(path);

    std::string filename = filePath.fileName();

    int found = -1;
    found = filename.find_last_of(".");

    std::string filename_without_extension;

    if (found == -1) {
        std::cout << "[Info] extension not found for file: " << filename.c_str() << std::endl;
        return ""; // folder = no filename
    } else // at least one "." char found
    {
        filename_without_extension = filename.substr(0, found); // return all before the lasrt dot "."
    }

    return filename_without_extension;
}

bool utils::filesystem::is_file(const std::string &path) {
    return !utils::filesystem::get_filename(path).empty(); // is_file if not empty
}

bool utils::filesystem::is_directory(const std::string &path) {
    return utils::filesystem::get_filename(path).empty(); // is_directory if empty
}

bool utils::filesystem::set_working_path(const std::string &path) {
    cppfs::FileHandle file_handle = cppfs::fs::open(path);

    if (!file_handle.exists()) {
        std::cout << "[Error] Path " << path << " does not exists on the current filesystem" << std::endl;
        return false;
    }

    current_working_path = path;
    return true;
}

// Process a tree level
void utils::filesystem::get_tree_filepaths(std::unique_ptr<cppfs::Tree> &file_tree, std::vector<std::string> &paths)
{
    for (auto &child : file_tree->listFiles()) {
        std::string tree_child_complete_path = (file_tree.get()->path() + "\\" + child); // file path (absolute)
        paths.push_back(tree_child_complete_path);
    }

    std::vector<std::unique_ptr<cppfs::Tree> > &tree_children = file_tree->children();

    for (auto &tree_child : tree_children) // if at least one children
    {
        utils::filesystem::get_tree_filepaths(tree_child, paths); // Look for deeper levels from this tree node
    }
//    }
}

void utils::filesystem::get_tree(const std::string &path, std::vector<std::string> &paths, bool include_hash) {
    cppfs::FileHandle file_handle = cppfs::fs::open(path);
    std::unique_ptr<cppfs::Tree> tree; // tree pointing to given (root) path

    if (file_handle.exists()) { // (root) path exists => tree opened
        tree = file_handle.readTree(path, include_hash); // Read the tree from the given path

        paths.push_back(tree->path()); // Get & Register the root path for this tree
//        std::cout << "TREE root path: " << tree->path() << std::endl;

        utils::filesystem::get_tree_filepaths(tree, paths);
    }
}

std::string utils::filesystem::get_current_path() {
    char path[FILENAME_MAX];

    GetCurrentDir(path, FILENAME_MAX);

    printf("Current working (binary) dir: %s\n", path);

    return std::string(path);
}

cppfs::FileHandle utils::filesystem::get_entry(const std::string &path) {
    cppfs::FileHandle entry = cppfs::fs::open(path);

    if (entry.isFile()) {
        std::cout << "[info] entry is a file" << std::endl;
    } else if (entry.isDirectory()) {
        std::cout << "[info] entry is a directory" << std::endl;
    } else if (!entry.exists()) {
        std::cout << "[info] Entry does not exists (at path " << path << ")" << std::endl;
    }

    return entry; // Not sure about this behaviour ! # TODO: check what happens when cppfs::FileHandle is "null"
}

std::vector<std::string> utils::filesystem::get_directory_entries(const std::string &path) {
    std::vector<std::string> entries;
    cppfs::FileHandle directory = cppfs::fs::open(path);

    for (std::string directory_entry : directory.listFiles()) {
        entries.push_back(directory_entry);
    }

    return entries;
}

void utils::filesystem::print_directory_entries(const std::string &path) {
    std::vector<std::string> entries = utils::filesystem::get_directory_entries(path);

    std::cout << "List of directory entries (" << path << "):" << std::endl;

    for (auto entry : entries) {
        std::cout << "-> " << entry << std::endl;
    }
}

// TODO: readfile;
// std::cout << cppfs::fs::open(tree_child_complete_path).readFile() << std::endl;