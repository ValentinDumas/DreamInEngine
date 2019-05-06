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

#include "components/Sprite.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void test_components()
{


//    ResourceManager::LoadTexture("assets\\textures\\container.jpg", true, "container");
//    Sprite sprite(ResourceManager::GetTexture("container"), glm::vec2(0.0f, 0.0f));
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

/// Main program function
int main(int argc, char **argv)
{
    Scene *scene = new Scene();
    Entity e = Entity("e1", 1);
    events::Events *ev = new events::Events(scene);
    auto path = utils::filesystem::get_current_path();
    std::cout << "Current main path: " << path << std::endl;

    utils::filesystem::print_directory_entries(path);

    //auto a = utils::filesystem::get_entry(path + "\\DreamInEngine.exe");

//    utils::filesystem::print_directory_entries("");

    auto t_index = getTypeIndex<int>();

    std::vector<std::string> assets_paths;
    utils::filesystem::get_tree(path, assets_paths);

    std::cout << "Setup status: SUCCESS !" << std::endl;
    // std::cin.get();

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    //const char* glsl_version = "#version 150"; Needed by ImGui
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    //const char* glsl_version = "#version 130"; // Needed by ImGui
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    bool err = gladLoadGL() == 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

    return 0;
}
