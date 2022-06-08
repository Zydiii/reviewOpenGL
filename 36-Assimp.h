#pragma once
#include "setting.h"

int assimpModel()
{
    /* ���� glfw */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    /* ���ô��� */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* ���� glad */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* �ߵ� y �� */
    stbi_set_flip_vertically_on_load(true);

    /* ������Ȼ��� */
    glEnable(GL_DEPTH_TEST);

    /* ʹ�� Shader */
    Shader ourShader("ShaderSource/30-VertexShader.vs", "ShaderSource/30-GeometryShader.fs");

    /* ����ģ�� */
    Model ourModel("Source/model/flight/commander.obj");

    /* ��Ⱦѭ�� */
    while (!glfwWindowShouldClose(window))
    {
        cout << "Frame" << endl;
        TC.update();

        /* ������ */
        processInput(window);

        /* ���������� */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ���� Shader */
        ourShader.use();

        /* ��ȡ�۲����ͶӰ����λ�ƾ��� */
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        /* ͳ����� */
        calDepth();

        /* ���������� */
        glfwSwapBuffers(window);
        glfwPollEvents();

        cout << "cost time:" << TC.getTimerMilliSec() << "ms" << endl;
        //cout << "cost time:" << TC.getTimerMicroSec() << "us" << endl;
    }

    /* �ͷ���Դ */
    glfwTerminate();

    return 0;
}