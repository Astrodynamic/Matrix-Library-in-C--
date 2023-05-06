cmake_minimum_required(VERSION 3.11)

# Включаем поддержку управления зависимостями
include(FetchContent)

# Создаем новый проект
project(TEST VERSION 1.0 LANGUAGES CXX)

#=============================================================== Setup CMake
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем путь к заголовочным файлам
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

enable_testing()

# Добавляем исполняемый файл с тестами
add_executable(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/tests.cc
)

add_library(Matrix STATIC IMPORTED)
set_target_properties(Matrix PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Matrix.a)

# Добавляем флаги компилятора для цели TEST
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -fsanitize=address
)

# Добавляем флаги связывания для цели TEST
target_link_options(
  ${PROJECT_NAME}
  PRIVATE
  -fsanitize=address
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  GTest::gtest_main
  Matrix
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
