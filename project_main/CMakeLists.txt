project(in_progress)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -std=c++17")

# Detta kommer från kurshemsidan
set(SOURCE_FILES in_progress.cc)
# På skolans Linux - system finns det två versioner av SFML. Se efter vilken som används :
if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/6.1.0.*"))
  set(CMAKE_CXX_COMPILER /sw/gcc-6.1.0/bin/g++)
  if (DEFINED ENV{SFML_ROOT})
    list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
  endif ()
endif ()

# Välj vilka moduler i SFML som ska användas .
set(SFML_MODULES network graphics window system)

# Försök att hitta SFML genom att anropa 'FindSFML .cmake ' (om det finns ).
find_package (SFML 2 COMPONENTS ${SFML_MODULES})
include_directories (${SFML_INCLUDE_DIR})

# Om det inte finns hoppas vi på att SFML finns installerat ändå.
if (NOT (${SFML_FOUND} STREQUAL "TRUE"))
  set(SFML_LIBRARIES "")
  foreach (i ${SFML_MODULES})
    list(APPEND SFML_LIBRARIES "sfml-${i}")
  endforeach (i)
endif ()

add_executable (in_progress ${SOURCE_FILES})
target_link_libraries (in_progress ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
