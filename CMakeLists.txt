cmake_minimum_required(VERSION 3.8)
project(avmmod)

set(CMAKE_C_STANDARD 99)

set(SOURCE_EXE main.c libs/avm/src/linklist.c libs/avm/includes/linklist.h libs/avm/src/avm.c libs/avm/includes/avm.h libs/avm/src/initializer.c libs/avm/includes/initializer.h libs/avm/includes/fss.h libs/avm/includes/defines.h libs/avm/src/fss.c libs/avm/includes/frame.h libs/avm/includes/object.h libs/avm/includes/thread.h libs/avm/includes/heap.h libs/avm/includes/stack.h libs/avm/includes/interpretator.h libs/avm/includes/classloader.h libs/avm/src/classloader.c libs/avm/src/interpretator.c libs/avm/src/heap.c libs/avm/includes/rlogger.h libs/avm/src/rlogger.c libs/avm/src/stack.c libs/avm/src/thread.c libs/avm/includes/cfutils.h libs/avm/includes/class.h)		# Установка переменной со списком исходников для исполняемого файла

#set(SOURCE_LIB libs/linklist.c)			# Тоже самое, но для библиотеки
#set(AVM_LIB libs/avm/avm.c)			# Тоже самое, но для библиотеки


#add_library(foo STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo
#add_library(avm STATIC ${AVM_LIB})	# Создание статической библиотеки с именем avm


add_executable(avmmod ${SOURCE_EXE})	# Создает исполняемый файл с именем main

#target_link_libraries(avmmod foo avm)		# Линковка программы с библиотекой
