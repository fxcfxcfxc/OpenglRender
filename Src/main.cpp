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
#include "LightDirectional.h"
#include "LightPoint.h"
#include "Material.h"
#include "LightSpot.h"
#include "Mesh.h"



//模型数据
#pragma region Model Data
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
#pragma endregion




//创建相机
#pragma region  Create Camera

Camera myCamera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, .0));
#pragma endregion



//更新键盘输入 更新相机位置方向
#pragma region Camera  Update Declare
float lastX;
float lastY;
bool firstMouse = true;


void processInput(GLFWwindow*  window) 
{
    if ( glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS )
    {

        glfwSetWindowShouldClose(window, true);

    }


    //按下WS
    if ( glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS )
    {
        myCamera.speedZ = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        myCamera.speedZ = -1.0f;
    }
    else
    {
        myCamera.speedZ = 0;
    }


    //按下AD
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        myCamera.speedX = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        myCamera.speedX = -1.0f;
    }
    else
    {
        myCamera.speedX = 0;
    }

    //按下QE
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        myCamera.speedY = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        myCamera.speedY = -1.0f;
    }
    else
    {
        myCamera.speedY = 0;
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

    myCamera.ProcessMouseMovement(deltaX, deltaY);

   // printf("%f \n", xPos);
}
#pragma endregion


//创建灯光
#pragma region Init Light

//实例化平行光
LightDirectional * lightD = new LightDirectional(glm::vec3(0.0f, 4.0f ,0.0f),
                                                 glm::vec3(glm::radians(45.0f),0,0),
                                                 glm::vec3(1.0f, 1.0f, 1.0f));

//实例化点光
LightPoint* lightP = new LightPoint(glm::vec3(0.2f, -2.0f, 0.0f),
                                    glm::vec3(glm::radians(90.0f), 0, 0), 
                                    glm::vec3(3.0f, 1.0f, 0.0f));

//实例化聚光灯
LightSpot* lightS = new LightSpot(glm::vec3(0.0f, 4.0f, 0.0f),
                                  glm::vec3(glm::radians(90.0f), 0, 0),
                                  glm::vec3(1.0f, 1.0f, 2.0f));

#pragma endregion



unsigned int LoadImageToGPU(const char* FileName,GLint  InternalFormat,GLenum Format, int TextureSlot)
{
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0 * TextureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);

    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(FileName, &width, &height, &nrChannel, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, Format, GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("load image failed");

    }
    stbi_image_free(data);
    return TexBuffer;

}

int main() 
{   
 
//创建窗口
#pragma region OpenWindow   
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

#pragma endregion



//创建shader对象  负责读取顶点和片元着色器文件，并创建shader程序
#pragma region Init Shader Program
    //创建一个shader对象  传入路径
    Shader* testshader = new Shader("Shader/vertexSource.vert", "Shader/fragmentSource.frag");
#pragma endregion  



//创建Material对象 读取图片，初始化传入shader的参数
#pragma region Init Material  Data
//--------------------------Creat Material
Material* myMaterial = new Material(testshader,
                                        LoadImageToGPU("resource/container2.png", GL_RGBA, GL_RGBA, Shader::Diffuse),
                                        LoadImageToGPU("resource/container2specular.png", GL_RGBA, GL_RGBA, Shader::Specular),
                                        glm::vec3(1.0f, 1.0f, 1.0f),
                                        64.0f);
#pragma endregion 





//创建Mesh对象 负责读取模型数据，并创建VAO,VAO， 纹理激活 传入shader
#pragma region Init and Load Models to VAO VBO
    Mesh cube(vertices);
        
    //----------------------------------生成VAO对象，VAO就像是属性列表
    //unsigned int VAO;
    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);

    //----------------------------------------生成VBO对象
    //unsigned int VBO;
    //glGenBuffers(1,&VBO);
    //第一个参数代表绑定的数据类型
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将模型数据复制到vbo中   obj data ->  VBO buffer
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    //-----------------------------------------创建EBO对象
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices , GL_STATIC_DRAW);




    //-----------------VBO -》  VAO--------------------------------------
    // 将正确的属性 放入到 VAO对应的插槽中 
    //链接顶点pos属性
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   // glEnableVertexAttribArray(0);

    //链接顶点  UV属性
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

    //normal
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(3);

    //链接顶点vertexcolor属性
/*  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);*/


#pragma endregion
 


//模型变化的矩阵数据
#pragma region MVP vertex

    //-----------------------------------------MVP  Matrices
    glm::mat4 trans;
    //model->world
    glm::mat4 modelMat;
    //world->view
    glm::mat4 viewMat; 
    //view-> clipspace
    glm:: mat4 projMat;  
    projMat = glm:: perspective(glm::radians(45.0f), 1600.0f / 1200.0f,  0.1f, 100.0f);


