cmake_minimum_required(VERSION 3.10)
project( w_serial_comm )
# find_package( OpenCV REQUIRED )
# find_package( OpenMP REQUIRED )
# include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( w_serial_comm  ZeroW_UART_Comm.cpp )
# target_link_libraries( w_serial_comm ${OpenCV_LIBS} )
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(w_serial_comm OpenMP::OpenMP_CXX)
# endif()