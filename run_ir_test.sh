make

# echo "EXPRESSIONS"
# ./parser test_inputs/test_input_expressions # echo "****************IF STATEMENTS****************"
# ./parser test_inputs/test_input_if_stmt
# echo "****************FOR STATEMENTS****************"
# ./parser test_inputs/test_input_for_stmt
# echo "****************RETURN STATEMENTS****************"
# ./parser test_inputs/test_input_return_stmt
# echo "****************DO STATEMENTS****************"
# ./parser test_inputs/test_input_do_stmt
# echo "****************WHILE STATEMENTS****************"
# ./parser test_inputs/test_input_while_stmt
echo "**************** SPIM INSTRUCTIONS ****************"
./parser test_inputs/spim_input.c - spim_output.s # && spim -file spim_output.s
                                                                             
make clean