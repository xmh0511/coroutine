cmake_minimum_required(VERSION 2.8)
project(asmtest)



# Set cflags
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -g -fno-strict-aliasing -O2 -Wall -export-dynamic -Wall -pipe  -D_GNU_SOURCE -D_REENTRANT -Wno-deprecated -m64)

# Use c and asm
enable_language(C ASM)

# Add source files
set(SOURCE_FILES
        main.cpp
        asm.S)

add_executable(asmtest ${SOURCE_FILES})
target_link_libraries(asmtest pthread dl)

install(TARGETS asmtest DESTINATION include)


