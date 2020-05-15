# My Solutions for Google Kick Start

This repo is used for sharing my solutions for Google Kick Start contest.

The `src` folder contains my solution to the problems based on year and round. The `data` folder contains sample inputs and outputs.

## Testing Automation

I've implemented a pytest framework for group testing. Please install pytest by `pip install pytest` if you have not done so.

### What is being tested?

By giving the year, round, and the question to test, it will look for `src/<year>/Round<round>/Q<question numbe>_*` as the source code file (currently only supports `.cpp` file). Tt will compile the source code and test for:

* Correctness: run it with sample input in `data/<year>/Round<round>Q<question number>.in` and compare the output with corresponding `.out` file.
* Memory Problem: run it with `valgrind` to check memory leaks and errors (since it is C++)

### Running `pytest`

This is how you run it:
```bash
pytest run_test.py -s [--year <year> --round <round> --question <questions>]
```
where `<year>` is a four digit number for the year of the contest (e.g. `2020`), `<round>` indicates which round (e.g. `'A'`), and `<questions>` is a list of comma separated questions to be run in form of Q#, q#, or # (e.g. `'Q1,Q3'` and `1,2,4`).

If any of the options are missing, then default will run ''everything'' for that option. For example, if only round and question is defined, then it will run all solutions in year 2019 and 2020 with matching round and questions number; if round is missing, then it will run a specific set of questions in the givan year for every round.

## Progress
- [ ] [2020](https://github.com/xu932/GoogleKickStart/tree/master/src/2020)
  - [x] [Round A](https://github.com/xu932/GoogleKickStart/tree/master/src/2020/RoundA)
    - [x] [Allocation](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundA/Q1_Allocation.cpp)
    - [x] [Plates](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundA/Q2_Plates.cpp)
    - [x] [Workout](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundA/Q3_Workout.cpp)
    - [x] [Bundling](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundA/Q4_Bundling.cpp)
  - [ ] [Round B](https://github.com/xu932/GoogleKickStart/tree/master/src/2020/RoundB)
    - [x] [Bike Tours](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundB/Q1_BikeTours.cpp)
    - [x] [Bus Routes](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundB/Q2_BusRoutes.cpp)
    - [x] [Robot Path Decoding](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundB/Q3_RobotPathDecoding.cpp)
    - [ ] Bundling
- [ ] [2019](https://github.com/xu932/GoogleKickStart/tree/master/src/2019)
  - [x] [Round A](https://github.com/xu932/GoogleKickStart/tree/master/src/2019/RoundA)
    - [x] [Training](https://github.com/xu932/GoogleKickStart/blob/master/src/2020/RoundA/Q1_Allocation.cpp)
    - [ ] Parcels
    - [ ] Contention
