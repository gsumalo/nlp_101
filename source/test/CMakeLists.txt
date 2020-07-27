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
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libbidd.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_atomic-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_random-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_log_setup-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_log-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_iostreams-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_date_time-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_chrono-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_regex-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_thread-vc141-mt-gd-x64-1_67.lib
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_program_options-vc141-mt-gd-x64-1_67.lib
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_system-vc141-mt-gd-x64-1_67.lib
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_filesystem-vc141-mt-gd-x64-1_67.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libxl.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/onig.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/icudt.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/icuind.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/icuiod.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/icutud.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/icuucd.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/sqlapiud.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libcurld.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/ssleay32.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libeay32.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/zlibd.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/tbb_debug.lib
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/ippcoremt.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/gtest.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libbid.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_atomic-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_random-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_log_setup-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_log-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_iostreams-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_date_time-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_chrono-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_regex-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_thread-vc141-mt-x64-1_67.lib
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_program_options-vc141-mt-x64-1_67.lib
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_system-vc141-mt-x64-1_67.lib
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_filesystem-vc141-mt-x64-1_67.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libxl.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/onig.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/icudt.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/icuin.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/icuio.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/icutu.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/icuuc.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/sqlapiu.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libcurl.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/ssleay32.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libeay32.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/zlib.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/tbb.lib
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/ippcoremt.lib
##        general Crypt32.lib
##        general Version.lib
##        general Wldap32.lib
##        general ws2_32.lib
    )
elseif(UNIX)
    target_link_libraries(${PART_NAME}
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libgtest.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libbid.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_log.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_log_setup.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_iostreams.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_regex.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_chrono.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_date_time.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_thread.a
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_program_options.a
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_filesystem.a
        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libboost_system.a
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libicuio.so.67
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libicui18n.so.67
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libicuuc.so.67
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libicudata.so.67
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libsqlapiud.so
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libcurl.so.4.4.0
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libssl.so.1.0.0
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libcrypto.so.1.0.0
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libxl.so
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libz.so.1.2.11
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libonig.so
##        debug ${THIRD_PARTY_LIBRARY_DIR}/Debug/libtbb_debug.so.2
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libgtest.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libbid.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_log.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_log_setup.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_iostreams.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_regex.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_chrono.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_date_time.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_thread.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_program_options.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_filesystem.a
        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libboost_system.a
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libicuio.so.67
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libicui18n.so.67
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libicuuc.so.67
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libicudata.so.67
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libsqlapiu.so
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libcurl.so.4.4.0
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libssl.so.1.0.0
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libcrypto.so.1.0.0
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libxl.so
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libz.so.1.2.11
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libonig.so
##        optimized ${THIRD_PARTY_LIBRARY_DIR}/Release/libtbb.so.2
##        general dl
##        general rt
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
