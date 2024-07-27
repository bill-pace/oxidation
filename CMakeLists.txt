cmake_minimum_required(VERSION 3.28)
project(oxidation)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        Corrosion
        GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
        GIT_TAG v0.5
)
FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH prime_iter/Cargo.toml)

add_executable(oxidation main.cpp)
target_link_libraries(oxidation PUBLIC prime_iter)
