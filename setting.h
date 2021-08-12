#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/* 窗口大小调整与视口调整回调函数 */
// 当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用
// 这个帧缓冲大小函数需要一个GLFWwindow作为它的第一个参数，以及两个整数表示窗口的新维度。每当窗口改变大小，GLFW会调用这个函数并填充相应的参数供你处理。
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    /* 配置视口 */
    // 必须告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)，OpenGL才只能知道怎样根据窗口大小显示数据和坐标
    // 可以通过调用glViewport函数来设置窗口的维度(Dimension)
    // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    // OpenGL幕后使用glViewport中定义的位置和宽高进行2D坐标的转换，将OpenGL中的位置坐标转换为你的屏幕坐标。
    glViewport(0, 0, width, height);
}

/* 输入控制 */
// 我们同样也希望能够在GLFW中实现一些输入控制，这可以通过使用GLFW的几个输入函数来完成。
// 我们将会使用GLFW的glfwGetKey函数，它需要一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下。
void processInput(GLFWwindow* window)
{
    // 如果没有按下，glfwGetKey将会返回GLFW_RELEASE。
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}