cmake_minimum_required(VERSION 3.6)
project(igniter)
add_definitions(-DENABLE_ANDROID_LOG)
find_library( # Sets the name of the path variable.
          androidLogLib

          # Specifies the name of the NDK library that
          # you want CMake to locate.
          log)
add_library(trojan
    trojan/src/authenticator.cpp
    trojan/src/clientsession.cpp
    trojan/src/config.cpp
    trojan/src/forwardsession.cpp
    trojan/src/log.cpp
    trojan/src/serversession.cpp
    trojan/src/service.cpp
    trojan/src/session.cpp
    trojan/src/socks5address.cpp
    trojan/src/ssldefaults.cpp
    trojan/src/sslsession.cpp
    trojan/src/trojanrequest.cpp
    trojan/src/udpforwardsession.cpp
    trojan/src/udppacket.cpp
    trojan/src/version.cpp)
target_include_directories(trojan PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/include
    ${CMAKE_SOURCE_DIR}/libs/include/${ANDROID_ABI})
target_link_libraries(trojan
    ${CMAKE_SOURCE_DIR}/libs/lib/${ANDROID_ABI}/libboost_program_options.a
    ${CMAKE_SOURCE_DIR}/libs/lib/${ANDROID_ABI}/libboost_system.a
    ${CMAKE_SOURCE_DIR}/libs/lib/${ANDROID_ABI}/libssl.a
    ${CMAKE_SOURCE_DIR}/libs/lib/${ANDROID_ABI}/libcrypto.a
    ${androidLogLib})
add_library(jni-helper SHARED jni-helper.cpp)
target_include_directories(jni-helper PRIVATE
    ${CMAKE_SOURCE_DIR}/trojan/src
    ${CMAKE_SOURCE_DIR}/libs/include
    ${CMAKE_SOURCE_DIR}/libs/include/${ANDROID_ABI})
target_link_libraries(jni-helper trojan)
