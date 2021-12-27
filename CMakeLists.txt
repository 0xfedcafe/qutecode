cmake_minimum_required(VERSION 3.21)
project(qutecode)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic -Werror -Wextra -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O2 -Wall -Wpedantic -Werror -Wextra")
include(conanbuildinfo.cmake)
conan_basic_setup()
set(THREADS_PREFER_PTHREAD_FLAG ON)


add_executable(qutecode main.cpp libqrcode/qr.cpp libqrcode/qr.h libqrcode/error_correction.cpp libqrcode/poly_utils.h libqrcode/field.cpp libqrcode/field.h libqrcode/encoding.cpp libqrcode/encoding.h libqrcode/bits.cpp libqrcode/bits.h libqrcode/pixel.cpp libqrcode/pixel.h libqrcode/code.cpp libqrcode/code.h libqrcode/plan.cpp libqrcode/plan.h libqrcode/metadata.cpp libqrcode/metadata.h)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

