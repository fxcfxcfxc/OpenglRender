#include    <iostream>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

//=========================================ģ�Ͷ�����Ϣ=================================
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




//====================================================================================

void processInput(GLFWwindow*  window) 
{
    if ( glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS )
    {

        glfwSetWindowShouldClose(window, true);

    }

}


int main() 
{   
    
     
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
    

    Shader* testshader = new Shader("vertexSource.txt", "fragmentSource.txt");



    //----------------------------------����VAO����VAO�����������б�
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //----------------------------------------����VBO����
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    //��һ����������󶨵���������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //��ģ��pos���Ը��Ƶ�vbo��   obj array ->  VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    //---------------------------------------------����EBO����
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices , GL_STATIC_DRAW);




    //-----------------VBO -��  VAO--------------------------------------
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

        //��������Ⱦһ������ʱҪʹ�õ���ɫ������
        testshader->use();
        
        //��һ����������ģʽ���ڶ����������ƶ��������������������������ͣ����ĸ����� EBO�е�ƫ����
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        //
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    //ɾ���ͷ���Դ�ķ���������������Դ ����ȷ���˳�����Ӧ��
    glfwTerminate();
    return 0;






}