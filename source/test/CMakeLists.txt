set(PART_NAME nlp_test)

set(${PART_NAME}_INC
    convenience.hpp
    environment.hpp
)

set(${PART_NAME}_SRC
    environment.cpp
    main.cpp
    tests/console.cpp
)

add_executable(${PART_NAME} ${${PART_NAME}_INC} ${${PART_NAME}_SRC})

## --- 3rd party libs ---
if(WIN32)
    set_target_properties(${PART_NAME} PROPERTIES LINK_FLAGS "/ignore:4099 /INCREMENTAL")

    target_link_libraries(${PART_NAME}
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/gtest.lib
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_program_options-vc141-mt-gd-x64-1_67.lib
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_system-vc141-mt-gd-x64-1_67.lib
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_filesystem-vc141-mt-gd-x64-1_67.lib
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_program_options-vc141-mt-x64-1_67.lib
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_system-vc141-mt-x64-1_67.lib
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_filesystem-vc141-mt-x64-1_67.lib
    )
elseif(UNIX)
    target_link_libraries(${PART_NAME}
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libgtest.a
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_program_options.a
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_filesystem.a
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_system.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libgtest.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_program_options.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_filesystem.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_system.a
        general pthread
    )
endif(WIN32)

## --- MSVC filters ---
if(WIN32)
    foreach(dep ${${PART_NAME}_INC})
        set(group_name "Header Files")

        string(FIND ${dep} "/" dir_end REVERSE)
        
        if(${dir_end} GREATER 0)
            string(SUBSTRING ${dep} 0 ${dir_end} dir)
            set(group_name "${group_name}/${dir}")
        endif(${dir_end} GREATER 0)
        
        string(REPLACE "/" "\\" final_group_name "${group_name}")
        
        source_group("${final_group_name}" FILES "${dep}")
    endforeach(dep)
    foreach(dep ${${PART_NAME}_SRC})
        set(group_name "Source Files")

        string(FIND ${dep} "/" dir_end REVERSE)
        
        if(${dir_end} GREATER 0)
            string(SUBSTRING ${dep} 0 ${dir_end} dir)
            set(group_name "${group_name}/${dir}")
        endif(${dir_end} GREATER 0)
        
        string(REPLACE "/" "\\" final_group_name "${group_name}")

        source_group("${final_group_name}" FILES "${dep}")
    endforeach(dep)    
endif(WIN32)

## --- Package ---
install(TARGETS ${PART_NAME} RUNTIME DESTINATION .)
