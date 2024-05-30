# Add the source files
set(SOURCES
    lexer.cpp
    token.cpp
)

# Add the header files
set(HEADERS
    lexer.h
    token.h
)

# Add the executable target
add_executable(monkey ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(monkey PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


