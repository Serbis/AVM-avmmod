cmake_minimum_required(VERSION 3.8)
project(avmmod)

set(CMAKE_C_STANDARD 99)

set(SOURCE_EXE main.c)		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB libs/linklist.c)			# Тоже самое, но для библиотеки

add_library(foo STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(avmmod ${SOURCE_EXE})	# Создает исполняемый файл с именем main

target_link_libraries(avmmod foo)		# Линковка программы с библиотекой


#add_executable(avmmod main.c)