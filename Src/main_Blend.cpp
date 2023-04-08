#pragma once
#include <iostream>
#include <direct.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

#include <glm.hpp>
#include <GLFW/glfw3native.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "DrawGizmo.h"
#include "FModel.h"

#include "LightDirectional.h"
#include "LightPoint.h"
#include "Material.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "Texture.h"


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

float transparentVertices[]= {
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};
float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};


#pragma endregion


#pragma region  Create Camera

Camera myCamera(glm::vec3(0, 0.5f, 5.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, .0));
#pragma endregion

//update keyboard
#pragma region Camera  Update Declare
float lastX;
float lastY;
bool firstMouse = true;

std::string GetFilePath()
{
    char* path = nullptr;
    path = _getcwd(nullptr,1);
    puts(path);

    std::string filePath(path);
    return filePath;

    delete path;
    path = nullptr;
}


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


int main(int argc, char* argv[]) 
{
    
    std::string exePath = argv[0];

// create window
#pragma region OpenWindow   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int srcWidth =1600;
    const int srcHeight =1200;
    GLFWwindow* window = glfwCreateWindow(srcWidth, srcHeight, "My OpenGl Game", NULL, NULL);
    if (window == NULL) 
    {
       printf("Open window failed");
       glfwTerminate();
       return -1;
    }
    glfwMakeContextCurrent(window);

  
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glViewport(0,0,1600,1200);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    

    glEnable(GL_DEPTH_TEST);

#pragma endregion
    
// create shader  
#pragma region Init Shader Program

    Shader* lambertShader = new Shader("Shader/Lambert.vert", "Shader/Lambert.frag");
    Shader* Unitshader = new Shader("Shader/Unit.vert", "Shader/Unit.frag");
    Shader* lightShader = new Shader("Shader/LightvertexSource.vert", "Shader/LightfragmentSource.frag");
    Shader* postShader = new Shader("Shader/ScenePost.vert", "Shader/ScenePost.frag");

#pragma endregion  


// init Matrix
#pragma region Init and Load Models to VAO VBO
    std::string projectPath = GetFilePath() + "\\model\\nanosuit.obj";
    Model model( projectPath);
 #pragma endregion
    
// create camera
#pragma region MVP vertex
    //world->view
    glm::mat4 viewMat; 
    //view-> clipspace
    glm:: mat4 projMat;  
    projMat = glm:: perspective(glm::radians(45.0f), 1600.0f / 1200.0f,  0.1f, 100.0f);
#pragma endregion

// creat texture
#pragma region create Texture
    FTexture* windowTexture =new FTexture("E:\\Project\\Opengl\\resource\\window.png");
    FTexture* floorTexture  =new FTexture("E:\\Project\\Opengl\\resource\\Stone_floor_albedo.png");
    FTexture* carTexture  =new FTexture("E:\\Project\\Opengl\\resource\\CarDiffuse.png");
#pragma endregion

// create Light
#pragma region Init Light


    LightDirectional * lightD = new LightDirectional(glm::vec3(0.0f, 4.0f ,0.0f),
                                                     glm::vec3(glm::radians(45.0f),0,0),
                                                     glm::vec3(1.0f, 1.0f, 1.0f));


    LightPoint* lightP = new LightPoint(glm::vec3(-3.0f, 5.0f, 6.0f),
                                        glm::vec3(glm::radians(90.0f), 0, 0), 
                                        glm::vec3(3.0f, 1.0f, 0.0f));

    LightSpot* lightS = new LightSpot(glm::vec3(0.0f, 4.0f, 0.0f),
                                      glm::vec3(glm::radians(90.0f), 0, 0),
                                      glm::vec3(1.0f, 1.0f, 2.0f));

#pragma endregion
    
// imgui data
#pragma region create transform
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool show_another_window = false;
    glm::vec3 floorTranlate = glm::vec3(0.0f, -10.0f, 0.0f);
    glm::vec3 carTranlate = glm::vec3(0.0f, -10.0f, 0.0f);
    float angle = 0;
    glm::vec3 abColor = glm::vec3(0.2f, 0.1f, 0.4f);
    float lightangle = 0;
    glm::vec3 pointPosition = glm::vec3(lightP->position);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

#pragma endregion
 
// create material
#pragma region create material
    FMaterial* windowMaterial = new FMaterial(lambertShader,windowTexture->Id,100);
    FMaterial* floorMaterial = new FMaterial(lambertShader,floorTexture->Id,100);
    FMaterial* carMaterial = new FMaterial(lambertShader,carTexture->Id,150);

#pragma endregion

//加载模型，配置模型材质贴图
#pragma region create model
//加载窗户模型
    std::string windowPath = GetFilePath() + "\\resource\\window.obj";
    FModel windowModel(windowPath,windowMaterial);
    
//加载地面模型
    std::string floorPath = GetFilePath() + "\\resource\\floor.obj";
    FModel floorModel(floorPath,floorMaterial);

//加载汽车模型
    std::string carPath = GetFilePath() + "\\resource\\car.obj";
    FModel carModel(carPath,carMaterial);

#pragma endregion


//后处理
#pragma region postProcessing
    //PostProcesing
    // screen quad VAO
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

    
    //----------------------------------------离屏framebuffer

    
    unsigned int framebuffer;
    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);

    unsigned int textureColorbuffer;
    glGenTextures(1,&textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D,textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, srcWidth, srcHeight,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);    
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,textureColorbuffer,0);

    unsigned int rbo;
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, srcWidth,srcHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) !=GL_FRAMEBUFFER_COMPLETE)
        std::cout<< "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" <<std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER,0);

