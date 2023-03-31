#include "VulkanRenderer.h"

void VulkanRenderer::Init()
{
	glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(800, 600, "Jake 3D", nullptr, nullptr);
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::cout << extensionCount << " extensions supported\n";
}