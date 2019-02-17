CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(TokenLibrary)

SET(CMAKE_CXX_STANDARD 17)

SET(SOURCE_FILES
	Token.h
	Parenthesis/Parenthesis.cpp
	Parenthesis/Parenthesis.h
	TokenConstant/TokenConstant.cpp
	TokenConstant/TokenConstant.h
	TokenExtensions/TokenExtensions.cpp
	TokenExtensions/TokenExtensions.h
	TokenInformation/TokenInformation.cpp
	TokenInformation/TokenInformation.h)

ADD_LIBRARY(TokenLibrary SHARED ${SOURCE_FILES})

IF (NOT TARGET StreamStringLibrary)
ADD_SUBDIRECTORY(StreamStringLibrary)
ENDIF ()

TARGET_LINK_LIBRARIES(TokenLibrary StreamStringLibrary)
