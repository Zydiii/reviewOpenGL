#pragma once

#include "setting.h"

int drawWindow()
{
    /* ���� glfw */
    // ��main�����е���glfwInit��������ʼ��GLFW
    glfwInit();
    // ʹ��glfwWindowHint����������GLFW
    // glfwWindowHint�����ĵ�һ����������ѡ������ƣ����ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ��
    // �ڶ�����������һ�����ͣ������������ѡ���ֵ
    // ������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // �ΰ汾��(Minor)��Ϊ3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
    // ��ȷ����GLFW������Ҫʹ�ú���ģʽ��ζ������ֻ��ʹ��OpenGL���ܵ�һ���Ӽ�
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* ���ô��� */
    // glfwCreateWindow������Ҫ���ڵĿ�͸���Ϊ����ǰ����������������������ʾ������ڵ����ƣ����⣩
    // ����������᷵��һ��GLFWwindow����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // �����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
    glfwMakeContextCurrent(window);

    /* ���� glad */
    // GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
    // ��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
    // GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ���
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* �����ӿڻص����� */
    // �����ڱ���һ����ʾ��ʱ��framebuffer_size_callbackҲ�ᱻ���á���������Ĥ(Retina)��ʾ����width��height�������Ա�ԭ����ֵ����һ�㡣
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* ��Ⱦѭ�� */
    // ����ϣ�����������������ر���֮ǰ���ϻ���ͼ���ܹ������û����롣
    // ������Ҫ�ڳ��������һ��whileѭ�������ǿ��԰�����֮Ϊ��Ⱦѭ��(Render Loop)��������������GLFW�˳�ǰһֱ�������С�
    /*
      ˫����(Double Buffer)
      Ӧ�ó���ʹ�õ������ͼʱ���ܻ����ͼ����˸�����⡣
      ������Ϊ���ɵ�ͼ����һ���ӱ����Ƴ����ģ����ǰ��մ����ң����϶��������صػ��ƶ��ɵġ�
      ����ͼ������˲����ʾ���û�������ͨ��һ��һ�����ɵģ���ᵼ����Ⱦ�Ľ���ܲ���ʵ��
      Ϊ�˹����Щ���⣬����Ӧ��˫������Ⱦ����Ӧ�ó���
      ǰ���屣�������������ͼ����������Ļ����ʾ�������еĵ���Ⱦָ����ں󻺳��ϻ��ơ�
      �����е���Ⱦָ��ִ����Ϻ����ǽ���(Swap)ǰ����ͺ󻺳壬����ͼ����������Գ�����֮ǰ�ᵽ�Ĳ���ʵ�о������ˡ�
    */
    // glfwWindowShouldClose����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
    while (!glfwWindowShouldClose(window))
    {
        // ����
        processInput(window);
        // ��Ⱦָ��
        // ����ʹ��һ���Զ������ɫ�����Ļ����ÿ���µ���Ⱦ������ʼ��ʱ����������ϣ�������������������ܿ�����һ�ε�������Ⱦ���
        // ������glClearColor�����������Ļ���õ���ɫ��������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ����������ǽ���Ļ����Ϊ�����ƺڰ��������ɫ��
        // glClearColor������һ��״̬���ú�������glClear��������һ��״̬ʹ�õĺ�������ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // ���ǿ���ͨ������glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ��壬���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��������������ֻ������ɫֵ����������ֻ�����ɫ���塣
        glClear(GL_COLOR_BUFFER_BIT);
        // glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        glfwSwapBuffers(window);
        // glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
        glfwPollEvents();
    }

    /* �����ͷ���Դ */
    // ����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ�����ǿ�����main������������glfwTerminate��������ɡ�
    glfwTerminate();
}