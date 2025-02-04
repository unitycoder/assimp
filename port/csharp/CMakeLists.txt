CMAKE_POLICY(PUSH)
CMAKE_POLICY(VERSION 3.14)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
	${Assimp_SOURCE_DIR}
	${Assimp_SOURCE_DIR}/include/assimp
	${Assimp_SOURCE_DIR}/include/assimp/Compiler
	${CMAKE_CURRENT_SOURCE_DIR}
)

LINK_DIRECTORIES(
	${Assimp_BINARY_DIR}
	${Assimp_BINARY_DIR}/lib
	${Assimp_BINARY_DIR}/code/
)

SET(CMAKE_SWIG_FLAGS "-c++;-namespace;Assimp")
SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
SET_SOURCE_FILES_PROPERTIES(assimp_swig.i PROPERTIES CPLUSPLUS ON)

SWIG_ADD_LIBRARY(assimp_swig LANGUAGE csharp SOURCES assimp_swig.i)
SWIG_LINK_LIBRARIES(assimp_swig assimp)

SET_TARGET_PROPERTIES(assimp_swig PROPERTIES PREFIX "")

INSTALL(TARGETS assimp_swig DESTINATION ${ASSIMP_LIB_INSTALL_DIR} COMPONENT ${LIBASSIMP_COMPONENT})

FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}" DOS_STYLE_SOURCE_DIR)
CONFIGURE_FILE(assimp_cs.csproj.template assimp_cs.csproj)

INCLUDE_EXTERNAL_MSPROJECT(
	assimp_cs ${CMAKE_CURRENT_BINARY_DIR}/assimp_cs.csproj
	TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
)

CMAKE_POLICY(POP)
