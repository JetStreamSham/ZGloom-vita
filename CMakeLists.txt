cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(ZGloom)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "ZGloom")
set(VITA_TITLEID  "JETSGLOOM")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

#include_directories(
#  common
#)

add_executable(${PROJECT_NAME}
#	src/logger.h
#	src/logger.cpp
	src/input.h
	src/input.cpp
	src/script.h
	src/script.cpp
	src/monsterlogic.h
	src/monsterlogic.cpp
	src/soundhandler.h
	src/soundhandler.cpp
	src/config.h
	src/config.cpp
	src/titlescreen.h
	src/titlescreen.cpp
	src/hud.h
	src/hud.cpp
	src/iffhandler.h
	src/iffhandler.cpp
	src/font.h
	src/font.cpp
	src/menuscreen.cpp
	src/menuscreen.h
	src/gamelogic.cpp
	src/gamelogic.h
	src/binresources.h
	src/binresource.cpp
	src/gloommap.h
	src/gloommap.cpp
	src/objectgraphics.h
	src/objectgraphics.cpp
	src/gloommaths.h
	src/gloommaths.cpp
	src/crmfile.h
	src/quick.h
	src/quick.cpp
	src/decrunchmania.h
	src/decrunchmania.cpp
	src/renderer.h
	src/renderer.cpp
	src/zgloom.cpp

)

target_link_libraries(${PROJECT_NAME}
  SDL2_mixer
  SDL2
  mikmod
  mpg123
  FLAC
  vorbisfile
  vorbis
  ogg
  xmp
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceSysmodule_stub
  SceGxm_stub
  SceCommonDialog_stub
  SceAppMgr_stub
  SceTouch_stub
  SceHid_stub
  SceMotion_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)
