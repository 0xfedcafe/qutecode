cmake_minimum_required(VERSION 3.21)
project(qutecode)

set(CMAKE_CXX_STANDARD 23)

add_executable(qutecode main.cpp libqrcode/qr.cpp libqrcode/qr.h libqrcode/error_correction.cpp libqrcode/poly_utils.h libqrcode/field.cpp libqrcode/field.h libqrcode/encoding.cpp libqrcode/encoding.h libqrcode/bits.cpp libqrcode/bits.h)
