cmake_minimum_required(VERSION 3.5)
project(windows-windows C CXX)

add_executable(msgbox window-main.c)
add_executable(appwin appwindow.c)
add_executable(win3D direct3Dwin.c)
add_executable(win3D++ direct3Dwin.cpp)

set(WINDOWS_LINK_OPTIONS -municode -mwindows)

target_link_options(msgbox PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(appwin PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(win3D PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(win3D++ PRIVATE ${WINDOWS_LINK_OPTIONS})

target_link_libraries(win3D d3d11)
target_link_libraries(win3D++ d3d11)

