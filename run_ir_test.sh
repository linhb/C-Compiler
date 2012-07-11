make

# echo "EXPRESSIONS"
# ./compiler test_inputs/test_input_expressions # echo "****************IF STATEMENTS****************"
# ./compiler test_inputs/test_input_if_stmt
# echo "****************FOR STATEMENTS****************"
# ./compiler test_inputs/test_input_for_stmt
# echo "****************RETURN STATEMENTS****************"
# ./compiler test_inputs/test_input_return_stmt
# echo "****************DO STATEMENTS****************"
# ./compiler test_inputs/test_input_do_stmt
# echo "****************WHILE STATEMENTS****************"
# ./compiler test_inputs/test_input_while_stmt
echo "**************** SPIM INSTRUCTIONS ****************"
# ./compiler test_inputs/test_input_comparison.c - test_input_comparison.s && spim -file test_input_comparison.s
# ./compiler test_inputs/test_input_for_stmt.c - test_input_for_stmt.s && spim -file test_input_for_stmt.s
./compiler test_inputs/test_input_function_entry.c - test_input_function_entry.s && spim -file test_input_function_entry.s
# ./compiler test_inputs/test_input_factorial.c - test_input_factorial.s && spim -file test_input_factorial.s
                                                                             
make clean