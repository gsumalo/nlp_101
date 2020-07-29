set(PART_NAME nlp_101)

set(${PART_NAME}_INC
    nlp/filter.hpp
    nlp/grammar.hpp
)

set(${PART_NAME}_SRC
    main.cpp
    nlp/filter.cpp
    nlp/grammar.cpp
)

add_executable(${PART_NAME} ${${PART_NAME}_INC} ${${PART_NAME}_SRC})

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
