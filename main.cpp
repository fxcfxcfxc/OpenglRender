#include    <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

//----------------------------------------ģ�Ͷ�����Ϣ-------------------
float vertices[] =
{
    0.5f,0.5f,0.0f,   1.0f, 0.0f, 0.0f,//0
    0.5f,-0.5f,0.0f,  0.0f, 1.0f, 0.0f,//1
    -0.5f,-0.5f,0.0f, 0.0f, 0.0f, 1.0f,//2
    - 0.5f,0.5f,0.0f, 0.3f, 0.2f, 0.1f//3

};

unsigned int indices[] =
{
    0,1,3,//��һ��������
    1,2,3 //�ڶ���������

};

//------------------------------------------------------------------------
//��VAO �����б� �������� �� vertexshader  ���������Ҫ������
const char* vertexShaderSource =
"#version 330 core                                       \n    "
"layout(location = 0 ) in vec3 aPos;                      \n   "
"layout(location = 1 ) in vec3 aColor;                    \n   "
"out vec4 ourColor;                                       \n   "
"void main(){\n                                               "
"        gl_Position = vec4(aPos.x, aPos.y, aPos.z,  1.0) ; \n  "
"        ourColor = vec4( aColor, 1.0 ); } \n";



//�� vertexshader ��������  �����ƬԪ����
const char* fragmentShaderSource =
"#version 330 core                                       \n   "
"in vec4 ourColor;                                       \n   "
"out vec4 FragColor;                                     \n   "
"void main(){\n                                               "
"        FragColor = ourColor;}      \n  ";



//-----------------------------------------------------------------------------

void processInput(GLFWwindow*  window) 
{
    if ( glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS )
    {

        glfwSetWindowShouldClose(window, true);

    }

}


int main() 
{   
    Shader* sha = new Shader("vertexSource.txt","fragmentSource.txt");
     
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //ʵ�������ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGl Game", NULL, NULL);
    if (window == NULL) 
    {
       printf("Open window failed");
       glfwTerminate();
       return -1;
    }
    glfwMakeContextCurrent(window);


    //
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Init GLEW failed");
        glfwTerminate();

        return -1;

    }

    
    ////----------------------------����copy buffer------------------------
    //������Ⱦ���ڵĴ�С
    glViewport(0,0,800,600);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    //����VAO����VAO�����������б�
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //����VBO����
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    //��һ����������󶨵���������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //��ģ��pos���Ը��Ƶ�vbo��   obj array ->  VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    //����EBO����
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices , GL_STATIC_DRAW);



    ////---------------------------------��ɫ��--------------------------
    //vertex
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    //fragment
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    //shaderProgram
    unsigned  int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    //-----------------VBO -��  VAO------------------
    // ����ȷ������ ���뵽 VAO��Ӧ�Ĳ��������
    //���Ӷ���pos����
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //���Ӷ���vertexcolor����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)( 3*sizeof(float) ));
    glEnableVertexAttribArray(1);



    ////----------------------------------Render Loop ��Ⱦѭ��-------------------------  
    while (!glfwWindowShouldClose(window))
    {
        //��ȡ��������
        processInput(window);

        //���������Ļ����ɫ
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        //�����Ļ��color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //��������VAO
        glBindVertexArray(VAO);

        //��EBO��   GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

        //
        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "vColor");
        //glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation,0, greenValue,0, 1.0f);


        //��������Ⱦһ������ʱҪʹ�õ���ɫ������
        glUseProgram(shaderProgram);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //��һ����������ģʽ���ڶ����������ƶ��������������������������ͣ����ĸ����� EBO�е�ƫ����
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
        
        
        //
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    //ɾ���ͷ���Դ�ķ���������������Դ ����ȷ���˳�����Ӧ��
    glfwTerminate();
    return 0;






}