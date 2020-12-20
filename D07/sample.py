def two():
    do_nothing = 0

def one():
    print(0)
    [x() for x in [two, two]]

def color():
    print(0)
    [x() for x in [one, two]]

color()
