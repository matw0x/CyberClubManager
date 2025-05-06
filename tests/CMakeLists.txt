set(RUN_TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/run_tests.py)

# impossible tests, because they use absolute path to .exe
# but checked manually
# add_test(
#     NAME validator_argc_1
#     COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
#             "${CMAKE_CURRENT_SOURCE_DIR}/test_validator_argc_1/expected_output.txt"
#             --
#             "$<TARGET_FILE:ccm>"
# )

# add_test(
#     NAME validator_argc_3
#     COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
#             "${CMAKE_CURRENT_SOURCE_DIR}/test_validator_argc_3/expected_output.txt"
#             --
#             "$<TARGET_FILE:ccm>"
#             "dummy_arg1"
#             "dummy_arg2"
# )

add_test(
    NAME validator_file_not_found
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/validator_file_not_found/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/validator_file_not_found/non_existent_file.txt"
)

add_test(
    NAME validator_no_extension
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/validator_no_extension/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/validator_no_extension/file_no_ext"
)

add_test(
    NAME validator_wrong_extension
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/validator_wrong_extension/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/validator_wrong_extension/file.csv"
)

add_test(
    NAME parser_empty_line
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_empty_line/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_empty_line/invalid_input.txt"
)

add_test(
    NAME parser_table_count_not_number
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_table_count_not_number/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_table_count_not_number/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_1
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_1/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_1/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_2
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_2/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_2/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_3
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_3/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_3/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_4
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_4/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_4/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_5
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_5/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_5/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_6
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_6/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_6/invalid_input.txt"
)

add_test(
    NAME parser_bad_time_format_7
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_7/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_bad_time_format_7/invalid_input.txt"
)

add_test(
    NAME parser_cost_not_positive_number
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_cost_not_positive_number/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_cost_not_positive_number/invalid_input.txt"
)

add_test(
    NAME parser_cost_very_big_number
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_cost_very_big_number/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_cost_very_big_number/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_1
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_1/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_1/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_2
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_2/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_2/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_3
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_3/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_3/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_4
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_4/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_4/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_5
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_5/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_5/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_6
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_6/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_6/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_7
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_7/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_7/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_8
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_8/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_8/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_9
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_9/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_9/invalid_input.txt"
)

add_test(
    NAME parser_event_invalid_format_10
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_10/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser_event_invalid_format_10/invalid_input.txt"
)

add_test(
    NAME business_logic_1
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_1/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_1/valid_input.txt"
)

add_test(
    NAME business_logic_2
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_2/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_2/valid_input.txt"
)

add_test(
    NAME business_logic_3
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_3/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_3/valid_input.txt"
)

add_test(
    NAME business_logic_4
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_4/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_4/valid_input.txt"
)

add_test(
    NAME business_logic_5
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_5/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_5/valid_input.txt"
)

add_test(
    NAME business_logic_6
    COMMAND ${Python3_EXECUTABLE} ${RUN_TEST_SCRIPT}
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_6/expected_output.txt"
            --
            "$<TARGET_FILE:ccm>"
            "${CMAKE_CURRENT_SOURCE_DIR}/business_logic_6/valid_input.txt"
)