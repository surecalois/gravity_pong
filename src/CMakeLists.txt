cmake_minimum_required(VERSION 2.6)

set ( PROJECT_NAME Gravity_pong2 )

project ( ${PROJECT_NAME} )

SET(CMAKE_CXX_FLAGS "-std=c++0x")

# declaring files in your project

set ( SOURCES
 main.cpp
 mainwindow.cpp
 gravity_scene2.cpp
)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set ( MOC_HEADERS
 mainwindow.h
 gravity_scene2.h
 #colorlinez2.h
)

set ( UIS
 mainwindow.ui
)

#set ( RESOURCES
# main.qrc
#)

# Next lines needed for building all Qt projects
find_package( Qt REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )

# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
#QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

# compile
add_executable( ${PROJECT_NAME} ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
# or use line below instead, if you using Windows ™ Operating System.
#add_executable( PROJECT_NAME WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} )


#=======below is to avoid the console window==================#

# generate proper GUI program on specified platform
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)
