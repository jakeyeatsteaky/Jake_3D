#ifndef APP_H
#define APP_H

#include "VulkanRenderer.h"

class App
{
public:
	App();
	~App() = default;

	bool IsRunning();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();

private:
	bool m_running = false;
	VulkanRenderer* m_renderer;
	GLFWwindow* m_window;

};

#endif