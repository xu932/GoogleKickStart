import os
import pytest
import re
import subprocess
import sys

########################################
# Helper classes
########################################

class Solution(object):
    def __init__(self, info):
        self.info = info
        self.solution = self._load_solution(info[0], info[1], info[2])
        self.in_file, self.out_file = self._load_test_data(info[0], info[1], info[2])
        self.exec = f'Y{info[0]}R{info[1]}Q{info[2]}'

    def __str__(self):
        return f'Y{self.info[0]} Round {self.info[1]} Q{self.info[2]}'

    def _load_solution(self, year, rnd, question):
        path = os.path.join(os.getcwd(), 'src')
        if year not in os.listdir(path):
            return ''
        path = os.path.join(path, year)
        if f'Round{rnd}' not in os.listdir(path):
            return ''
        path = os.path.join(path, f'Round{rnd}')
        
        files = os.listdir(path)
        for f in files:
            if f.startswith(f'Q{question}'):
                return os.path.join(path, f)
        return ''

    def _load_test_data(self, year, rnd, question):
        path = os.path.join(os.getcwd(), 'data')
        if year not in os.listdir(path):
            return ''
        path = os.path.join(path, year)

        if f'Round{rnd}Q{question}.in' not in os.listdir(path) or \
            f'Round{rnd}Q{question}.out' not in os.listdir(path):
            return '', ''

        return os.path.join(path, f'Round{rnd}Q{question}.in'), os.path.join(path, f'Round{rnd}Q{question}.out')

    def is_valid(self):
        return all((self.solution, self.in_file, self.out_file))

    def compile_solution(self):
        try:
            subprocess.check_call(['g++', '-std=c++14', '-Wall', '-Wno-sign-compare', '-o', self.exec, self.solution])
        except subprocess.CalledProcessError as e:
            sys.stderr.write(f'{self.__str__()} failed to compile...\n')
            return False
        return True

    def cleanup(self):
        subprocess.check_call(['rm', '-rf', self.exec])

    def run_exec_and_compare_result(self):
        with open(self.in_file, 'r') as f:
            stdin = f.read()
        output = subprocess.check_output([f'./{self.exec}'], universal_newlines=True, input=stdin)
        if output[-1] == '\n':
            output = output[:-1]
        with open(self.out_file, 'r') as f:
            expect = f.read()
        if expect[-1] == '\n':
            expect = expect[:-1]
        
        assert output == expect, 'The output does not match expected output'
    
    def check_memory(self):
        with open(self.in_file, 'r') as f:
            stdin = f.read()
        output = subprocess.check_output(['valgrind', '--tool=memcheck', '--leak-check=full', '--track-origins=yes', f'./{self.exec}'],
                                         stderr=subprocess.STDOUT, universal_newlines=True, input=stdin)
        leaks = re.findall(r'lost: ([0-9,]+ bytes in [0-9]+ blocks\n)', output)
        assert len(leaks) == 0, f'Memory leak detected: {sum([int(leak) for leak in leaks])} bytes are leaked'
        error = re.findall(r'ERROR SUMMARY: ([0-9,]+) errors from ([0-9,]+) contexts', output)
        assert len(error) == 1 and len(error[0]) == 2 and int(error[0][0]) + int(error[0][1]) == 0,\
            f'Memory error detected: {error[0][0]} errors from {error[0][1]} contexts'


########################################
# CLI parser
########################################

def pytest_addoption(parser):
    parser.addoption('--year', dest='year', type=str, default='all',
                     help='the year of the testing question (e.g. 2020)')
    parser.addoption('--round', dest='round', type=str, default='all',
                     help='the round of the testing question in a single letter (e.g. \'A\'')
    parser.addoption('--question', dest='question', type=str, default='all',
                     help='which questions (comma separated) to run in form of "Q#" or "q#" or "#" (e.g. \'q3,q4\')')

########################################
# pytest fixtures
########################################

@pytest.fixture(scope='session')
def collect_tests(request):
    year_raw = request.config.getoption('year')
    year = [year_raw] if year_raw != 'all' else ['2019', '2020']
    rnd_raw = request.config.getoption('round').upper()
    rnd = [rnd_raw] if rnd_raw != 'ALL' else ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
    question_raw = request.config.getoption('question').lower()
    question = question_raw.replace('q', '').split(',') if question_raw != 'all' else ['1', '2', '3', '4']

    return [(y, r, q) for y in year for r in rnd for q in question]


@pytest.fixture(scope='session')
def solutions(collect_tests):
    sol = []
    for test in collect_tests:
        s = Solution(test)
        if s.is_valid() and s.compile_solution():
            sol.append(s)
    print()
    yield sol

    for s in sol:
        s.cleanup()
