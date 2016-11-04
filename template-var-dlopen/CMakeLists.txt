add_library(tpl MODULE lib.cc)
add_executable(main main.cc)
target_link_libraries(main ${CMAKE_DL_LIBS})
