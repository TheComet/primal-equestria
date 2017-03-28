Primal Equestria
================

3D Horror/Puzzle adventure game.

Building Urho3D
---------------
Execute the following script to set up the correct symlinks to Urho3D.
```
./scripts/setup-urho3d.sh /path/to/urho3d/installation
```
Next, build as you would any other CMake project (make a "build" directory, run cmake, make). The following CMake options are recommended
```
-DURHO3D_C++11=ON -DURHO3D_EXTRAS=ON -DURHO3D_LUA=ON -DURHO3D_LUAJIT=ON -DURHO3D_SAMPLES=ON
```

Story
-----
A  game  where  you craft spells by  combining  lots  of  fundamental  spells.
Everything is based on the laws of physics.
 
You wake up in some lab to find a unicorn horn has been transplanted onto your
forehead. You miraculously escape by accidentally casting a powerful spell and
killing everyone in the lab.  You  later  find out the reason you were able to
escape  is  because your horn used to belong  to  one  of  the  most  powerful
unicorns in (unnamed alternate universe). It was a self defense mechanism. You
learn that you are part of a secret  experimental military operation that aims
to create an army of modified humans who  can perform deadly magic. The source
of their magic comes from transplanted unicorn horns. The military has invaded
most  of  (unnamed alternate universe) and are killing unicorns  en  masse  in
order to obtain more horns.

Game Mechanics
--------------
The  game  is  a  first  person  puzzle/horror  game  and  you  learn  various
fundamental  spells  on  your  journey through  the  military  complex  and  -
eventually - the parallel universe.
   
The spell system  is  the unique part of this game. The horn acts as an energy
converter, in that it converts your  calories  into pure energy, which in turn
can  be  converted  into  various  other   forms   (light,   electric  charge,
force/pressure, heat/cold). The "spells" you learn all in some way take a form
of energy as an input and convert it to some output. You can  combine  them in
every which way you see fit to craft unique spells.
    
Seeing as you are limited to a number of calories you  can  spend and are also
limited on how fast you can convert calories,  it should create an interesting
game mechanic.
