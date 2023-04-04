#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <iostream>
#include <optional>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

struct QueueFamilyIdxs
{
	std::optional<uint32_t> graphicsFamily;

	bool IsComplete() {	return graphicsFamily.has_value(); }
};

class VulkanRenderer
{
public:
	VulkanRenderer() = default;
	~VulkanRenderer() = default;
	void Init();
	void CreateInstance();
	bool CheckValidationLayers();
	VkResult SetupDebugMessenger();
	void DestroyDebugMessenger();
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIdxs FindQueueFamilies(VkPhysicalDevice device);

	void CleanUp();

	std::vector<VkExtensionProperties> EnumerateExtensions(bool printEnumList);
	std::vector<const char*> getRequiredExtensions() { return m_requiredExtensions; }

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

private:
	VkInstance m_instance;
	VkDebugUtilsMessengerEXT m_debugMessenger;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	std::vector<VkExtensionProperties> m_vkExtProps;
	std::vector<const char*> m_validationLayers;
	std::vector<const char*> m_requiredExtensions;
	QueueFamilyIdxs m_queueFamilyIndices;
	bool m_enableValidationLayers = false;


};



#endif




