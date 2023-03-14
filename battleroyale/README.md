# BattleRoyale

This is a battle royale game. It became really popular among
my friends back in back in 2019 and, during lockdown, we decided
to make our own. 

## Description

The game is simple. There is a list of names of the people that
participate. Each player can also have a team. The game is turn based
simulated. When a turn is run there will be a duel between two players,
where one will kill the other. 

At the same time there is an infection
called 'La Enfermedad' (notice this was created in COVID times, but
I was fed up with hearing that word in the news so I didn't want to 
see it here too). There is a chance that players get infected during a 
turn, but also of getting vaccinated. Probabilities of these events, 
and others, change over time to make the end game more interesting.

Players have a profession, that can be seen in the different output
formats. Professions are chosen randomly, although I think I introduced
a way of altering this to cheat with my friends. They grant some 
advantages or not, depending on how lucky you are with Profession 
assignments. How Professions affect the game can mainly be seen in 
`Probabulity.h` and `Probability.cpp` files.

## Modes

There are three execution modes:

- **Batch**. The game is executed in a terminal. It works by introducing
    commands in the terminal, and the command *help* or *h* will help you
    get around.
- **New**. It creates a new game from an initial save file with the
    players' names and teams. It then stores all necessary information
    into test files or JSON to reload the game.
- **JSON**. It runs a single turn and stores the information. Same as 
    new mode, it needs the name of the save files.

## Building

A Makefile is provided (copied from [here](https://gist.github.com/zobayer1/7265c698d1b024bb7723bc624aeedeb3)).
It assumed a project structure like this:
```
.
├── bin
│   └── main
├── data
│   └── problem.in
├── include
│   └── rapidjson
├── Makefile
└── src
    ├── main.cpp
    └── and rest of source files
```

A directory called ``save_files`` inside ``src`` is also provided in the
repo to show an example of initial txt file. Names there are twitter
users, but please refrain from using them in any malicious way (They 
are my friends :d).

The only dependency it has is `rapijson`, a JSON library for C++ that 
can be found on its [GitHub](https://github.com/Tencent/rapidjson/) page](https://github.com/Tencent/rapidjson/).
You should download the source code and place it all in the proper 
directory. 

If building in a Linux system make sure the ``#define AT_LINUX`` macros
are uncommented. They substitute Windows commands with native Linux ones.
The project was originally made in Windows, so if you are building in
there comment them. I have no idea how Mac works, but I guess it won't
be too different from Linux systems.

If you have Make, then just go to root directory and `make`. If you are
building in an IDE you will need to add the ``include/rapidjson`` path
to the search paths of the IDE.

Output binaries will be placed in `bin` folder, and when giving a path
to the execution, the root will be that directory.

## About the code and usage

The code might not be the prettiest, or most efficient, or even correct, 
but it was good practise for me and you might find useful some patterns
applied. Inside the project, almost everything is in Spanish, as it
was meant just for us to play.

- **Model-View-Controller**. Usual pattern used to be able to 
    change the output format. Its main component are the `Controller`, 
    the `Display` or `JSONOutput` for the view and the `Game`.
- **Singleton**. Used to make sure there is only one instance of an object. In this case used in the `Controller`.
- **Commands**. I am not sure if this is a programming pattern, but
    it is a nice example of inheritance.

Feel free to change the code in any way you want. I can't assure I will
make any fix in case there is a bug (neither do I think anyone will
care), but if you find something wrong in the code you can post an Issue
or, as a nice exercise, fix the mess I surely will have done in this
little project.

The program is prepared to be run along a Twitter bot. It worked back
in the day, not sure if it will now since all the changes in the platform.
However, on batch mode, my friends and I did have a good time on discord seeing who 
would survive, putting funny names and spicing it up with our inner jokes, so you might find it funny too.
The Twitter bot did work, although we never decided to put it in public and make a battle with people outside. That sort of thing was popular in our city at least, but by the time I finished programming everything,
the fuss about it had been long gone. A real pity. 

Anyway, use it however you want, and hope it is useful or at least fun 
for somebody.