#pragma endregion

    
// create render loop
#pragma region create render loop
  
    while (!glfwWindowShouldClose(window))
    {   
        processInput(window);
        //----------------------------------------离屏framebuffer
        //glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glEnable(GL_DEPTH_TEST);
        //-------------------------------------------------------------
        
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();
        

        //-----------------------------------------------------------------逻辑更新-----
        viewMat = myCamera.GetViewMatrix();
        lightP->position = pointPosition;
        lightP->color = glm::vec3(clear_color.x,clear_color.y,clear_color.z);
        lambertShader->use();
        lambertShader->SetRenderingData(viewMat, projMat, abColor, lightD, lightP, lightS, myCamera);
        floorModel.UpdateTransform(angle,floorTranlate);
        carModel.UpdateTransform(angle,carTranlate);
        
        //-----------------------------------------------opquape---- 
        glDisable(GL_BLEND);
        floorModel.Draw();
        carModel.Draw();
        
        //-----------------------------------------------transparent---
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        windowModel.Draw();

        
        //----------------------------------------------Postprocesing-------------------
        // glBindFramebuffer(GL_FRAMEBUFFER,0);
        // glDisable(GL_DEPTH_TEST);
        // glClearColor(1.0f,1.0f,1.0f,1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        //
        // postShader->use();
        // glBindVertexArray(quadVAO);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D,textureColorbuffer);
        // postShader->SetUniform1i("screenTexture",0);
        // glDrawArrays(GL_TRIANGLES,0,6);
        
        
        //-----------------------------------------------Gizmo------
        DrawGizmo::mMatrix = glm::scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        DrawGizmo::mMatrix = glm::rotate(DrawGizmo::mMatrix, glm::radians(lightangle), glm::vec3(0.0f, 1.0f, 0.0f));
        DrawGizmo::mMatrix = glm::translate(DrawGizmo::mMatrix, pointPosition);
        DrawGizmo::SetGizmoShader(lightShader,DrawGizmo::mMatrix,viewMat,projMat);
        unsigned int VAO,VBO;
        DrawGizmo::DrawBox(VAO,VBO);
        
 
        
        //----------------------------imgui 绘制--------------------------------
        //imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");
        
            ImGui::SliderFloat3("floorTranlate", &floorTranlate.x, -30.0f, 30.0f);
            ImGui::SliderFloat3("carTranlate", &carTranlate.x, -30.0f, 30.0f);
       
            ImGui::SliderFloat3("pointPosition", &pointPosition.x, -30.0f, 30.0f);
            
   
            ImGui::SliderFloat("angle", &angle, 0.0f, 360.0f);
            ImGui::SliderFloat("lightangle", &lightangle, 0.0f, 360.0f);
            
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
#pragma endregion
    
    // release
    glfwTerminate();
    return 0;


}