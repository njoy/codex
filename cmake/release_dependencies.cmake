cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         fb84b82ebf7a4789aa43cea560680cf745c6ee4f
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         2606933a854bb0269c4ec37143e1236797e27838
    )

FetchContent_Declare( eigen
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         dc252fbf00079ccab57948a164b1421703fe4361 # tag: 3.3.8
    )
set( BUILD_TESTING CACHE BOOL OFF )

FetchContent_Declare( ENDFtk
    GIT_REPOSITORY  https://github.com/njoy/ENDFtk
    GIT_TAG         da5275f7a96e68f4da25cc842c602de108104d1c
    )

FetchContent_Declare( hana-adapter
    GIT_REPOSITORY  https://github.com/njoy/hana-adapter
    GIT_TAG         f58e8973c9a614dc4f3720b5581a762c61bdbb40
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  https://github.com/njoy/header-utilities
    GIT_TAG         cc2610fee15e255c151e8e22aca1e8b3d1a96b39
    )

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         52962b7796afe37ef1d8f7edb4bf9ecb1b868d15
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         f1abf5d9159b805674197f6bc443592e631c9130 # tag: v2.6.1
    )

FetchContent_Declare( range-v3
    GIT_REPOSITORY  https://github.com/ericniebler/range-v3
    GIT_TAG         4989f3e9ff2efee1852942bb9328ef121369ba02 # tag: 0.11.0
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         a51b4856377a71f81b6d74b9af459305c4c644f8
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    catch-adapter
    disco
    eigen
    ENDFtk
    hana-adapter
    header-utilities
    Log
    pybind11
    range-v3
    spdlog
    )
