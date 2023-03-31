#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

class VulkanRenderer
{
public:
	VulkanRenderer() = default;
	~VulkanRenderer() = default;
	void Init();
	GLFWwindow* getWindow() { return m_window; }

private:
	GLFWwindow* m_window;
	uint32_t m_extensionCount;

};






#endif




