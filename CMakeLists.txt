cmake_minimum_required(VERSION 3.16)
project(ParticlePhysics)
enable_testing()

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

add_executable( main_test_1  main_test_1.cpp ParticleType.cpp ResonanceType.cpp)
target_compile_options(main_test_1 PRIVATE -Wall -Wextra -fsanitize=address )
target_link_options(main_test_1 PRIVATE -fsanitize=address)

add_executable( main_test_2 main_test_2.cpp ParticleType.cpp ResonanceType.cpp Particle.cpp)
target_compile_options(main_test_2 PRIVATE -Wall -Wextra -fsanitize=address )
target_link_options(main_test_2 PRIVATE -fsanitize=address)

