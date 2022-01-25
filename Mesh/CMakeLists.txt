project(Mesh)

file(GLOB_RECURSE SOURCES
    "include/*.h"
    "src/*.cpp"
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
install(TARGETS ${PROJECT_NAME})
install(FILES ${SOURCES} DESTINATION MeshLibrary)
