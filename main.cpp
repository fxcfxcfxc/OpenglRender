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

//=========================================模型数据信息=================================
//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
//




unsigned int indices[] =
{
    0,1,2,//第一个三角形
    2,3,0 //第二个三角形

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

    //实例化窗口对象
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
    //设置渲染窗口的大小
    glViewport(0,0,1600,1200);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    //启动zbuffer
    glEnable(GL_DEPTH_TEST);


    //创建一个shader对象  传入 路径
    Shader* testshader = new Shader("vertexSource.txt", "fragmentSource.txt");



    //----------------------------------生成VAO对象，VAO就像是属性列表
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //----------------------------------------生成VBO对象
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    //第一个参数代表绑定的数据类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将模型pos属性复制到vbo中   obj array ->  VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    //-----------------------------------------创建EBO对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices , GL_STATIC_DRAW);




    //-----------------VBO -》  VAO--------------------------------------
    // 将正确的属性 放入到 VAO对应的插槽数组中
    //链接顶点pos属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //链接顶点vertexcolor属性
  /*  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/


    //链接顶点  UV属性
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
    //注意顺序
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


    ////----------------------------------Render Loop 渲染循环-------------------------  
    while (!glfwWindowShouldClose(window))
    {   
        //trans = glm:: translate(trans,glm:: vec3(-0.01f, 0, 0));

        //获取键盘输入
        processInput(window);

        //设置用来 清空屏幕的 颜色
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

        //清空屏幕的color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        //绑定上下文纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, TexBufferB);



        //绑上下文VAO 
        glBindVertexArray(VAO);

        //绑定EBO到   GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);


        for (int index = 0; index<10; index++)
        {
            glm::mat4 modelMat2;
            modelMat2 = glm::translate( modelMat2,  cubePositions[index] );
            float angle = 20.0f * index;
            modelMat2 = glm:: rotate(modelMat2, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //当我们渲染一个物体时要使用的着色器程序
            testshader->use();

            glUniform1i(glGetUniformLocation(testshader->ID, "ourTexture"), 0);
            glUniform1i(glGetUniformLocation(testshader->ID, "ourFace"), 1);
            //glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "transform"), 1, GL_FALSE, glm:: value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));


            //第一个参数绘制模式，第二个参数绘制定点数，第三个参数是索引类型，第四个参数 EBO中的偏移量
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //从数组缓存中的哪一位开始绘制，一般为0.,数组中顶点的数量.
            glDrawArrays(GL_TRIANGLES, 0, 36);


        }

        
        //
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    //删除释放资源的方法，清理所有资源 并正确地退出所有应用
    glfwTerminate();
    return 0;






}