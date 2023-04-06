#pragma once
#include    <iostream>
#include <direct.h>

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
#include "DrawGizmo.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "Material.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

//�ֶ�ģ������
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



#pragma endregion

//�������
#pragma region  Create Camera

Camera myCamera(glm::vec3(0, 0.5f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, .0));
#pragma endregion

//���¼������� �������λ�÷���
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


    //����WS
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


    //����AD
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

    //����QE
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

//�����ƹ�
#pragma region Init Light

//ʵ����ƽ�й�
LightDirectional * lightD = new LightDirectional(glm::vec3(0.0f, 4.0f ,0.0f),
                                                 glm::vec3(glm::radians(45.0f),0,0),
                                                 glm::vec3(1.0f, 1.0f, 1.0f));

//ʵ�������
LightPoint* lightP = new LightPoint(glm::vec3(-3.0f, 5.0f, 6.0f),
                                    glm::vec3(glm::radians(90.0f), 0, 0), 
                                    glm::vec3(3.0f, 1.0f, 0.0f));

//ʵ�����۹��
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



//��������
#pragma region OpenWindow   
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

    //������� ������к���ʾ
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //�����������¼����������������
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
    //������Ⱦ���ڵĴ�С
    glViewport(0,0,1600,1200);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    //����zbuffer
    glEnable(GL_DEPTH_TEST);

#pragma endregion
    

//����shader����  �����ȡ�����ƬԪ��ɫ���ļ���������shader����
#pragma region Init Shader Program
    //����һ��Mesh ��Ҫ�õ���shader
    Shader* testshader = new Shader("Shader/vertexSource.vert", "Shader/fragmentSource.frag");

    //���Ƶƹ⸨����ʾ shader
    Shader* lightShader = new Shader("Shader/LightvertexSource.vert", "Shader/LightfragmentSource.frag");
#pragma endregion  

//����Material���� ��ȡͼƬ����ʼ������shader�Ĳ���
#pragma region Init Material  Data
//--------------------------Creat Material
//Material* myMaterial = new Material(testshader,
//                                        LoadImageToGPU("Debug/model/body_dif.png", GL_RGBA, GL_RGBA, Shader::Diffuse),
//                                        LoadImageToGPU("resource/container2specular.png", GL_RGBA, GL_RGBA, Shader::Specular),
//                                        glm::vec3(1.0f, 1.0f, 1.0f),
//                                        64.0f);
#pragma endregion 

// ����model
#pragma region Init and Load Models to VAO VBO
    std::string projectPath = GetFilePath() + "\\model\\nanosuit.obj";
    Model model( projectPath);
 #pragma endregion
 

//ģ�ͱ仯�ľ�������
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

    //��¼ ģ��λ��ֵ
    glm::vec3 t = glm::vec3(0.0f, -10.0f, 0.0f);
    //��¼ ģ����תֵ
    float angle = 0;

    float lightangle = 0;

    //������������ɫ
    glm::vec3 abColor = glm::vec3(0.2f, 0.1f, 0.4f);

    //
    glm::vec3 pointPosition = glm::vec3(lightP->position);

    // ������ͼ
    unsigned int transparentTexture = LoadImageToGPU();

    //���� VAO
    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1,&transparentVAO);
    glGenBuffers(1,&transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer( GL_ARRAY_BUFFER,transparentVBO );
    glBufferData( GL_ARRAY_BUFFER,sizeof(transparentVertices), transparentVertices,GL_STATIC_DRAW );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float),(void*)(3 *sizeof(float)) );
    
    ////----------------------------------Render Loop ��Ⱦѭ�� -------------------------  
    while (!glfwWindowShouldClose(window))
    {   
 

        //��ȡ��������
        processInput(window);

        //�������� �����Ļ�� ��ɫ
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        //�����Ļ ģʽΪ color buffer ,DEPTH_BUFFER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();

        //--------------------------------------����mesh----------------------------
        //����ģ�����任  model����
        model.ResetTransform();
        model.modelMatrix = glm::rotate(model.modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model.modelMatrix = glm::translate(model.modelMatrix, t);

        //����������� V����
        viewMat = myCamera.GetViewMatrix();
        
        //���µ��Դ����
        lightP->position = pointPosition;
        lightP->color = glm::vec3(clear_color.x,clear_color.y,clear_color.z);

        //�󶨵�ǰʹ�õ�shader��ɫ
        testshader->use();

        //������Ⱦ������������� ���ݸ�shader��ɫ�� �ƹ����ݣ�ƽ�й⣬����⣬���Դ�������⣬MVP����������ݣ�
        testshader->SetRenderingData(model.modelMatrix, viewMat, projMat, abColor, lightD, lightP, lightS, myCamera);

        //���û���ÿһ��mesh����
        model.Draw(testshader);


        //------------------------------------͸�����------------------------------
        //�����������
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        
        //����ʹ�õĻ��shader
            
        //���ݲ���

        //��vao

        //������
        
        
        
        

        //----------------------------------------���Ƶƹ�ؼ���ʾ-------------------------
        //���� �ƹ������������ݲ�����
        //���� M����
        DrawGizmo::mMatrix = glm::scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        DrawGizmo::mMatrix = glm::rotate(DrawGizmo::mMatrix, glm::radians(lightangle), glm::vec3(0.0f, 1.0f, 0.0f));
        DrawGizmo::mMatrix = glm::translate(DrawGizmo::mMatrix, pointPosition);

        //���þ���shader
        DrawGizmo::SetGizmoShader(lightShader,DrawGizmo::mMatrix,viewMat,projMat);
        
        //���Ƹ����ƹ�ؼ�������۲죨��box��־��
        unsigned int VAO,VBO;
        DrawGizmo::DrawBox(VAO,VBO);
   
	    

        //imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");
            // ����ģ��λ��
            ImGui::SliderFloat3("t", &t.x, -30.0f, 30.0f);
            // ���ڵ��Դλ��
            ImGui::SliderFloat3("pointPosition", &pointPosition.x, -30.0f, 30.0f);
            
            // ����ģ����ת
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
    //ɾ���ͷ���Դ�ķ���������������Դ ����ȷ���˳�����Ӧ��
    glfwTerminate();
    return 0;






}