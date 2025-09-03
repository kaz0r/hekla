#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

// spdlog is available in extern/spdlog/
// To use: #define SPDLOG_HEADER_ONLY then #include <spdlog/spdlog.h>
// Note: May need fmt library properly configured for your system
#define SPDLOG_HEADER_ONLY
#define FMT_HEADER_ONLY
#include <spdlog/spdlog.h>

#define GL_LINE 0x1B01

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create window
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Hekla - OpenGL Window", NULL, NULL);
  if (window == NULL) {
    // std::cerr << "Failed to create GLFW window" << std::endl;
    spdlog::error("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Load OpenGL function pointers with GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    // std::cerr << "Failed to initialize GLAD" << std::endl;
    spdlog::error("Failed to initialize GLAD");
    return -1;
  }

  // Print OpenGL version info
  spdlog::info("OpenGL Version: {}",
               reinterpret_cast<const char *>(glGetString(GL_VERSION)));
  spdlog::info("GLSL Version: {}", reinterpret_cast<const char *>(glGetString(
                                       GL_SHADING_LANGUAGE_VERSION)));
  spdlog::info("Vendor: {}",
               reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
  spdlog::info("Renderer: {}",
               reinterpret_cast<const char *>(glGetString(GL_RENDERER)));

  float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };

  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO); // 1. bind VAO first

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2. copy vertices
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // 3. copy indices
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    // std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
    //           << infoLog << std::endl;
    spdlog::error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
  }

  const char *fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    spdlog::error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
  }

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // 4. set vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0); // unbind VAO

  // Main render loop
  while (!glfwWindowShouldClose(window)) {
    // Handle input
    process_input(window);

    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup
  glfwTerminate();
  return 0;
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width,
                               int height) {
  glViewport(0, 0, width, height);
}
