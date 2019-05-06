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
#include "GLFWEnvironment.h"

#include "components/Texture.h"
#include "components/Sprite.h"
#include "components/Input.h"
#include "components/BoxPhysics.h"
#include "components/ContactListener.h"
#include "components/Shader.h"

void test_components()
{
    Texture texture = Texture();
    Sprite sprite = Sprite(texture, glm::vec2(10.0f, 10.0f));
    Input input = Input();
    BoxPhysics boxPhysics = BoxPhysics();
    ContactListener contactListener = ContactListener();
    Shader shader = Shader();

//    ResourceManager::LoadTexture("assets\\textures\\container.jpg", true, "container");
//    Sprite sprite(ResourceManager::GetTexture("container"), glm::vec2(0.0f, 0.0f));
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// TODO: always check if glad is initialized when making a "glad related call"

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

    GLFWEnvironment *glfw = new GLFWEnvironment();
    glfw->init();

    bool err = gladLoadGL() == 0;
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 0;
    }

    test_components(); // Note: processed only if glad is initialized

    // Main loop
    while (!glfw->quit())
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents(); // poll glfw events
        glfw->process_input(); // inputs related to glfw

        int display_w, display_h;
        glfwMakeContextCurrent(glfw->get_window());
        glfwGetFramebufferSize(glfw->get_window(), &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);
        glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwMakeContextCurrent(glfw->get_window());
        glfwSwapBuffers(glfw->get_window());
    }

    glfw->close();

    return 0;
}
