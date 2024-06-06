set(SOURCES
    main.cpp
    core/JT_Window.cpp
)

set(HEADERS
    core/JT_Window.h
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE sdlLib imgui)