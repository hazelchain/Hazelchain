include(FetchContent)

function(fetch_repo NAME REPO TAG)
    message(STATUS "fetching ${NAME} from ${REPO}...")
    FetchContent_Declare(
            ${NAME}
            GIT_REPOSITORY ${REPO}
            GIT_TAG ${TAG}
    )
    message(STATUS "populating ${NAME}...")
    FetchContent_GetProperties(${NAME})
    if (NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
    endif ()
    message(STATUS "fetched ${NAME}")
    FetchContent_MakeAvailable(${NAME})
endfunction()

function(fetch_url NAME URL)
    message(STATUS "fetching ${NAME} from ${URL}...")
    FetchContent_Declare(
            ${NAME}
            URL ${REPO}
    )
    message(STATUS "populating ${NAME}...")
    FetchContent_GetProperties(${NAME})
    if (NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
    endif ()
    message(STATUS "fetched ${NAME}")
    FetchContent_MakeAvailable(${NAME})
endfunction()