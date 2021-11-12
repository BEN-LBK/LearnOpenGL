#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
 
//定于窗口宽高
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
 
int main()
{
 
    glfwInit();//初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//OpenGL 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式（Core-profile）
 
    //使用的是Max OS X系统，将下面代码解除注释
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 
    //Open GLFW Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
 
    //GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //注册framebuffer_size_callback函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    //渲染循环 Render Loop
    while(!glfwWindowShouldClose(window)) //glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出
    {
        
        //输入
        processInput(window);
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲
 
        //检查并调用事件，交换缓冲
        
        //glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
        glfwPollEvents();
        //glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲),它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwSwapBuffers(window);
    }
    
    //防止窗口一闪而过
    while(!glfwWindowShouldClose(window))
    {
        std::cout << " WIindow opon"<< std::endl;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //释放/删除之前的分配的所有资源
    glfwTerminate();
    return 0;
}
 
//回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    std::cout<< "width:" << width << " height:"<< height << std::endl;
    glViewport(0, 0, width, height);
}
 
//检查用户是否按下了返回键(Esc)如果没有按下，glfwGetKey将会返回GLFW_RELEASE。
//如果用户的确按下了返回键，我们将通过glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
//下一次while循环的条件检测将会失败，程序将会关闭
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
