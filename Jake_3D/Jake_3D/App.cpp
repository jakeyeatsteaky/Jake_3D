#include "App.h"


App::App() {
	
}

bool App::IsRunning() {
	if (glfwWindowShouldClose(m_window))
		m_running = false;
	return m_running;
}

void App::Setup() 
{
	glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(800, 600, "Jake 3D", nullptr, nullptr);
	m_running = true;

	m_renderer = new VulkanRenderer();
	m_renderer->Init();
}

void App::Input() 
{
	glfwPollEvents();
}

void App::Update() 
{

}

void App::Render() 
{

}

void App::Destroy() 
{
	m_renderer->CleanUp();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}