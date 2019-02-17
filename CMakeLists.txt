CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(LRParser)

SET(CMAKE_CXX_STANDARD 17)

SET(SOURCE_FILES
	main.cpp
	Symbol/Symbol.cpp
	Symbol/Symbol.h
	Cell/Cell.cpp
	Cell/Cell.h Collapse/Collapse.cpp Collapse/Collapse.h)

ADD_EXECUTABLE(LRParser ${SOURCE_FILES})

IF (NOT TARGET InputLibrary)
	ADD_SUBDIRECTORY(InputLibrary)
ENDIF ()

IF (NOT TARGET LexerLibrary)
	ADD_SUBDIRECTORY(LexerLibrary)
ENDIF ()

TARGET_LINK_LIBRARIES(LRParser InputLibrary LexerLibrary)
