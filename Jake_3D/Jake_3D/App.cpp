#include "App.h"


App::App() {
	
}

bool App::IsRunning() {
	if (glfwWindowShouldClose(m_renderer->getWindow()))
		m_running = false;
	return m_running;
}

void App::Setup() 
{
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
	glfwDestroyWindow(m_renderer->getWindow());
	glfwTerminate();
}