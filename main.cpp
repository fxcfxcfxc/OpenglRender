#include    <iostream>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"

//=========================================ģ��������Ϣ=================================
//float vertices[] = {
//    //     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};
//




unsigned int indices[] =
{
    0,1,2,//��һ��������
    2,3,0 //�ڶ���������

};





float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float lastX;
float lastY;
bool firstMouse = true;



//====================================================================================

void processInput(GLFWwindow*  window) 
{
    if ( glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS )
    {

        glfwSetWindowShouldClose(window, true);

    }

}


void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse == true)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;

    }

    float deltaX, deltaY; 
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;

    printf("%f \n", xPos);
}




int main() 
{   
    
     
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //ʵ�������ڶ���
    GLFWwindow* window = glfwCreateWindow(1600, 1200, "My OpenGl Game", NULL, NULL);
    if (window == NULL) 
    {
       printf("Open window failed");
       glfwTerminate();
       return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    //
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Init GLEW failed");
        glfwTerminate();

        return -1;

    }

    
    ////---------------------------- buffer------------------------
    //������Ⱦ���ڵĴ�С
    glViewport(0,0,1600,1200);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    //����zbuffer
    glEnable(GL_DEPTH_TEST);


    //����һ��shader����  ���� ·��
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



    //-----------------------------------------����EBO����
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices , GL_STATIC_DRAW);




    //-----------------VBO -��  VAO--------------------------------------
    // ����ȷ������ ���뵽 VAO��Ӧ�Ĳ��������
    //���Ӷ���pos����
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //���Ӷ���vertexcolor����
  /*  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/


    //���Ӷ���  UV����
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);




    //-----------------------------------Texturebuffer object
    unsigned int TexBufferA;
    glGenTextures(1, &TexBufferA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TexBufferA);

    int width, height, nrChannel;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else
    {
        printf("load image failed");
    }

    stbi_image_free(data);


    //
    unsigned int TexBufferB;
    glGenTextures(1, &TexBufferB);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,TexBufferB);
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed." << std::endl;

    }

    stbi_image_free(data2);

    //-----------------------------------------
    glm::mat4 trans;
    //ע��˳��
    //trans = glm:: translate(trans, glm:: vec3(-1.0f, 0, 0));
    //trans = glm:: rotate(trans,glm:: radians(.0f), glm:: vec3(0.0, 0.0, 1.0f));
    //trans = glm:: scale(trans, glm:: vec3(0.8f, 0.8f, 0.8f));

    //Camera myCamera(glm::vec3(0, 0, 8.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
    Camera myCamera( glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f,.0) );


    //model->world
    glm::mat4 modelMat;
    modelMat = glm:: rotate(modelMat, glm:: radians(-55.0f), glm:: vec3(1.0f, 0 , 0));

    //world->view
    glm::mat4 viewMat;
    //viewMat = glm:: translate(viewMat, glm:: vec3( 0, 0, -3.0f ));
    viewMat = myCamera.GetViewMatrix();

    //view-> clipspace
    glm:: mat4 projMat;  
    projMat = glm:: perspective(glm::radians(45.0f), 1600.0f / 1200.0f,  0.1f, 100.0f);


    ////----------------------------------Render Loop ��Ⱦѭ��-------------------------  
    while (!glfwWindowShouldClose(window))
    {   
        //trans = glm:: translate(trans,glm:: vec3(-0.01f, 0, 0));

        //��ȡ��������
        processInput(window);

        //�������� �����Ļ�� ��ɫ
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

        //�����Ļ��color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        //������������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, TexBufferB);



        //��������VAO 
        glBindVertexArray(VAO);

        //��EBO��   GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);


        for (int index = 0; index<10; index++)
        {
            glm::mat4 modelMat2;
            modelMat2 = glm::translate( modelMat2,  cubePositions[index] );
            float angle = 20.0f * index;
            modelMat2 = glm:: rotate(modelMat2, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //��������Ⱦһ������ʱҪʹ�õ���ɫ������
            testshader->use();

            glUniform1i(glGetUniformLocation(testshader->ID, "ourTexture"), 0);
            glUniform1i(glGetUniformLocation(testshader->ID, "ourFace"), 1);
            //glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "transform"), 1, GL_FALSE, glm:: value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));


            //��һ����������ģʽ���ڶ����������ƶ��������������������������ͣ����ĸ����� EBO�е�ƫ����
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //�����黺���е���һλ��ʼ���ƣ�һ��Ϊ0.,�����ж��������.
            glDrawArrays(GL_TRIANGLES, 0, 36);


        }

        
        //
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    //ɾ���ͷ���Դ�ķ���������������Դ ����ȷ���˳�����Ӧ��
    glfwTerminate();
    return 0;






}