project(Siedler)
cmake_minimum_required(VERSION 3.28.3)

# Finde Python
find_package(Python3 COMPONENTS Interpreter Development NumPy)

# Definiere den absoluten Pfad zum include-Verzeichnis
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Füge das include-Verzeichnis hinzu
include_directories(${Python3_INCLUDE_DIRS} ${INCLUDE_DIR})

# Füge die ausführbare Datei hinzu
add_executable(Siedler src/main.cpp)

# Füge das include-Verzeichnis für das Ziel hinzu
target_include_directories(Siedler PUBLIC ${INCLUDE_DIR} include)

# Verlinke mit den Python-Bibliotheken
target_link_libraries(Siedler ${Python3_LIBRARIES})
