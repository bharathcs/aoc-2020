% A bright white bag, which can hold your shiny gold bag directly.
% A muted yellow bag, which can hold your shiny gold bag directly, plus some other bags.
% A dark orange bag, which can hold bright white and muted yellow bags, either of which could then hold your shiny gold bag.
% A light red bag, which can hold bright white and muted yellow bags, either of which could then hold your shiny gold bag.% 

bags_in(bw, [sg]).
bags_in(my, [sg]).
bags_in(do, [bw, my]).
bags_in(lr, [bw, my]).
direct_in(X,Y) :- bags_in(X,Z), member(Y,Z).
in(X,Y) :- direct_in(X,Y).
in(X,Y) :- direct_in(X,Z), in(Z,Y).
