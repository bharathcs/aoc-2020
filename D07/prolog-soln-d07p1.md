# Prolog Solution for AOC 2020 Day 07 Part 1

## Prolog notes

- Composed of facts, rules and queries
    - Facts just state things to be true. Can use bound or unbound (unknown) variables. 
        - E.g. `featherless(plucked-chicken).`
    - Rules states relationships between variables.
        - E.g. `isHuman(X) :- featherless(X), biped(X).`
    - Unbound / bound variables matter in your facts

## Making the prolog knowledge base

First step is to turn every two word colour to a single hyphenated word.

Neovim steps (works for any vim variant):
1. Replace all 'bags' with 'bag'.
1. Search for 'bag'.
1. Run the following recursive macro: `let @q = 'nbhr-nnb@q'`

This will convert line 1 to line 2:
```
drab gray bags contain 5 mirrored white bags, 1 light green bag, 5 shiny lavender bags, 5 faded aqua bags.
drab-gray bag contain 5 mirrored-white bag, 1 light-green bag, 5 shiny-lavender bag, 5 faded-aqua bag.
```

Next step is to prepend, append and replace ' contains ' to convert the input file into a prolog knowledge base. Stored as `part1.pl` here.

## Running the prolog file

To load a prolog knowledge base (e.g. `this-file.pl`, open your terminal in the directory where you have stored the file and hit `[this-file].`

Finding the solution:
```
?- [part1].
?- forall(in(X, shiny-gold), writeln(X)).
```

The terminal output has to be copy pasted into a text file, stripped of duplicate lines and then the number of lines must be counted.
I used neovim (any vim variant will work) and ran the command `:sort u` to do this.
(This was my first time touching prolog, have mercy at my impure solution.)

