add_subdirectory(SDL)
add_subdirectory(imgui)

add_library(sdlLib INTERFACE)

target_link_libraries(sdlLib INTERFACE SDL3::SDL3)