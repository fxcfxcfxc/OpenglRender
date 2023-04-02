#pragma once
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
#include "Model.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

//手动模型数据
#pragma region Model Data
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
#pragma endregion

//创建相机
#pragma region  Create Camera

Camera myCamera(glm::vec3(0, 0.5f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, .0));
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

unsigned int LoadImageToGPU(const char* FileName,GLint   InternalFormat,GLenum Format, int TextureSlot)
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

int main(int argc, char* argv[]) 
{   
    std::string exePath = argv[0];
    //std::cout << exePath.substr(0, exePath.find_last_of('\\')) +"\\model\\nanosuit.obj" << std::endl;



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

    //设置鼠标 光标运行后不显示
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //监听鼠标键盘事件，更新摄像机数据
    //glfwSetCursorPosCallback(window, mouse_callback);

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
    //创建一个Mesh 需要用到的shader
    Shader* testshader = new Shader("Shader/vertexSource.vert", "Shader/fragmentSource.frag");

    //绘制灯光辅助显示 shader
    Shader* lightShader = new Shader("Shader/LightvertexSource.vert", "Shader/LightfragmentSource.frag");
#pragma endregion  

//创建Material对象 读取图片，初始化传入shader的参数
#pragma region Init Material  Data
//--------------------------Creat Material
//Material* myMaterial = new Material(testshader,
//                                        LoadImageToGPU("Debug/model/body_dif.png", GL_RGBA, GL_RGBA, Shader::Diffuse),
//                                        LoadImageToGPU("resource/container2specular.png", GL_RGBA, GL_RGBA, Shader::Specular),
//                                        glm::vec3(1.0f, 1.0f, 1.0f),
//                                        64.0f);
#pragma endregion 

// 创建model
#pragma region Init and Load Models to VAO VBO
    Model model( "E:\\Project\\Opengl\\model\\Houtou.obj");
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

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //模型位移
    glm::vec3 t = glm::vec3(0.0f, -10.0f, 0.0f);


    //模型旋转
    float angle = 0;

    float lightangle = 0;

    //创建环境光颜色
    glm::vec3 abColor = glm::vec3(1.0f, 0.1f, 0.4f);

    //
    glm::vec3 pointPosition = glm::vec3(lightP->position);

    
    ////----------------------------------Render Loop 渲染循环 -------------------------  
    while (!glfwWindowShouldClose(window))
    {   
 

        //获取键盘输入
        processInput(window);

        //设置用来 清空屏幕的 颜色
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        //清空屏幕 模式为 color buffer ,DEPTH_BUFFER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();

        
        //---更新模型 变换矩阵M --
        //缩放
        modelMat = glm::scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        //旋转
        modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        //平移
        modelMat = glm::translate(modelMat, t);

        //---更新相机数据 V矩阵---
        viewMat = myCamera.GetViewMatrix();


        //---更新点光源数据---
        lightP->position = pointPosition;

        //绑定当前使用的shader着色
        testshader->use();

        //设置渲染所需的最新数据 传递给shader着色器 灯光数据（平行光，方向光，点光源，环境光，MVP矩阵，相机数据）
        testshader->SetRenderingData(modelMat, viewMat, projMat, abColor, lightD, lightP, lightS, myCamera);

        //调用绘制每一个mesh对象
        model.Draw(testshader);
        
        //绑定 灯光绘制的 shader着色
        lightShader->use();
        
        //设置 灯光绘制所需的数据并传递
        //---更新模型 变换矩阵M --
        //缩放
        modelMat = glm::scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        //旋转
        modelMat = glm::rotate(modelMat, glm::radians(lightangle), glm::vec3(0.0f, 1.0f, 0.0f));
        //平移
        modelMat = glm::translate(modelMat, pointPosition);

        lightShader->SetRenderingData(modelMat, viewMat, projMat,myCamera);

        //绘制辅助灯光控件，方便观察（用box标志）
        unsigned int VAO,VBO;
        Model::DrawLight(VAO,VBO);
   
	

        //imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");
            // 调节模型位置
            ImGui::SliderFloat3("t", &t.x, -30.0f, 30.0f);
            // 调节点光源位置
            ImGui::SliderFloat3("pointPosition", &pointPosition.x, -30.0f, 30.0f);
            
            // 调节模型旋转
            ImGui::SliderFloat("angle", &angle, 0.0f, 360.0f);
            
            ImGui::ColorEdit3("clear color", (float*)&clear_color); 

            ImGui::Checkbox("Demo Window", &show_demo_window);      
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                           
                counter++;

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }


        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        //Clean up, prepare for next render loop
        glfwSwapBuffers(window);
        glfwPollEvents();
        myCamera.UpdateCameraPos();

    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    //删除释放资源的方法，清理所有资源 并正确地退出所有应用
    glfwTerminate();
    return 0;






}