#pragma once
#include "shader.h"
#include "setting.h"

int drawReverseTriangle()
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
    /* �����ӿڻص����� */
    // �����ڱ���һ����ʾ��ʱ��framebuffer_size_callbackҲ�ᱻ���á���������Ĥ(Retina)��ʾ����width��height�������Ա�ԭ����ֵ����һ�㡣
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* ���� glad */
    // GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
    // ��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
    // GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ���
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* ���嶥�� */
    // ��������ϣ����Ⱦһ�������Σ�����һ��Ҫָ���������㣬ÿ�����㶼��һ��3Dλ�á����ǻὫ�����Ա�׼���豸�������ʽ��OpenGL�Ŀɼ����򣩶���Ϊһ��float���顣
    // ����OpenGL����3D�ռ��й����ģ���������Ⱦ����һ��2D�����Σ����ǽ��������z��������Ϊ0.0�������ӵĻ�������ÿһ������(Depth����ע2)����һ���ģ��Ӷ�ʹ������ȥ����2D�ġ�
    // ͨ����ȿ������Ϊz���꣬������һ�������ڿռ��к���ľ��룬�������Զ�Ϳ��ܱ���������ڵ�����Ϳ��������ˣ����ᱻ�������Խ�ʡ��Դ��
    float vertices[] = {
        // λ��              // ��ɫ
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader ourShader("ShaderSource/10-VertexShader.vs", "ShaderSource/10-GeometryShader.fs");

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
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

        ourShader.use();
        
        // һ�����������Ƕ����������ú�Ӧʹ�õ�VBO�Ķ����������һ�㵱�������ƶ������ʱ��������Ҫ����/�������е�VAO���ͱ����VBO������ָ��)��Ȼ�󴢴����ǹ�����ʹ�á������Ǵ�����������ʱ����ó���Ӧ��VAO��������������������ٽ��VAO��
        glBindVertexArray(VAO);
        /* ���������� */
       // Ҫ�����������Ҫ�����壬OpenGL�������ṩ��glDrawArrays��������ʹ�õ�ǰ�������ɫ����֮ǰ����Ķ����������ã���VBO�Ķ������ݣ�ͨ��VAO��Ӱ󶨣�������ͼԪ��
       // glDrawArrays������һ�����������Ǵ�����Ƶ�OpenGLͼԪ�����͡�
       // ����ϣ�����Ƶ���һ�������Σ����ﴫ��GL_TRIANGLES������
       // �ڶ�������ָ���˶����������ʼ����������������0��
       // ���һ������ָ�����Ǵ�����ƶ��ٸ����㣬������3������ֻ�����ǵ���������Ⱦһ�������Σ���ֻ��3�����㳤����
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        glfwSwapBuffers(window);
        // glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    /* �����ͷ���Դ */
    // ����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ�����ǿ�����main������������glfwTerminate��������ɡ�
    glfwTerminate();
    return 0;
}