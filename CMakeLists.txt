cmake_minimum_required(VERSION 3.25)
project(n_body_simulations)

set(CMAKE_CXX_STANDARD 14)


# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES Catch2/2.6.0@catchorg/stable
        BASIC_SETUP)

add_executable(n_body_simulations
        main.cpp)
target_link_libraries(main ${CONAN_LIBS})

#conan_cmake_run (CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS NO_OUTPUT_DIRS)

#find_package(boost REQUIRED)
#if(boost_FOUND)
#    target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${boost_LIBRARIES})
#endif()
#
##find_package(glfw REQUIRED)
##if(glfw_FOUND)
##    target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_INCLUDE_DIRS})
##    target_link_libraries(${PROJECT_NAME} PRIVATE ${glfw_LIBRARIES})
##endif()
#
#find_package(opengl REQUIRED)
#if(opencl_FOUND)
#    target_include_directories(${PROJECT_NAME} PRIVATE ${opengl_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${opengl_LIBRARIES})
#endif()
#
#find_package(qt REQUIRED)
#if(qt_FOUND)
#    target_include_directories(${PROJECT_NAME} PRIVATE ${qt_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${qt_LIBRARIES})
#endif()
#
#find_package(glew REQUIRED)
#if(glew_FOUND)
#    target_include_directories(${PROJECT_NAME} PRIVATE ${glew_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${glew_LIBRARIES})
#endif()
#
##find_package(glm REQUIRED)
##if(glm_FOUND)
##    target_include_directories(${PROJECT_NAME} PRIVATE ${glm_INCLUDE_DIRS})
##    target_link_libraries(${PROJECT_NAME} PRIVATE ${glm_LIBRARIES})
##endif()