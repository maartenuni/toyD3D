cmake_minimum_required(VERSION 3.5)
project(windows-windows C CXX)

add_definitions(-DUNICODE)

add_executable(msgbox WIN32 window-main.c)
add_executable(appwin WIN32 appwindow.c)
add_executable(win3D WIN32 direct3Dwin.c)
add_executable(win3D++ WIN32 direct3Dwin.cpp)

if (NOT MSVC)
    set(WINDOWS_LINK_OPTIONS -municode -mwindows)
endif()

target_link_options(msgbox PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(appwin PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(win3D PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(win3D++ PRIVATE ${WINDOWS_LINK_OPTIONS})

target_link_libraries(win3D d3d11)
target_link_libraries(win3D++ d3d11)

