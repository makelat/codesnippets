set(TARGET auxlib)
add_library(${TARGET} SHARED
#    prog.f
    interface.cxx
)
target_include_directories(${TARGET} PUBLIC include)
install(TARGETS ${TARGET} DESTINATION lib)
#install(FILES interface.h DESTINATION include/)

