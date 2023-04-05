#include "VulkanRenderer.h"

#include <algorithm>

void VulkanRenderer::Init()
{
    if (!CheckValidationLayers()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    m_vkExtProps = EnumerateExtensions(true);

	CreateInstance();

    if (SetupDebugMessenger() != VK_SUCCESS)
        throw std::runtime_error("failed to set up debug messenger\n");

    PickPhysicalDevice();
    CreateLogicalDevice();
    

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

        // use glfw specific function to specify windowing extension info, and debug callback extensions
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        
    if (m_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
        createInfo.ppEnabledLayerNames = m_validationLayers.data();
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = DebugCallback;
		debugCreateInfo.pUserData = nullptr; // Optional
	
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }
    m_requiredExtensions = std::move(extensions);
    createInfo.enabledExtensionCount = m_requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = m_requiredExtensions.data();



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
        std::cout << extensionCount << " available extensions:\n";

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

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
    std::cerr << "VVL--> " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VkResult VulkanRenderer::SetupDebugMessenger()
{
    if (!m_enableValidationLayers) return VK_ERROR_FEATURE_NOT_PRESENT;
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = DebugCallback;
    debugCreateInfo.pUserData = nullptr; // Optional

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
    if (func == nullptr) 
        return VK_ERROR_EXTENSION_NOT_PRESENT;
   
    return func(m_instance, &debugCreateInfo, nullptr, &m_debugMessenger);
}

void VulkanRenderer::DestroyDebugMessenger()
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(m_instance, m_debugMessenger, nullptr);
    }
}

void VulkanRenderer::PickPhysicalDevice()
{
    // list graphics cards available
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
    if (deviceCount == 0)
        throw std::runtime_error("failed to find GPUs with Vulkan support\n");
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (IsDeviceSuitable(device)) {
            m_physicalDevice = device;
            
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(m_physicalDevice, &deviceProperties);
            std::cout << "Selected Physical Device: " << deviceProperties.deviceName << std::endl;
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }

}

bool VulkanRenderer::IsDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIdxs m_queueFamilyIndices = FindQueueFamilies(device);

    return m_queueFamilyIndices.IsComplete();
}

QueueFamilyIdxs VulkanRenderer::FindQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIdxs indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.IsComplete()) {
            break;
        }

        i++;
    }

    return indices;
    
}

void VulkanRenderer::CreateLogicalDevice()
{
    m_queueFamilyIndices = FindQueueFamilies(m_physicalDevice);
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = m_queueFamilyIndices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (m_enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
        createInfo.ppEnabledLayerNames = m_validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_device, m_queueFamilyIndices.graphicsFamily.value(), 0, &m_graphicsQueue);

}


void VulkanRenderer::CleanUp()
{
    vkDestroyDevice(m_device, nullptr);

    if (m_enableValidationLayers)
        DestroyDebugMessenger();

    vkDestroyInstance(m_instance, nullptr);
}

