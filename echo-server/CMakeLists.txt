

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Boost REQUIRED)
find_package(glog REQUIRED)

add_executable(echo-server main.cpp)

target_link_libraries(echo-server Boost::headers glog)

# include(CTest)
# if (BUILD_TESTING)
#     add_subdirectory(tests)
# endif ()
