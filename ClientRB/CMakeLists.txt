cmake_minimum_required(VERSION 3.10)
project(ClientRB)

# Указываем директорию с файлом каскада
set(CASCADE_FILE "${CMAKE_SOURCE_DIR}/../Data/haarcascade_fullbody.xml")

# Копируем файл каскада в директорию сборки при сборке проекта
file(COPY ${CASCADE_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Подключим библиотеку rapidjson
include(FetchContent)
FetchContent_Declare(rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
)
FetchContent_MakeAvailable(rapidjson)
include_directories(${rapidjson_SOURCE_DIR}/include)

# Добавление исполняемого файла
add_executable(ClientRB src/main.cpp src/Application.cpp src/Alphabot.cpp src/Clientget.cpp src/Recogniser.cpp src/Send.cpp src/Table.cpp)
add_compile_definitions(CMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

# Подключение директории с заголовками
target_include_directories(ClientRB PUBLIC inc)

# Поиск и подключение библиотек
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(ClientRB ${WIRINGPI_LIBRARIES} ${OpenCV_LIBS} httplib)
