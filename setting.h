#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/* ������� */
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// ʱ��
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

// ��Դ��λ��
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

/* ���ڴ�С�������ӿڵ����ص����� */
// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
// ���֡�����С������Ҫһ��GLFWwindow��Ϊ���ĵ�һ���������Լ�����������ʾ���ڵ���ά�ȡ�ÿ�����ڸı��С��GLFW�������������������Ӧ�Ĳ������㴦��
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    /* �����ӿ� */
    // �������OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)��OpenGL��ֻ��֪���������ݴ��ڴ�С��ʾ���ݺ�����
    // ����ͨ������glViewport���������ô��ڵ�ά��(Dimension)
    // glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
    // OpenGLĻ��ʹ��glViewport�ж����λ�úͿ�߽���2D�����ת������OpenGL�е�λ������ת��Ϊ�����Ļ���ꡣ
    glViewport(0, 0, width, height);
}

/* ������� */
// ����ͬ��Ҳϣ���ܹ���GLFW��ʵ��һЩ������ƣ������ͨ��ʹ��GLFW�ļ������뺯������ɡ�
// ���ǽ���ʹ��GLFW��glfwGetKey����������Ҫһ�������Լ�һ��������Ϊ���롣����������᷵����������Ƿ����ڱ����¡�
void processInput(GLFWwindow* window)
{
    // ���û�а��£�glfwGetKey���᷵��GLFW_RELEASE��
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // �����λ�õ���
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}