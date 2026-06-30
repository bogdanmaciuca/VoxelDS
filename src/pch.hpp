#pragma once

#include <iostream>
#include <format>
#include <source_location>
#include <string_view>
#include <mutex>
#include <type_traits>
#include <functional>


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
