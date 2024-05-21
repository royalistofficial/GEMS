#include <main.hpp>

GLFWwindow* window;
GameGrid* Game = new GameGrid;


int main() {
	
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        Game->Render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    delete Game;
    glfwTerminate();
    return 0;
}
