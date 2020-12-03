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

    def __str__(self):
        return (str(self.numpair)
                + '\t' + str(self.letter)
                + '\t' + str(self.valid)
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


CLEANED = [Line(i) for i in PWDS]

RESULT = reduce(lambda x, y: x + (1 if y.valid else 0),
                CLEANED, 0)
print(RESULT)
