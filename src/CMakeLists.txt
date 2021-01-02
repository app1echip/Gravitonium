cmake_minimum_required(VERSION 3.14)
project(Gravitonium)

set(SFML_DIR "PATHTOLIB/SFML/lib/cmake/SFML")
set(BOX2D_LIB "PATHTOLIB/Box2d/lib/libBox2D.a")

set(SFML_INCLUDE_DIRECTORIES "PATHTOLIB/Box2D/include")
set(RAPIDJSON_INCLUDE_DIRECTORIES "PATHTOLIB/RapidJSON/include")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(SFML_STATIC_LIBRARIES TRUE)

include_directories(${RAPIDJSON_INCLUDE_DIRECTORIES})
include_directories(${SFML_INCLUDE_DIRECTORIES})

add_executable(Gravitonium WIN32 main.cpp Resource/ResourceManager.cpp Resource/ResourceManager.h Resource/ResourceManager/TextureManager.cpp Resource/ResourceManager/TextureManager.h State.h Game.cpp Game.h State/Play/Play.cpp State/Play/Play.h State/Play/Object/Weapon.cpp State/Play/Object/Weapon.h State/Play/Object/Character.cpp State/Play/Object/Character.h State/Play/Object/Map.cpp State/Play/Object/Map.h State/Play/Physics/ContactListener.cpp State/Play/Physics/ContactListener.h State/Play/Object/Bullet.cpp State/Play/Object/Bullet.h State/Play/Object/BaseObject.cpp State/Play/Object/BaseObject.h State/MainMenu.cpp State/MainMenu.h State/Widget.cpp State/Widget.h Resource/ResourceManager/FontManager.cpp Resource/ResourceManager/FontManager.h State/MultiPlay/Server.cpp State/MultiPlay/Server.h State/MultiPlay/Client.cpp State/MultiPlay/Client.h Resource/ResourceManager/SoundManager.cpp Resource/ResourceManager/SoundManager.h State/Help.cpp State/Help.h GameConfig.cpp GameConfig.h)

find_package(SFML 2.5.1 COMPONENTS graphics window network audio REQUIRED)

target_link_libraries(Gravitonium sfml-graphics sfml-window sfml-network sfml-audio)
target_link_libraries(Gravitonium ${BOX2D_LIB})