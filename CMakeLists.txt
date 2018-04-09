cmake_minimum_required (VERSION 2.8.3)
project (InnovationTeam)

include_directories(include)

set(SCHMITT_SIM_SOURCE src/schmitt_sim.cpp)
set(SIM_HEADER_FILES include/simulation/schmitt_trigger.h)

add_executable(schmitt_sim ${SCHMITT_SIM_SOURCE})

