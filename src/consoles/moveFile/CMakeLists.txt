project(moveFile LANGUAGES CXX)

include_directories(../libs/processArgs)
include_directories(../libs/processPath)


find_package(Qt6 REQUIRED COMPONENTS Core) 

# 当前目录下也有代码

FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h")
add_executable(${PROJECT_NAME}
  ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    processArgs
    processPath)


install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

