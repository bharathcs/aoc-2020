"""On Day 2 part 1
"""

from functools import reduce

with open('input') as f:
    PWDS = f.readlines()


class Line:
    """Each password and policy pair
    """

    def __init__(self, line):
        parsed = line.split()
        self.line = line
        self.numpair = parsed[0].split("-")
        self.letter = parsed[1][0]
        self.pwd = parsed[2]
        self.valid = self.policy_check()
        self.valid2 = self.policy2()

    def __str__(self):
        return (str(self.numpair)
                + '\t' + str(self.letter)
                + '\t' + str(self.valid)
                + '\t' + str(self.valid2)
                + '\t' + str(self.pwd)
                + '\t' + str(self.line) + '\n')

    def policy_check(self):
        """Checks if the passwords match the policy
        """
        count = 0
        for ltr in self.pwd:
            if ltr == self.letter:
                count += 1
        start = int(self.numpair[0])
        end = int(self.numpair[1])
        return start <= count <= end

    def policy2(self):
        """Checks if the passwords match the second policy
        """
        first = self.pwd[int(self.numpair[0]) - 1]
        second = self.pwd[int(self.numpair[1]) - 1]
        return (first == self.letter) == (second != self.letter)


CLEANED = [Line(i) for i in PWDS]

RESULT = reduce(lambda x, y: x + (1 if y.valid else 0),
                CLEANED, 0)
RESULT2 = reduce(lambda x, y: x + (1 if y.valid2 else 0),
                 CLEANED, 0)
print(RESULT, RESULT2)
