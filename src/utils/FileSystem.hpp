//
// Created by Spark on 29/04/2019.
//

#ifndef DREAMINENGINE_FILESYSTEM_H
#define DREAMINENGINE_FILESYSTEM_H

#include <vector>
#include <string>
#include <cppfs/Tree.h>
#include <cppfs/FileHandle.h>

namespace utils {
    namespace filesystem {
        std::string get_filename(const std::string& path);

        bool is_file(const std::string& path);

        bool is_directory(const std::string& path);

        bool set_working_path(const std::string& path);

        void get_tree_filepaths(std::unique_ptr<cppfs::Tree>& file_tree, std::vector<std::string>& paths, bool tidy = true);

        // # TODO return list of list of ... of vectors (std::vector<std::string>...), representing the tree and containing all the item paths !
        void get_tree(const std::string& path, std::vector<std::string>& paths, bool tidy = true, bool include_hash = false);

        std::string get_current_path();

        std::vector<std::string> get_directory_entries(const std::string & path);

        void print_directory_entries(const std::string &path);

        cppfs::FileHandle get_entry(const std::string &path);
    }
}

#endif //DREAMINENGINE_FILESYSTEM_H
