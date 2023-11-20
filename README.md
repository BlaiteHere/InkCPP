# InkCPP

### HELLO EVERYONE!
Welcome to README.md of my project:
> `my game - Rupestri`

### Which is actually my first CPP [ACTUAL GAME / PROJECT]

# I'LL BE MAKING IT WITH THESE
 > stuff I use

```
+ 😝 C++ (compiler: G++)
+ 💻 GIT (GitHub)
+ 🤓 VISUAL STUDIO CODE
+ 🙂 WINDOWS (duh)
+ 👾 DISCORD
+ 📝 PHYSICAL NOTEPAD
+ 🧠 THOUGHTS && IDEAS of mine

~ 😎 FRIENDS
```



# FAQ:

## OKAY THEN, HOW DO I PLAY THE GAME/COMPILE?

### There's also a RELEASE with a compiled `.exe` file & Dynamic libs that should work on any Windows & maybe Linux OS!
Otherwise, you can try compiling the files *yourself*.

### The compiling tutorial will be at the end of this document.



## BUT JOHN, WHAT IS THE GAME ABOUT?
 > about

The game will revolve about you, human.
You'll seek shelter and materials to
Survive in harsh environment of nature.
You'll make tools and fight monsters.
Or you will befriend them! your choice.
There's no goals. you do what you want.
Build structures, gather resources
**In this pocket-sized 1d adventure.**

# Goals:

### WHAT I'LL BE DOING ASAP!
 > aka current goals

```
+ make Interaction with Tiles work
 + class type Action with `name` (to display), what the Tile should change to
(if it even should), what Item the player has to have equipped to do the action
successfully && what `loot_table` to give to the player when
the Interaction is successful

- make Inventory and Items work
 - make Items removed from inventory and use them
 - make Tools have `Durability` that will replace `Amount`
 - make Tools have `max_durability` or `max_amount`
 - improve Inventory TUI design

- make Crafting system (recipes, Crafting, Workbench)
 - make Workbench give you access to better recipes
 - make dynamic Tiles as Chest work

- improve visible chunk/scene design

~ make Tiles animated and change (example: make Crops grow)
```



# FUTURE IMPROVEMENTS PLANNED
 > more abstract goals

If something works, I'll mark it with a plus (+) instead of a default minus (-).

```
- working Inventory & Hand system;
 + working Items
 + working Inventory UI
 + working Item Holding and Usage

- working Crafting system;
 - working Inventory/Crafting UI

- save game to files;
 + saving chunks with a function
 - saving game essentials to a file
 ~ optimising tiles into dynamic (eg. chest, house) && static (eg. tree, rock)

+ more GameViewMode support;
 + making all GameViewMode dependant functions execute in one function,
so you don't need to go to `getInput()` and `main()` separately when
changing one thing

~ more Structures: spawned & built;
 ~ world generation with enabled spawning structures and
being able to loot them (like Statue, Lake)
 - Crafting system giving structures to Inventory and ability to place them
(like House, Camp & Farm 
~ Enemies & battle system;
 - ability to defeat Enemies in a battle
 - ability to calm Enemies & exit battling
 - making Enemies give you resources if befriended or defeated
```

 #survival #sandbox #ascii-game
 #strategic #turn-based #generetive-world



# HowToCompile: Part II

GUIDE:

### Download && Install a MinGW C++ Compiler
 > default https://www.mingw-w64.org
 > or my fav: https://sourceforge.net/projects/mingw

### Check if G++ works as intended
```
g++ --version
```
If you got an error, there's something wrong with your installation.
You might also need to go to Windows Settings && add `g++` to your system's variables || you can just use `g++` in the same directory as `main.cpp`

### Compiling && Linking `main.cpp` file (example for `g++` on Windows)
 > Open CMDL (Command Line)
 > Go to the file directory, compile && link the file to `a.exe` && then execute it in the terminal using the following cmds:
```bash
cd [file path of the InkCPP folder]
g++ main.cpp
a.exe
```
 > Boom! You should now see my game in your CMDL up && running! Good job.
### There are also releases, that should from release v0.1.4 work.

# Have fun
 > This is just a demo of the project.
 > You can code things in yourself, if you're `(smart && lucky)` enough to understand my code.
 > It's not much, but think of the bright side:
