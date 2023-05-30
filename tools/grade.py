import subprocess

basic_tests = [
    "test1", "test2", "test3", "test4", "test5"
]
BASIC_NEEDED = len(basic_tests)
BASIC_POINTS = 0.7

advanced_tests = [
    "testadvanced1", "testadvanced2", "testadvanced3", "testadvanced4", "testadvanced5", "testadvanced6", "testadvanced7"
]
ADVANCED_NEEDED = 4
ADVANCED_POINTS = 0.5

def run_test(test_name):
    try:
        command = "make run_" + test_name
        print(command)
        return int(subprocess.check_output(command, shell=True)) == 0
    except:
        return False


def run_tests(tests):
    passed=0
    for test in tests:
        if run_test(test):
            passed += 1

    return passed

def calc_grade(basic, advanced):
    return (basic * BASIC_POINTS) + (advanced * ADVANCED_POINTS)


if __name__ == "__main__":
    basic_passed = run_tests(basic_tests)
    advanced_passed = run_tests(advanced_tests)

    print("You are passing {}/{}) basic tests and {}/{}) advanced tests".format(basic_passed, len(basic_tests), advanced_passed, len(advanced_tests)))

    print("Your (tentative) grade is a {}".format(calc_grade(basic_passed, advanced_passed)))

    if basic_passed < BASIC_NEEDED:
        print("You must still complete {} basic tests in order to pass".format(BASIC_NEEDED - basic_passed))
    
    if advanced_passed < ADVANCED_NEEDED:
        print("You must still complete {} advanced tests in order to pass".format(ADVANCED_NEEDED - advanced_passed))

    if  advanced_passed >= ADVANCED_NEEDED and basic_passed >= BASIC_NEEDED:
        print("You are currently passing all required tests and eligible to do the bonus assignments")
        print("NOTE: Bonus assignments are graded separately")
        print("NOTE: 0.5 point style points not considered in this script")
