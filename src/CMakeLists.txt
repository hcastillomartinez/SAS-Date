set(OUT_DIR ${PROJECT_SOURCE_DIR}/out)
file(GLOB SRC "*.c")
file(GLOB HDR "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable(${OUT_NAME} ${SRC} ${HDR})

message(STATUS "output dir: ${OUT_DIR}")

target_include_directories(${OUT_NAME} PRIVATE
                            ${PROJECT_SOURCE_DIR}/src
                            ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${OUT_NAME} PROPERTIES
                                     OUTPUT_NAME ${OUT_NAME}
                                     RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}
                                     )
