cmake_minimum_required(VERSION 3.9)
project(ErgasiaVraka)

add_executable(ErgasiaVraka 
            main.cpp
            database.h
            array.h
            avltree.h
            avlnode.h
            hashtable.h
            datahandler.h datahandler.cpp
            webclass.h webclass.cpp
            command_interpreter.h command_interpreter.cpp 
            tsomtable.h)