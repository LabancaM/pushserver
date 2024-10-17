cmake_minimum_required (VERSION 3.0)
project (xxxxxxxxxx C)

set(CMAKE_INSTALL_PREFIX "/opt/pehu")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "gbe") #required

# dependences
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "yyyyyyy")

link_directories("/usr/local/unity")
include_directories("/usr/local/unity")

set(PostgreSQL_INCLUDE_DIRS "/usr/include/postgresql")
include_directories (${PostgreSQL_INCLUDE_DIRS})

include(CTest)
include(CPack)

include_directories(/opt/pehu/include)
link_directories(/opt/pehu/lib)


#add_subdirectory(src)
