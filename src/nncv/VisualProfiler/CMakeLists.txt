set(CMAKE_CXX_STANDARD 20)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

find_package(Vulkan REQUIRED)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/third_party/imgui)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/third_party/glfw)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)
include_directories(${GLFW_DIR}/deps)

set(LIBRARIES "glfw;Vulkan::Vulkan")

file(GLOB sources *.cpp)

add_executable(nncv-vp 
    ${sources} 
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp 
    ${IMGUI_DIR}/imgui.cpp 
    ${IMGUI_DIR}/imgui_draw.cpp 
    ${IMGUI_DIR}/imgui_demo.cpp 
    ${IMGUI_DIR}/imgui_tables.cpp 
    ${IMGUI_DIR}/imgui_widgets.cpp
)

target_link_libraries(nncv-vp ${LIBRARIES})

target_compile_definitions(nncv-vp PUBLIC -DImTextureID=ImU64)
