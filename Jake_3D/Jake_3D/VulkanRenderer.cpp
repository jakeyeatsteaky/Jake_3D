#include "VulkanRenderer.h"

#include <algorithm>

void VulkanRenderer::Init()
{
    if (!CheckValidationLayers()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

	CreateInstance();
    m_vkExtProps = EnumerateExtensions(true);

}

void VulkanRenderer::CreateInstance()
{
    // optional application info for the drivers and stuff
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Jake-3D";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // required instance info struct where you specify application info
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

        // use glfw specific function to specify windowing extension info
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    if (m_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
        createInfo.ppEnabledLayerNames = m_validationLayers.data();
    } else
        createInfo.enabledLayerCount = 0;


    // Create the instance. 
    // This paradigm is very common in vulkan creation of objects:
    //      1. Pointer to info of object to create
    //      2. Pointer to a custom allocator
    //      3. Pointer to the variable that will hold this new object

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

std::vector<VkExtensionProperties> VulkanRenderer::EnumerateExtensions(bool printEnumList)
{
    // Identify size for vector
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // initialize vector and pass pointer to data into vk function to populate extProps
    std::vector<VkExtensionProperties> ret(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, ret.data());

    if (printEnumList)
    {
        std::cout << "available extensions:\n";

        for (const auto& extension : ret) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }
    return ret;
}

bool VulkanRenderer::CheckValidationLayers()
{
    m_validationLayers = { "VK_LAYER_KHRONOS_validation" };
    m_enableValidationLayers = true;

    // Check Validation Layer Support
    uint32_t layerCount; 
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : m_validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;


}

void VulkanRenderer::CleanUp()
{
    /*
       Destroy all Other Vulkan Things
    */

    vkDestroyInstance(m_instance, nullptr);
}

