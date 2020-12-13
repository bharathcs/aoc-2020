import logging
logging.basicConfig(level=logging.CRITICAL)

class Passport:
    def __init__(self, passportStr):
        self.input_string = passportStr
        passportStr = passportStr.replace('\n', ' ').replace('  ', ' ')
        passport = [x.split(':') for x in passportStr.split(' ') if len(x) > 3]
        passport = dict((field, value) for (field, value) in passport)
        self.parsed = passport
        self.validity = self.passport_validator()

    def passport_validator(self):
        """Checks if the dictionary in self.parsed passes the following:
            byr - 4 digits; at least 1920 and at most 2002.
            iyr - 4 digits; at least 2010 and at most 2020.
            eyr - 4 digits; at least 2020 and at most 2030.
            hgt - a number followed by either cm or in:
                If cm, at least 150 and at most 193.
                If in, at least 59 and at most 76.
            hcl - '#' followed by six characters 0-9 or a-f.
            ecl - exactly one of: amb blu brn gry grn hzl oth.
            pid - a nine-digit number, including leading zeroes.
            cid - ignored, missing or not.
        """
        def hgt_check(hgt_val):
            unit = hgt_val[-2:]
            value = hgt_val[:-2]
            try:
                value = int(value)
            except ValueError:
                return False
            if unit == 'cm':
                return 150 <= value <= 193
            if unit == 'in':
                return 59 <= value <= 76
            return False

        def hcl_check(hcl_val):
            if hcl_val[0] != '#' or len(hcl_val) != 7:
                return False
            for i in hcl_val[1:]:
                if i in ['a', 'b', 'c', 'd', 'e', 'f']:
                    continue
                if int(i) in range(0, 10):
                    continue
                return False
            return True

        def pid_check(pid_val):
            if len(pid_val) != 9:
                return False
            for i in pid_val:
                if int(i) not in range(0, 10):
                    return False
            return True

        field_dict = self.parsed
        rules = {
            'byr': lambda x: 2002 >= int(x) >= 1920,
            'iyr': lambda x: 2020 >= int(x) >= 2010,
            'eyr': lambda x: 2030 >= int(x) >= 2020,
            'hgt': hgt_check,
            'hcl': hcl_check,
            'ecl': lambda x: x in [
                'amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'],
            'pid': pid_check
        }
        for field in rules:
            if field not in field_dict:
                logging.debug("%s not found in dictionary", field)
                return False
            check = rules[field]
            value = field_dict[field]
            logging.debug("Checking %s: %s", field, value)
            if not check(value):
                logging.debug("%s failed check: %s", field, value)
                return False
        return True


with open('input', 'r') as f:
    INPUTFILE = f.read()
PASSPORTS = [Passport(element) for element in INPUTFILE.split("\n\n")]

VALID_PASSPORTS = [line for line in PASSPORTS if line.passport_validator()]
print("Final Answer: ", len(VALID_PASSPORTS))
