import sys

def test_solutions(solutions):
    correct = len(solutions)
    for s in solutions:
        sys.stderr.write(f'running {str(s)}... ')
        result = 'Passed'
        try:
            s.run_exec_and_compare_result()
            s.check_memory()
        except AssertionError as e:
            sys.stderr.write(f'Solution {str(s)} failed\n')
            sys.stderr.write(str(e))
            correct -= 1
            result = 'Failed'
        sys.stderr.write(f'{result}\n')
    sys.stderr.write(f'{correct}/{len(solutions)} passed\n')
