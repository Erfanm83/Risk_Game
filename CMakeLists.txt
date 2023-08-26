cmake_minimum_required(VERSION 3.24)
project(untitled C)
configure_file(Risk_menu.jpg Risk_pause_menu.jpg background-sea-water.jpg soldier.png Help_menu1.jpg Help_menu2.jpg
        Help_menu3.jpg Help_menu4.jpg map_background.jpg info_menu.jpg winner_page.jpg Risk_player_menu.jpg
        dota_logo.jpg Yakuza-.opus COPYONLY)
set(CMAKE_C_STANDARD 11)

add_executable(Risk_Game main.c)
INCLUDE_DIRECTORIES(/usr/include/allegro5)
LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu)

file(GLOB LIBRARIES "/usr/lib/x86_64-linux-gnu/liballegro*.so")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(Risk_Game ${LIBRARIES})
