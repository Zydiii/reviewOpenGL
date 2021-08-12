#pragma once

#include "setting.h"

const char* vertexShaderSource3 = "#version 460 core\n" // OpenGL 3.3�Լ��͸��߰汾�У�GLSL�汾�ź�OpenGL�İ汾��ƥ��ģ�����˵GLSL 420�汾��Ӧ��OpenGL 4.2��������ͬ����ȷ��ʾ���ǻ�ʹ�ú���ģʽ��
"layout (location = 0) in vec3 aPos;\n" // ʹ��in�ؼ��֣��ڶ�����ɫ�����������е����붥������(Input Vertex Attribute)������ͬ��Ҳͨ��layout (location = 0)�趨�����������λ��ֵ(Location)
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // Ϊ�����ö�����ɫ������������Ǳ����λ�����ݸ�ֵ��Ԥ�����gl_Position����������Ļ����vec4���͵ġ���main������������ǽ�gl_Position���õ�ֵ���Ϊ�ö�����ɫ���������
"}\0";

const char* fragmentShaderSource3 = "#version 460 core\n"
"out vec4 FragColor;\n" // Ƭ����ɫ��ֻ��Ҫһ��������������������һ��4��������������ʾ�������յ������ɫ������Ӧ���Լ����������������������������ʹ��out�ؼ��֣�������������ΪFragColor��
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int drawTwoTriangle1()
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

    /* ����������ɫ������ */
    // Ϊ���ܹ���OpenGLʹ���������Ǳ���������ʱ��̬��������Դ����
    // ����Ҫ�����Ǵ���һ����ɫ������ע�⻹����ID�����õġ�
    // �������Ǵ������������ɫ��Ϊunsigned int��Ȼ����glCreateShader���������ɫ��
    // ���ǰ���Ҫ��������ɫ�������Բ�����ʽ�ṩ��glCreateShader�������������ڴ���һ��������ɫ�������ݵĲ�����GL_VERTEX_SHADER��
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    /* ���붥����ɫ�� */
    // ���ǰ������ɫ��Դ�븽�ӵ���ɫ��������
    // glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
    glShaderSource(vertexShader, 1, &vertexShaderSource3, NULL);
    glCompileShader(vertexShader);

    /* ��ȡ�����Ƿ�ɹ���Ϣ */
    // �������Ƕ���һ�����ͱ�������ʾ�Ƿ�ɹ����룬��������һ�����������Ϣ������еĻ�����������Ȼ��������glGetShaderiv����Ƿ����ɹ����������ʧ�ܣ����ǻ���glGetShaderInfoLog��ȡ������Ϣ��Ȼ���ӡ����
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* ����Ƭ����ɫ�� */
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource3, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* ������ɫ�� */
    // glCreateProgram��������һ�����򣬲������´�����������ID���á�
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // ����������Ҫ��֮ǰ�������ɫ�����ӵ���������ϣ�Ȼ����glLinkProgram��������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    /* ����Ƿ����ӳɹ� */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // �ڰ���ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* ���嶥�� */
    // ��������ϣ����Ⱦһ�������Σ�����һ��Ҫָ���������㣬ÿ�����㶼��һ��3Dλ�á����ǻὫ�����Ա�׼���豸�������ʽ��OpenGL�Ŀɼ����򣩶���Ϊһ��float���顣
    // ����OpenGL����3D�ռ��й����ģ���������Ⱦ����һ��2D�����Σ����ǽ��������z��������Ϊ0.0�������ӵĻ�������ÿһ������(Depth����ע2)����һ���ģ��Ӷ�ʹ������ȥ����2D�ġ�
    // ͨ����ȿ������Ϊz���꣬������һ�������ڿռ��к���ľ��룬�������Զ�Ϳ��ܱ���������ڵ�����Ϳ��������ˣ����ᱻ�������Խ�ʡ��Դ��
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

    /* ��������������� */
    // �����������(Vertex Array Object, VAO)�����񶥵㻺������������󶨣��κ����Ķ������Ե��ö��ᴢ�������VAO�С�
    // �����ĺô����ǣ������ö�������ָ��ʱ����ֻ��Ҫ����Щ����ִ��һ�Σ�֮���ٻ��������ʱ��ֻ��Ҫ����Ӧ��VAO�����ˡ�
    // ��ʹ�ڲ�ͬ�������ݺ���������֮���л���÷ǳ��򵥣�ֻ��Ҫ�󶨲�ͬ��VAO�����ˡ�
    /* ���嶥�㻺����� */
    // ���㻺�������������OpenGL�̳��е�һ�����ֵ�OpenGL���󡣾���OpenGL�е���������һ�������������һ����һ�޶���ID���������ǿ���ʹ��glGenBuffers������һ������ID����һ��VBO����
    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    /* �󶨶���������� */
    // Ҫ��ʹ��VAO��Ҫ����ֻ��ʹ��glBindVertexArray��VAO���Ӱ�֮��������Ӧ�ð󶨺����ö�Ӧ��VBO������ָ�룬֮����VAO��֮��ʹ�á������Ǵ������һ�������ʱ������ֻҪ�ڻ�������ǰ�򵥵ذ�VAO�󶨵�ϣ��ʹ�õ��趨�Ͼ����ˡ�
    glBindVertexArray(VAOs[0]);

    /* �󶨶��㻺����� */
    // OpenGL�кܶ໺��������ͣ����㻺�����Ļ���������GL_ARRAY_BUFFER��
    // OpenGL��������ͬʱ�󶨶�����壬ֻҪ�����ǲ�ͬ�Ļ������͡�
    // ���ǿ���ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // ����ʹ�õ��κΣ���GL_ARRAY_BUFFERĿ���ϵģ�������ö����������õ�ǰ�󶨵Ļ���(VBO)��
    // Ȼ�����ǿ��Ե���glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
    // glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ�����
    // ���ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ�
    // �ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�
    // ����������������ϣ�����͵�ʵ�����ݡ�
    // ���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�
    // ���������Ѿ��Ѷ������ݴ������Կ����ڴ��У���VBO������㻺��������
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    /* ������ν��� */
    // ʹ��glVertexAttribPointer��������OpenGL����ν�����������
    // ��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��
    // �ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
    // ����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec*�����ɸ�����ֵ��ɵ�)
    // �¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������-1����1֮�䡣���ǰ�������ΪGL_FALSE��
    // �����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮�����ǰѲ�������Ϊ3 * sizeof(float)��Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ��
    // ���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // ÿ���������Դ�һ��VBO������ڴ��л���������ݣ��������Ǵ��ĸ�VBO�������п����ж��VBO����ȡ����ͨ���ڵ���glVertexAttribPointerʱ�󶨵�GL_ARRAY_BUFFER��VBO�����ġ������ڵ���glVertexAttribPointer֮ǰ�󶨵�����ǰ�����VBO���󣬶�������0���ڻ����ӵ����Ķ������ݡ�
    // ��������Ӧ��ʹ��glEnableVertexAttribArray���Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õ�
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

        /* ������ɫ������ */
        // �õ��Ľ������һ������������ǿ��Ե���glUseProgram�������øմ����ĳ��������Ϊ���Ĳ������Լ�������������
        // ��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������
        // �����Ѿ������붥�����ݷ��͸���GPU����ָʾ��GPU����ڶ����Ƭ����ɫ���д�����
        glUseProgram(shaderProgram);
        // һ�����������Ƕ����������ú�Ӧʹ�õ�VBO�Ķ����������һ�㵱�������ƶ������ʱ��������Ҫ����/�������е�VAO���ͱ����VBO������ָ��)��Ȼ�󴢴����ǹ�����ʹ�á������Ǵ�����������ʱ����ó���Ӧ��VAO��������������������ٽ��VAO��
        glBindVertexArray(VAOs[0]);
        /* ���������� */
       // Ҫ�����������Ҫ�����壬OpenGL�������ṩ��glDrawArrays��������ʹ�õ�ǰ�������ɫ����֮ǰ����Ķ����������ã���VBO�Ķ������ݣ�ͨ��VAO��Ӱ󶨣�������ͼԪ��
       // glDrawArrays������һ�����������Ǵ�����Ƶ�OpenGLͼԪ�����͡�
       // ����ϣ�����Ƶ���һ�������Σ����ﴫ��GL_TRIANGLES������
       // �ڶ�������ָ���˶����������ʼ����������������0��
       // ���һ������ָ�����Ǵ�����ƶ��ٸ����㣬������3������ֻ�����ǵ���������Ⱦһ�������Σ���ֻ��3�����㳤����
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        glfwSwapBuffers(window);
        // glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
        glfwPollEvents();
    }

    /* �����ͷ���Դ */
    // ����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ�����ǿ�����main������������glfwTerminate��������ɡ�
    glfwTerminate();
    return 0;
}