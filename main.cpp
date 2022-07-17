#include    <iostream>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

//=========================================模型顶点信息=================================
float vertices[] =
{
    0.5f,0.5f,0.0f,   1.0f, 0.0f, 0.0f,//0
    0.5f,-0.5f,0.0f,  0.0f, 1.0f, 0.0f,//1
    -0.5f,-0.5f,0.0f, 0.0f, 0.0f, 1.0f,//2
    - 0.5f,0.5f,0.0f, 0.3f, 0.2f, 0.1f//3

};

unsigned int indices[] =
{
    0,1,3,//第一个三角形
    1,2,3 //第二个三角形

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

    //实例化窗口对象
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

    
    ////----------------------------数据copy buffer------------------------
    //设置渲染窗口的大小
    glViewport(0,0,800,600);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    

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



    //---------------------------------------------创建EBO对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices , GL_STATIC_DRAW);




    //-----------------VBO -》  VAO--------------------------------------
    // 将正确的属性 放入到 VAO对应的插槽数组中
    //链接顶点pos属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //链接顶点vertexcolor属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)( 3*sizeof(float) ));
    glEnableVertexAttribArray(1);



    ////----------------------------------Render Loop 渲染循环-------------------------  
    while (!glfwWindowShouldClose(window))
    {
        //获取键盘输入
        processInput(window);

        //设置清空屏幕的颜色
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

        //清空屏幕的color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //绑定上下文VAO
        glBindVertexArray(VAO);

        //绑定EBO到   GL_ELEMENT_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

        //当我们渲染一个物体时要使用的着色器程序
        testshader->use();
        
        //第一个参数绘制模式，第二个参数绘制定点数，第三个参数是索引类型，第四个参数 EBO中的偏移量
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        //
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    //删除释放资源的方法，清理所有资源 并正确地退出所有应用
    glfwTerminate();
    return 0;






}