#pragma endregion





    ////----------------------------------Render Loop 渲染循环-------------------------  
    while (!glfwWindowShouldClose(window))
    {   
 

        //获取键盘输入
        processInput(window);

        //设置用来 清空屏幕的 颜色
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        //清空屏幕的color buffer ,DEPTH_BUFFER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        //绑定EBO到   GL_ELEMENT_ARRAY_BUFFER
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);


        viewMat = myCamera.GetViewMatrix();

        for (int index = 0; index<2; index++)
        {
            // Set model Martix
            modelMat = glm::translate( glm:: mat4(1.0f), cubePositions[index]);
            float angle = 20.0f * index;
            modelMat= glm:: rotate(modelMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));



            //Set Material -> ShaderProgram
            testshader->use();

            //Set Material  -> Texture
            //glActiveTexture(GL_TEXTURE0);
           //glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
           // glActiveTexture(GL_TEXTURE0 +1);
           // glBindTexture(GL_TEXTURE_2D, myMaterial->specular);


            //-----------------------------------设置材质数据
            //矩阵数据传入
            //glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "transform"), 1, GL_FALSE, glm:: value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(testshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));



            //光源数据传入 shader

            //环境光
            glUniform3f(glGetUniformLocation(testshader->ID, "ambientColor"), 0.1f, 0.1f, 0.4f);
            
            //平行光数据
            glUniform3f(glGetUniformLocation(testshader->ID, "lightd.pos"), lightD->position.x, lightD->position.y, lightD->position.z);
            glUniform3f(glGetUniformLocation(testshader->ID, "lightd.direction"), lightD->direction.x, lightD->direction.y, lightD->direction.z);
            glUniform3f(glGetUniformLocation(testshader->ID, "lightd.color"), lightD->color.x, lightD->color.y, lightD->color.z);

            //点光源数据
            glUniform3f(glGetUniformLocation(testshader->ID, "lightP.pos"), lightP->position.x, lightP->position.y, lightP->position.z );
            glUniform3f(glGetUniformLocation(testshader->ID, "lightP.color"), lightP->color.x, lightP->color.y, lightP->color.z);
            glUniform1f(glGetUniformLocation(testshader->ID, "lightP.constant"), lightP->constant);
            glUniform1f(glGetUniformLocation(testshader->ID, "lightP.linear"), lightP->linear);
            glUniform1f(glGetUniformLocation(testshader->ID, "lightP.quadratic"), lightP->quadratic);


            //聚光灯
            glUniform3f(glGetUniformLocation(testshader->ID, "lightS.pos"), lightS->position.x, lightS->position.y, lightS->position.z );
            glUniform3f(glGetUniformLocation(testshader->ID, "lightS.color"), lightS->color.x, lightS->color.y, lightS->color.z );
            glUniform3f(glGetUniformLocation(testshader->ID, "lightS.direction"), lightS->direction.x, lightS->direction.y, lightS->direction.z );
            glUniform1f(glGetUniformLocation(testshader->ID, "lightS.cosPhyInner"), lightS->cosPhyInner );
            glUniform1f(glGetUniformLocation(testshader->ID, "lightS.cosPhyOut"), lightS->cosPhyOut );


            //相机数据传入
            glUniform3f(glGetUniformLocation(testshader->ID, "cameraPos"), myCamera.Position.x, myCamera.Position.y, myCamera.Position.z);
            
            //材质纹理数据传入
            myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
            //myMaterial->shader->SetUniform1i("material.diffuse", Shader::Diffuse);
            //myMaterial->shader->SetUniform1i("material.specular", Shader::Specular);
            myMaterial->shader->SetUniform1f("material.shininess",myMaterial->shininess);
   


            //Set Model  绑上下文VAO 
           //glBindVertexArray(VAO);


            //DrawCall
            //从数组缓存中的哪一位开始绘制，一般为0.,数组中顶点的数量.
            //glDrawArrays(GL_TRIANGLES, 0, 36);


            //第一个参数绘制模式，第二个参数绘制定点数，第三个参数是索引类型，第四个参数 EBO中的偏移量
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            cube.Draw(myMaterial->shader);


        }

        
        //Clean up, prepare for next render loop
        glfwSwapBuffers(window);
        glfwPollEvents();
        myCamera.UpdateCameraPos();

    }

    //删除释放资源的方法，清理所有资源 并正确地退出所有应用
    glfwTerminate();
    return 0;






}