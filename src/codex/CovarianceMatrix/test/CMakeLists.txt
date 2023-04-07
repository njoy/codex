
add_executable( codex.CovarianceMatrix.test CovarianceMatrix.test.cpp )
target_compile_options( codex.CovarianceMatrix.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${codex_appended_flags} )
target_link_libraries( codex.CovarianceMatrix.test PUBLIC codex )
add_test( NAME codex.CovarianceMatrix COMMAND codex.CovarianceMatrix.test )
