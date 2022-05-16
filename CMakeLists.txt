
file(GLOB SRC "*.c")
file(GLOB HDR "*.h")

set(DATE_PARSER "date-parser")
add_executable(${DATE_PARSER} ${SRC} ${HDR})

set(OUT_DIR ${PROJECT_SOURCE_DIR}/out)

message(STATUS "output dir = ${OUT_DIR}")

set_target_properties(${DATE_PARSER} PROPERTIES
                                     OUTPUT_NAME ${DATE_PARSER}
                                     RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}
                                     )
