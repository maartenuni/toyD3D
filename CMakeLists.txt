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

if (MSVC)
    target_compile_options(msgbox  PRIVATE /W4)
    target_compile_options(appwin  PRIVATE /W4)
    target_compile_options(win3D   PRIVATE "/W3")
    target_compile_options(win3D++ PRIVATE /W4)
else()
    target_compile_options(msgbox  PRIVATE -Wall -pedantic)
    target_compile_options(appwin  PRIVATE -Wall -pedantic)
    target_compile_options(win3D   PRIVATE -Wall -pedantic)
    target_compile_options(win3D++ PRIVATE -Wall -pedantic)
endif()
 
set_target_properties(
        win3D
    PROPERTIES 
        C_STANDARD 11
        C_STANDARD_REQUIRED TRUE
    )



target_link_options(msgbox  PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(appwin  PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(win3D   PRIVATE ${WINDOWS_LINK_OPTIONS})
target_link_options(win3D++ PRIVATE ${WINDOWS_LINK_OPTIONS})

target_link_libraries(win3D d3d11 dxguid)
target_link_libraries(win3D++ d3d11)

