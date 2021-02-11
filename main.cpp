#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <ctime>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main()
{
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "uniform mat4 scale;\n"
        "uniform mat4 goup;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        //"		if(model == mat4(0.0f)) goup * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "		gl_Position = view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "		TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);\n"
        //"ourColor = aColor;\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        //"in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"
    //	"uniform sampler2D texture1;\n"
        "uniform sampler2D texture2;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(texture2, TexCoord);\n"
        "}\n";
    GLFWwindow* window;
    if (!glfwInit()) {
        std::cout << "glfwerror\n";
    }
    window = glfwCreateWindow(720, 600, "practice", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "glew error\n";
    }
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height, nrChannels;
    int bgwidth, bgheight, brchannels;
    unsigned char* data = stbi_load("/home/viveklinux/personel/openglproj/flappy/assets/0.png", &width, &height, &nrChannels, 0);
    unsigned char* background = stbi_load("/home/viveklinux/personel/openglproj/flappy/assets/top.png", &bgwidth, &bgheight, &brchannels, 0);

    float vertices[] = { -0.5f,  -0.5f , -0.5f,  0.0f, 0.0f,
                         -0.25f, -0.5f , -0.5f,  1.0f, 0.0f,
                         -0.25f, -0.25f, -0.5f,  1.0f, 1.0f,
                         -0.25f, -0.25f, -0.5f,  1.0f, 1.0f,
                         -0.5f,  -0.25f, -0.5f,  0.0f, 1.0f,
                         -0.5f,  -0.5f , -0.5f,  0.0f, 0.0f,
                          0.0f,  -1.0f , -0.5f,  0.0f, 0.0f,
                          0.5f,  -1.0f,  -0.5f,  1.0f, 0.0f,
                          0.5f,   0.0f,  -0.5f,  1.0f, 1.0f,
                          0.5f,   0.0f,  -0.5f,  1.0f, 1.0f,
                          0.0f,   0.0f,  -0.5f,  0.0f, 1.0f,
                          0.0f,  -1.0f,  -0.5f,  0.0f, 0.0f
                       };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 0.0f,  1.8f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  1.8f,  0.0f),
        glm::vec3( 2.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  1.8f,  0.0f),
        glm::vec3( 3.0f,  0.0f,  0.0f),
        glm::vec3( 3.0f,  1.8f,  0.0f)
        //glm::vec3( 0.5f,  0.2f,  0.0f),
        //glm::vec3( 0.3f,  0.0f,  0.0f)
    };

    float assigned[]{
        -1.0f, -1.0f, -1.0f, -1.0f , -1.0f , -1.0f , -1.0f , -1.0f
    };
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * 6 * 5 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* 4));
    glEnableVertexAttribArray(1);

    unsigned int texture[2];
    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    //glBindTexture(GL_TEXTURE_2D, texture);


    //glGenTextures(1, &bgtexture);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgwidth, bgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, background);
    glGenerateMipmap(GL_TEXTURE_2D);

    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vao);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shader;
    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);
    glUseProgram(shader);
    glValidateProgram(shader);
    glm::vec3 bird(0.0f, 0.0f, 0.0f);
    float x_Cor = 0.0f;
    float t = 0.02f;
    std::vector<float> arr(4, -1);
    int pipe = 0;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        float up_val = 0;
        float down_val = 0.02f;

        bird.y -= t;
        bird.x += 0.006f;
        //std::cout << gravity.y << "\n";
        glm::mat4 view = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(x_Cor, 0.0f, 0.0f));
        x_Cor -= 0.006f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { up_val += 0.06f; t = 0.02f;}
      //  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { /*up_val += 0.07f;*/ t = 0.02f;}
        //std::cout << gravity.y << "\n";
        //std::cout << assigned[0] << " " << assigned[2]  << " " << assigned[4] << "\n";
        //std::cout << (int)bird.x % 4 << "\n";
        if ((bird.x - (int)bird.x) > 0.3f && (bird.x - (int)bird.x) < 0.8f) {
            if (bird.y > arr[(int)bird.x % 4] + 0.45f && bird.y < (arr[(int)bird.x % 4] + 1.10f)) {
                 //std::cout << bird.x << " " << bird.y  << " " << arr[(int)bird.x % 4] << "\n";
            }
          //  pipe++;
            else { break; }
        }
        t += 0.001f;
        glm::mat4 model = glm::mat4(1.0f);
        //gravity.x = 0.001f;
        bird.y += up_val;

        model = glm::translate(model, bird);
        //if (gravity.y > 1.3f || gravity.y < -1.3f) std::cout << "game ended\n";
        unsigned int texloc = glGetUniformLocation(shader, "texture2");
        unsigned int pos    = glGetUniformLocation(shader, "model");
        unsigned int view_mat = glGetUniformLocation(shader, "view");
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glUniform1i(texloc, 0);
        glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_mat, 1, GL_FALSE, glm::value_ptr(view));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glUniform1i(texloc, 0);
        int turn = 0;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for(int i = 0; i < 8; i++)
        {
            model = glm::mat4(1.0f);
            if(assigned[i] == -1.0f){
                if(i % 2 == 0){ 
                    int pos_pipes = std::rand() % 80;
                    if (pos_pipes == 0)  assigned[i] = 0.0f;
                    else {
                        assigned[i] = float(pos_pipes) / 100.0f;
                        assigned[i] = -1 * assigned[i];
                    }
                    arr[i/2] = assigned[i];
                }
                else{
                    assigned[i] =  assigned[i - 1];
                }
            }
            model = glm::translate(model, glm::vec3(0.0f, assigned[i], 0.0f));
            model = glm::translate(model, cubePositions[i]);

            unsigned int pos = glGetUniformLocation(shader, "model");
            glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 6, 12);
            model = glm::mat4(1.0f);
            if (bird.x - cubePositions[i].x > 1.5f) { cubePositions[i].x += 4; assigned[i] = -1.0f;  }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
