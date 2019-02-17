CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(StreamStringLibrary)

SET(CMAKE_CXX_STANDARD 17)

SET(SOURCE_FILES
	StreamPosition/StreamPosition.cpp
	StreamPosition/StreamPosition.h
	StreamString.cpp
	StreamString.h)

ADD_LIBRARY(StreamStringLibrary SHARED ${SOURCE_FILES})
