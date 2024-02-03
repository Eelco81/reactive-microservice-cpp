
project(testmain)
add_library(testmain STATIC testmain.cc)
target_link_libraries(testmain PUBLIC gtest gmock loggermock)