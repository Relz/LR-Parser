CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(LexerLibrary)

SET(CMAKE_CXX_STANDARD 17)

SET(SOURCE_FILES
	NumberSystem/NumberSystem.h
	NumberSystem/NumberSystemExtensions/NumberSystemExtensions.cpp
	NumberSystem/NumberSystemExtensions/NumberSystemExtensions.h
	Lexer.cpp
	Lexer.h)

ADD_LIBRARY(LexerLibrary SHARED ${SOURCE_FILES})

IF (NOT TARGET InputLibrary)
	ADD_SUBDIRECTORY(InputLibrary)
ENDIF ()

IF (NOT TARGET TokenLibrary)
	ADD_SUBDIRECTORY(TokenLibrary)
ENDIF ()

TARGET_LINK_LIBRARIES(LexerLibrary InputLibrary TokenLibrary)
