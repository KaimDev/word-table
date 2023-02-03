cmake_minimum_required(VERSION 3.24)

project(WordTable C)

add_executable(WordTable Main.c)

target_compile_features(WordTable PUBLIC c_std_17)