set(SUBMODULE_NAME log)
message(STATUS "----configuring submodule " ${SUBMODULE_NAME})

set(${SUBMODULE_NAME}_LIBS liblog.so)

set(${SUBMODULE_NAME}_MAIN_DIR ${CMAKE_CURRENT_LIST_DIR})
set(${SUBMODULE_NAME}_INCLUDE_DIRS ${${SUBMODULE_NAME}_MAIN_DIR}/include)
set(${SUBMODULE_NAME}_LIB_DIRS  ${${SUBMODULE_NAME}_MAIN_DIR}/lib)

unset(SUBMODULE_NAME)