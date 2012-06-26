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
./compiler test_inputs/spim_input.c - spim_output.s && spim -file spim_output.s
                                                                             
make clean