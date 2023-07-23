cmake_minimum_required(VERSION 3.25)
project(n_body_simulations)

set(CMAKE_CXX_STANDARD 14)

# add_library(n_body_simulations, yaml-cpp, data_reader.cpp)

#find_library(GLFW test_library lib)
#target_link_libraries(cmake_testapp LINK_PUBLIC ${GLFW})

add_executable(n_body_simulations
        main.cpp)

find_package(boost REQUIRED)
if(boost_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${boost_LIBRARIES})
endif()

#find_package(glfw REQUIRED)
#if(glfw_FOUND)
#    target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${glfw_LIBRARIES})
#endif()

find_package(opengl REQUIRED)
if(opencl_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${opengl_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${opengl_LIBRARIES})
endif()

find_package(qt REQUIRED)
if(qt_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${qt_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${qt_LIBRARIES})
endif()

find_package(glew REQUIRED)
if(glew_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${glew_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${glew_LIBRARIES})
endif()

#find_package(glm REQUIRED)
#if(glm_FOUND)
#    target_include_directories(${PROJECT_NAME} PRIVATE ${glm_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${glm_LIBRARIES})
#endif()