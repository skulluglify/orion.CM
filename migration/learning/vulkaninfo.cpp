#include<iostream>
#include<vulkan/vulkan.h>

#define LOG(x) std::cout << x << std::endl;

#ifndef __debugbreak
void __debugbreak(void) {}
#endif

#define ASSERT_VULKAN(val)\
		if(val != VK_SUCCESS) {\
			__debugbreak();\
		}

VkInstance instance;

int main(const int argc, const char** argv) noexcept {

	(void)argc;
	(void)argv;

	VkApplicationInfo appInfo;

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;

	appInfo.pApplicationName = "Vulkan Demo";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 3, 5);
	appInfo.pEngineName = "OrionEX";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = NULL
	};

	VkResult result = vkCreateInstance(&instanceInfo, NULL, &instance);

	switch (result) {

		case VK_SUCCESS:
			LOG("VK_SUCCESS")
			break;

		case VK_NOT_READY:
			LOG("VK_NOT_READY")
			break;

		case VK_TIMEOUT:
			LOG("VK_TIMEOUT")
			break;

		case VK_EVENT_SET:
			LOG("VK_EVENT_SET")
			break;

		case VK_EVENT_RESET:
			LOG("VK_EVENT_RESET")
			break;

		case VK_INCOMPLETE:
			LOG("VK_INCOMPLETE")
			break;

		case VK_ERROR_OUT_OF_HOST_MEMORY:
			LOG("VK_ERROR_OUT_OF_HOST_MEMORY")
			break;
			
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			LOG("VK_ERROR_OUT_OF_DEVICE_MEMORY")
			break;
			
		case VK_ERROR_INITIALIZATION_FAILED:
			LOG("VK_ERROR_INITIALIZATION_FAILED")
			break;
			
		case VK_ERROR_LAYER_NOT_PRESENT:
			LOG("VK_ERROR_LAYER_NOT_PRESENT")
			break;
			
		case VK_ERROR_EXTENSION_NOT_PRESENT:
			LOG("VK_ERROR_EXTENSION_NOT_PRESENT")
			break;
			
		case VK_ERROR_INCOMPATIBLE_DRIVER:
			LOG("VK_ERROR_INCOMPATIBLE_DRIVER")
			break;

		case VK_ERROR_DEVICE_LOST:
			LOG("VK_ERROR_DEVICE_LOST")
			break;

		case VK_ERROR_MEMORY_MAP_FAILED:
			LOG("VK_ERROR_MEMORY_MAP_FAILED")
			break;

		case VK_ERROR_FEATURE_NOT_PRESENT:
			LOG("VK_ERROR_FEATURE_NOT_PRESENT")
			break;

		case VK_ERROR_TOO_MANY_OBJECTS:
			LOG("VK_ERROR_TOO_MANY_OBJECTS")
			break;

		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			LOG("VK_ERROR_FORMAT_NOT_SUPPORTED")
			break;

		case VK_ERROR_FRAGMENTED_POOL:
			LOG("VK_ERROR_FRAGMENTED_POOL")
			break;

		case VK_ERROR_UNKNOWN:
			LOG("VK_ERROR_UNKNOWN")
			break;

		case VK_ERROR_OUT_OF_POOL_MEMORY:
			LOG("VK_ERROR_OUT_OF_POOL_MEMORY")
			break;

		case VK_ERROR_INVALID_EXTERNAL_HANDLE:
			LOG("VK_ERROR_INVALID_EXTERNAL_HANDLE")
			break;

		case VK_ERROR_FRAGMENTATION:
			LOG("VK_ERROR_FRAGMENTATION")
			break;

		case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
			LOG("VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS")
			break;

		case VK_ERROR_SURFACE_LOST_KHR:
			LOG("VK_ERROR_SURFACE_LOST_KHR")
			break;

		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			LOG("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR")
			break;

		case VK_SUBOPTIMAL_KHR:
			LOG("VK_SUBOPTIMAL_KHR")
			break;

		case VK_ERROR_OUT_OF_DATE_KHR:
			LOG("VK_ERROR_OUT_OF_DATE_KHR")
			break;

		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			LOG("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR")
			break;

		case VK_ERROR_VALIDATION_FAILED_EXT:
			LOG("VK_ERROR_VALIDATION_FAILED_EXT")
			break;

		case VK_ERROR_INVALID_SHADER_NV:
			LOG("VK_ERROR_INVALID_SHADER_NV")
			break;

		case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
			LOG("VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT")
			break;

		case VK_ERROR_NOT_PERMITTED_EXT:
			LOG("VK_ERROR_NOT_PERMITTED_EXT")
			break;

		case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
			LOG("VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT")
			break;

		case VK_THREAD_IDLE_KHR:
			LOG("VK_THREAD_IDLE_KHR")
			break;

		case VK_THREAD_DONE_KHR:
			LOG("VK_THREAD_IDLE_KHR")
			break;

		case VK_OPERATION_DEFERRED_KHR:
			LOG("VK_OPERATION_DEFERRED_KHR")
			break;

		case VK_OPERATION_NOT_DEFERRED_KHR:
			LOG("VK_OPERATION_NOT_DEFERRED_KHR")
			break;

		case VK_PIPELINE_COMPILE_REQUIRED_EXT:
			LOG("VK_PIPELINE_COMPILE_REQUIRED_EXT")
			break;

		case VK_RESULT_MAX_ENUM:
			LOG("VK_RESULT_MAX_ENUM")
			break;
	}

	ASSERT_VULKAN(result);

	return 0;
}
