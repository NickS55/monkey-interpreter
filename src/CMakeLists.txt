# Add the source files
set(SOURCES
    lexer.cpp
    token.cpp
    repl.cpp
    main.cpp
    parser.cpp
    ast.cpp
)

# Add the header files
set(HEADERS
    lexer.h
    token.h
    repl.h
    main.h
    parser.h
    ast.h
)

# Add the executable target
add_executable(monkey ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(monkey PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


