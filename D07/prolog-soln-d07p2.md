Do all the steps from the previous to turn all the two word colours into one word, then convert each line to so:
```
drab-gray bag contain 5 mirrored-white bag, 1 light-green bag, 5 shiny-lavender bag, 5 faded-aqua bag.
drab-gray bag contain mirrored-white mirrored-white mirrored-white mirrored-white mirrored-white bag, light-green bag, shiny-lavender shiny-lavender shiny-lavender shiny-lavender shiny-lavender bag, faded-aqua faded-aqua faded-aqua faded-aqua faded-aqua bag.             
```

For this, I used neovim with the following macro: `let @q = '/\dA 1 I:%s/1\s//g/\dwyWhp@q'`. 

I used more search and replace to convert this:
```
muted-blue bag contain vibrant-lavender bag, dotted-silver dotted-silver dotted-silver dotted-silver bag, dim-indigo dim-indigo bag.    
drab-gray bag contain mirrored-white mirrored-white mirrored-white mirrored-white mirrored-white bag, light-green bag, shiny-lavender shiny-lavender shiny-lavender shiny-lavender shiny-lavender bag, faded-aqua faded-aqua faded-aqua faded-aqua faded-aqua bag.            
```
To the final form here:
```
muted-blue = [vibrant-lavender, dotted-silver, dotted-silver, dotted-silver, dotted-silver, dim-indigo, dim-indigo].
drab-gray = [mirrored-white, mirrored-white, mirrored-white, mirrored-white, mirrored-white, light-green, shiny-lavender, shiny-lavender, shiny-lavender, shiny-lavender, shiny-lavender, faded-aqua, faded-aqua, faded-aqua, faded-aqua, faded-aqua].
```
