
IF ((NOT DAS_MINFFT_INCLUDED) AND ((NOT ${DAS_MINFFT_DISABLED}) OR (NOT DEFINED DAS_MINFFT_DISABLED)))
    SET(DAS_MINFFT_INCLUDED TRUE)
    MESSAGE(STATUS "dasMinfft module included.")

	SET(DAS_MINFFT_DIR ${PROJECT_SOURCE_DIR}/modules/dasMinfft)
	SET(MINFFT_INCLUDE_DIR ${DAS_MINFFT_DIR}/minfft)

    LIST(APPEND CMAKE_MODULE_PATH ${DAS_MINFFT_DIR})

	# libDasModuleMinfft
	SET(DAS_MINFFT_MODULE_SRC
		${DAS_MINFFT_DIR}/src/dasMinfft.h
		${DAS_MINFFT_DIR}/src/dasMinfft.cpp
  	${DAS_MINFFT_DIR}/minfft/minfft.c
  	${DAS_MINFFT_DIR}/minfft/minfft.h
	)

	ADD_MODULE_CPP(Minfft)
	# ADD_MODULE_NATIVE(MINFFT_boost)
	ADD_MODULE_LIB(libDasModuleMinfft ${DAS_MINFFT_MODULE_SRC} ${DAS_MINFFT_MODULE_PLATFORM_SRC})
    target_compile_definitions(libDasModuleMinfft PUBLIC MINFFT_SINGLE)
	TARGET_LINK_LIBRARIES(libDasModuleMinfft ${MINFFT_LIBRARIES})
	# ADD_DEPENDENCIES(libDasModuleMinfft)
	TARGET_INCLUDE_DIRECTORIES(libDasModuleMinfft PUBLIC ${MINFFT_INCLUDE_DIR})

	SETUP_CPP11(libDasModuleMinfft)


	# MINFFT AOT
	add_custom_target(MINFFT_AOT)
	SET(MINFFT_GENERATED_SRC)
	SET(MINFFT_AOT
		"${DAS_MINFFT_DIR}/examples/minfft_example_sinus.das"
		"daslib/random.das"
		"daslib/math_boost.das"
	)
	DAS_AOT("${MINFFT_AOT}" MINFFT_GENERATED_SRC MINFFT_AOT daslang)
	SOURCE_GROUP_FILES("aot stub" MINFFT_GENERATED_SRC)

	# now, the demo
	SET(MINFFT_SRC
		${DAS_MINFFT_DIR}/examples/minfftAot.cpp
		${DAS_MODULES_NEED_INC}
	)
	SOURCE_GROUP_FILES("main" MINFFT_SRC)
	add_executable(minfftAot ${MINFFT_SRC} ${MINFFT_GENERATED_SRC})
	TARGET_LINK_LIBRARIES(minfftAot libDaScript libDasModuleMinfft Threads::Threads)
	ADD_DEPENDENCIES(minfftAot libDaScript)
	ADD_DEPENDENCIES(minfftAot MINFFT_AOT dasAotStub)
	TARGET_INCLUDE_DIRECTORIES(minfftAot PUBLIC ${MINFFT_INCLUDE_DIR})
	SETUP_CPP11(minfftAot)
	SETUP_LTO(minfftAot)
	ADD_EXAMPLE(minfftAot)

    file(GLOB DAS_MINFFT_EXAMPLES
		${DAS_MINFFT_DIR}/examples/*.das
    )
    install(FILES ${DAS_MINFFT_EXAMPLES}
        DESTINATION ${DAS_INSTALL_EXAMPLESDIR}/minfft
    )
	install(FILES ${PROJECT_SOURCE_DIR}/modules/dasPUGIXML/pugixml/LICENSE.md DESTINATION ${DAS_INSTALL_DOCDIR} RENAME PUGIXML.LICENSE)

ENDIF()
