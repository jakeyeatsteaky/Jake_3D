#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <iostream>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

class VulkanRenderer
{
public:
	VulkanRenderer() = default;
	~VulkanRenderer() = default;
	void Init();
	void CreateInstance();
	bool CheckValidationLayers();

	void CleanUp();

	std::vector<VkExtensionProperties> EnumerateExtensions(bool printEnumList);

private:
	VkInstance m_instance;
	std::vector<VkExtensionProperties> m_vkExtProps;
	std::vector<const char*> m_validationLayers;
	bool m_enableValidationLayers = false;


};



#endif




